#include "min_genetic_divergence.h"

#include <cmath>

#include "update.h"

/* ---------------------------------------------------------------------- */

LAMMPS_NS::MinGeneticDivergence::MinGeneticDivergence(LAMMPS *lmp) : MinGeneticParent(lmp){
}

/* ---------------------------------------------------------------------- */

void LAMMPS_NS::MinGeneticDivergence::init(){
	Min::init();

	dt = update->dt;
	last_negative = update->ntimestep;
}

/* ---------------------------------------------------------------------- */

void LAMMPS_NS::MinGeneticDivergence::ga_setup(){
	//Nothing to set up
}

/* ---------------------------------------------------------------------- */

void LAMMPS_NS::MinGeneticDivergence::CalculateFitness(Population &population) {
	double penalty = 0;
	double dx = population.upperBounds.x - population.lowerBounds.x;
	double dy = population.upperBounds.y - population.lowerBounds.y;
	double dz = population.upperBounds.z - population.lowerBounds.z;
	double normalization_factor = std::sqrt(nvec/3*(dx*dx + dy*dy + dz*dz));

	//settings lammps atom positions to chromosomes
	for (int i = 0; i < population.numIndividuals; i++) {
		for (int j = 0; j < nvec; j++) xvec[j] = population.individuals[i].chromosome[j];

		ecurrent = energy_force(0);
		penalty = normalization_factor/pow(VectorDistance(population.individuals[i].chromosome, best),0.1);
		population.individuals[i].SetFitness(ecurrent*penalty);
		population.individuals[i].SetChromosome(xvec);
	}
}

/* ---------------------------------------------------------------------- */

double LAMMPS_NS::MinGeneticDivergence::VectorDistance(std::vector<double> first, std::vector<double> second){
	int n = first.size();
	double distance = 0;
	for(int i=0; i<n; i++) {
		distance += (first[i] - second[i])*(first[i] - second[i]);
	}
	return std::sqrt(distance);
}
