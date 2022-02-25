#ifdef MINIMIZE_CLASS
// clang-format off
MinimizeStyle(ga_divergence,MinGeneticDivergence);
// clang-format on
#else

#ifndef LMP_MIN_GENETIC_DIV_H
#define LMP_MIN_GENETIC_DIV_H

#include <vector>
#include "min_genetic_parent.h"

namespace LAMMPS_NS {

class MinGeneticDivergence : public MinGeneticParent {
public:
	MinGeneticDivergence(class LAMMPS *);
	void init();
	void ga_setup();
	void CalculateFitness(Population& population);
	double VectorDistance(std::vector<double> first, std::vector<double> second);
};

}    // namespace LAMMPS_NS

#endif
#endif
