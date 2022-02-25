#ifdef MINIMIZE_CLASS
// clang-format off
MinimizeStyle(genetic,MinGenetic);
// clang-format on
#else

#ifndef LMP_MIN_GENETIC_H
#define LMP_MIN_GENETIC_H

#include "min_genetic_parent.h"

namespace LAMMPS_NS {

class MinGenetic : public MinGeneticParent {
public:
	MinGenetic(class LAMMPS *);
	void init();
	void ga_setup();
	void CalculateFitness(Population& population);
};

}    // namespace LAMMPS_NS

#endif
#endif
