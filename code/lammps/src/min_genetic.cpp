#include "min_genetic.h"
#include "update.h"

/* ---------------------------------------------------------------------- */

LAMMPS_NS::MinGenetic::MinGenetic(LAMMPS *lmp) : MinGeneticParent(lmp){
}

/* ---------------------------------------------------------------------- */

void LAMMPS_NS::MinGenetic::init()
{
	Min::init();

	dt = update->dt;
	last_negative = update->ntimestep;
}

/* ---------------------------------------------------------------------- */

void LAMMPS_NS::MinGenetic::ga_setup()
{
	//Nothing to setup
}

/* ---------------------------------------------------------------------- */

void LAMMPS_NS::MinGenetic::CalculateFitness(Population &population) {

	//settings lammps atom positions to chromosomes
	for (int i = 0; i < population.numIndividuals; i++) {
		for (int j = 0; j < nvec; j++) {
			xvec[j] = population.individuals[i].chromosome[j];
		}

		ecurrent = energy_force(0);

		population.individuals[i].SetFitness(ecurrent);
		population.individuals[i].SetChromosome(xvec);
	}
}
