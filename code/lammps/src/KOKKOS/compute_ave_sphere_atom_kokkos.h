/* -*- c++ -*- ----------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   https://www.lammps.org/, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#ifdef COMPUTE_CLASS

ComputeStyle(ave/sphere/atom/kk,ComputeAveSphereAtomKokkos<LMPDeviceType>)
ComputeStyle(ave/sphere/atom/kk/device,ComputeAveSphereAtomKokkos<LMPDeviceType>)
ComputeStyle(ave/sphere/atom/kk/host,ComputeAveSphereAtomKokkos<LMPHostType>)

#else

#ifndef LMP_COMPUTE_AVE_SPHERE_ATOM_KOKKOS_H
#define LMP_COMPUTE_AVE_SPHERE_ATOM_KOKKOS_H

#include "compute_ave_sphere_atom.h"
#include "kokkos_type.h"

namespace LAMMPS_NS {

struct TagComputeAveSphereAtom{};

template<class DeviceType>
class ComputeAveSphereAtomKokkos : public ComputeAveSphereAtom {
 public:
  typedef DeviceType device_type;
  typedef ArrayTypes<DeviceType> AT;

  ComputeAveSphereAtomKokkos(class LAMMPS *, int, char **);
  virtual ~ComputeAveSphereAtomKokkos();
  void init();
  void compute_peratom();

  KOKKOS_INLINE_FUNCTION
  void operator()(TagComputeAveSphereAtom, const int&) const;

 private:
  typename AT::t_x_array_randomread x;
  typename AT::t_v_array_randomread v;
  typename ArrayTypes<DeviceType>::t_int_1d mask;

  typename AT::t_neighbors_2d d_neighbors;
  typename AT::t_int_1d_randomread d_ilist;
  typename AT::t_int_1d_randomread d_numneigh;

  DAT::tdual_float_2d k_result;
  typename AT::t_float_2d d_result;
};

}

#endif
#endif

/* ERROR/WARNING messages:

*/
