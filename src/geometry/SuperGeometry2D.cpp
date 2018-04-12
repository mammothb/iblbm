#include "SuperGeometry2D.hpp"

namespace iblbm
{
template<typename T>
SuperGeometry2D<T>::SuperGeometry2D(
    CuboidGeometry2D<T>& rCuboidGeometry
  , LoadBalancer<T>& rLoadBalancer
  , std::size_t overlap/*=2*/)
  :  SuperStructure2D<T>{rCuboidGeometry, rLoadBalancer, overlap},
//    mStatistics(this),
    mOstream{std::cout, "SuperGeometry2D"}
{
  ;
}

template<typename T>
bool* SuperGeometry2D<T>::operator()(
    gsl::index localCuboidIndex
  , gsl::index xIndex
  , gsl::index yIndex
  , gsl::index dataIndex)
{
  return nullptr;
//  return (bool*)&getExtendedBlockGeometry(localCuboidIndex).get(xIndex + this->mOverlap,
//      yIndex + this->mOverlap);
}

template<typename T>
BlockGeometry2D<T>& SuperGeometry2D<T>::rGetExtendedBlockGeometry(
    gsl::index localCuboidIndex)
{
//  mStatistics.getStatisticsStatus() = true;
  return mExtendedBlockGeometries[localCuboidIndex];
}
// explicit instantiation
template class SuperGeometry2D<double>;
}  // namespace iblbm