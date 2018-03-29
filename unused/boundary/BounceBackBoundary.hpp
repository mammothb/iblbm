#ifndef SRC_BOUNDARY_BOUNCEBACKBOUNDARY_HPP_
#define SRC_BOUNDARY_BOUNCEBACKBOUNDARY_HPP_

#include "AbstractBoundaryCondition.hpp"
#include "AbstractCollisionModel.hpp"
#include "Node.hpp"

namespace iblbm
{
class BounceBackBoundary : public AbstractBoundaryCondition
{
 public:
  /**
   * This constructor creates bounce back nodes. Creates fullway bounce back
   * nodes when p_cm points to a valid AbstractCollisionModel. Creates
   * halfway bounceback nodes when p_cm is a nullptr
   *
   * \param r_lm AbstractLatticeModel to provide information on the number of
   *        rows, columns, dimensions, discrete directions and lattice
   *        velocity
   * \param p_cm CollisionModel to indicate which nodes to be skipped during
   *        the collision step
   */
  BounceBackBoundary(
      AbstractLatticeModel& rLatticeModel
    , AbstractCollisionModel* pCollisionModel = nullptr);

  ~BounceBackBoundary() = default;

  void UpdateNodes(
      std::vector<std::vector<double>>& rDF
    , bool isModifyStream);

  void AddNode(
      std::size_t x
    , std::size_t y);

  const std::vector<Node>& rGetNodes() const;

 private:
  AbstractCollisionModel* mpCollisionModel;
  std::vector<Node> mNodes;
};
}  // namespace iblbm
#endif  // SRC_BOUNDARY_BOUNCEBACKBOUNDARY_HPP_