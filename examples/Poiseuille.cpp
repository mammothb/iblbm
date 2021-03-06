#include <iostream>
#include "UnitTest++/UnitTest++.h"
#include "CuboidGeometry2D.hpp"
#include "Descriptor.hpp"
#include "HeuristicLoadBalancer.hpp"
#include "IndicatorFunctor2D.hpp"
#include "MpiManager.hpp"
#include "SuperGeometry2D.hpp"
#include "UnitConverter.hpp"
#include "Vector.hpp"

namespace iblbm
{
TEST(Simulation_Poiseuille_BodyForceDriven)
{
  class PoiseuilleBodyForceDriven
  {
   public:
    PoiseuilleBodyForceDriven()
    {
      std::cout << "called" << std::endl;
    }
  };

  // ========== Initialization ==========
  const auto lx {2.0};  // length of channel
  const auto ly {1.0};  // height of channel
  const auto resolution {20};
  const auto Re {10.0};  // Reynolds number
  const auto max_phys_time {20.0};  // Max simulation time, s
  const auto phys_interval {0.2};  // Interval for convergence check, s
  const auto residual {1e-5};  // residual for convergence check

  const UnitConverterFromResolutionAndRelaxationTime<double,
      descriptor::ForcedD2Q9Descriptor> converter {
          unsigned{resolution},
          /*latticeRelaxationTime=*/0.8,
          /*charPhysLength=*/1.0,
          /*charPhysVelocity=*/1.0,
          /*physViscosity=*/1.0 / Re,
          /*physDensity=*/1.0
      };
  converter.Print();

  // ========== Prepare geometry ==========
  Vector2D<double> extent {lx, ly};
  Vector2D<double> origin;
  IndicatorCuboid2D<double> indicator_cuboid {extent, origin};

  // Instantiation of cuboid geometry with weights
  const auto num_cuboid {MpiManager::Instance().GetSize()};
  CuboidGeometry2D<double> cuboid_geometry {indicator_cuboid,
      converter.GetConversionFactorLength(), num_cuboid};

  // Periodic boundary in x-direction
  cuboid_geometry.SetIsPeriodic(true, false);

  // Instantiation of load balancer
  HeuristicLoadBalancer<double> load_balancer {cuboid_geometry};

  SuperGeometry2D<double> super_geometry {cuboid_geometry, load_balancer,
      /*overlap=*/2};

  PoiseuilleBodyForceDriven simulation;
}
}  // namespace iblbm
