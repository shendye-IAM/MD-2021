#include "min_genetic_parent.h"

#include <cmath>
#include <cstring>

#include "atom.h"
#include "error.h"
#include "force.h"
#include "output.h"
#include "timer.h"
#include "universe.h"
#include "update.h"
#include "domain.h"
#include "min_cg.h"

using namespace LAMMPS_NS;

// EPS_ENERGY = minimum normalization for energy tolerance

#define EPS_ENERGY 1.0e-8

#define DELAYSTEP 5

/* ---------------------------------------------------------------------- */

MinGeneticParent::MinGeneticParent(LAMMPS *lmp) : Min(lmp){
}

/* ---------------------------------------------------------------------- */

void MinGeneticParent::setup_style()
{
	double **v = atom->v;
	int nlocal = atom->nlocal;

	for (int i = 0; i < nlocal; i++)
		v[i][0] = v[i][1] = v[i][2] = 0.0;
}

/* ----------------------------------------------------------------------
   set current vector lengths and pointers
   called after atoms have migrated
   ------------------------------------------------------------------------- */

void MinGeneticParent::reset_vectors()
{
	// atomic dof

	nvec = 3 * atom->nlocal;
	if (nvec) xvec = atom->x[0];
	if (nvec) fvec = atom->f[0];
}

/* ----------------------------------------------------------------------
   minimization via Genetic Algorithm
   ------------------------------------------------------------------------- */

int MinGeneticParent::iterate(int maxiter)
{
	int flag,flagall;
	ga_setup();
	atom->sortfreq = 0;

	alpha_final = 0.0;

	/* ----------------------------------------------------------------------
	   Genetic Algorithm Parameters
	   ------------------------------------------------------------------------- */

	int numAtoms = nvec/3;
	bool randomInit = false;
	elites = 2;
	//Get bounding box
	Vector3 upperBounds = Vector3(this->domain->boxhi);
	Vector3 lowerBounds = Vector3(this->domain->boxlo);
	if(this->domain->dimension == 2)
	{
		upperBounds.z = 0;
		lowerBounds.z = 0;
	}

	std::default_random_engine defEngine(time(0));

	Population population = Population(numIndividuals, numAtoms, 1, p, dmax, elites, randomInit, lowerBounds, upperBounds, defEngine);
	population.SetPopulation(xvec);
	if (randomInit) population.RandomizePopulation();

	CalculateFitness(population);
	population.SortByFitness();

	for (int iter = 0; iter < maxiter; iter++) {

		if (timer->check_timeout(niter))
			return TIMEOUT;

		ntimestep = ++update->ntimestep;
		niter++;

		/* ----------------------------------------------------------------------
		   Loop of the Genetic Algorithm
		   ------------------------------------------------------------------------- */

		population.Selection();

		population.Crossover();

		population.Mutation();

		CalculateFitness(population);

		//Sort By Fitness
		Sort(population);

		// output for thermo, dump, restart files

		if (output->next == ntimestep) {
			timer->stamp();
			output->write(ntimestep);
			timer->stamp(Timer::OUTPUT);
		}
	}

	//minimize->cleanup();
	return MAXITER;
}

void LAMMPS_NS::MinGeneticParent::Sort(Population &population)
{
	population.SortByFitness();
	best = population.individuals[0].chromosome;
	for (int j = 0; j < nvec; j++) { xvec[j] = population.individuals[0].chromosome[j]; }
	eprevious = ecurrent;
	//ecurrent = population.individuals[0].fitness;
	ecurrent = energy_force(0);
	neval++;
}
