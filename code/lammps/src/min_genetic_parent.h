#ifndef LMP_MIN_GENETIC_PARENT_H
#define LMP_MIN_GENETIC_PARENT_H

#include <vector>

#include "min.h"
#include "ga_population.h"

namespace LAMMPS_NS {

class MinGeneticParent : public Min {
public:
	MinGeneticParent(class LAMMPS *);
	virtual void init() = 0;
	virtual void ga_setup() = 0;
	void setup_style();
	void reset_vectors();
	int iterate(int);
	virtual void CalculateFitness(Population&) = 0;
	void Sort(Population &population);

protected:
	double dt;
	bigint last_negative;
	bigint ntimestep;
	std::vector<double> best;
};

}    // namespace LAMMPS_NS

#endif
