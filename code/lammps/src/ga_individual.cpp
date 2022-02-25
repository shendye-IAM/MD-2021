#include "ga_individual.h"
#include "ga_population.h"

#include <float.h>

Individual::Individual(Vector3 lowerBounds, Vector3 upperBounds, std::default_random_engine& defaultEngine,
                       Population* population_) : defEngine(defaultEngine), population(population_){
	fitness = DBL_MAX;
	this->chromosome = std::vector<double>(3*population->numAtoms);
	this->upperBounds = upperBounds;
	this->lowerBounds = lowerBounds;
}

void Individual::SetChromosome(double dataArray[]){
	//unsigned dataArraySize = sizeof(dataArray) / sizeof(double);
	chromosome.assign(&dataArray[0], &dataArray[3*population->numAtoms]);
}

void Individual::RandomizeChromosome(){
	Vector3 pos = Vector3();
	for (int i = 0; i < 3*population->numAtoms; i+=3) {
		pos.RandomVector(lowerBounds, upperBounds, defEngine);
		chromosome[i] = pos.x;
		chromosome[i + 1] = pos.y;
		chromosome[i + 2] = pos.z;
	}
}

void Individual::RandomizeCurrentPosition(){
	Vector3 pos = Vector3();
	if (population->randomInit)
	{
		for (int i = 0; i < 3 * population->numAtoms; i += 3) {
			pos.RandomVector(lowerBounds, upperBounds, defEngine);
			chromosome[i] = pos.x;
			chromosome[i + 1] = pos.y;
			chromosome[i + 2] = pos.z;
		}
	} else {

		for (int i = 0; i < 3 * population->numAtoms; i += 3) {
			double epsilon = population->dmax;  // dmax can be set by min_modify command
			Vector3 local_upperBounds = Vector3(chromosome[i], chromosome[i + 1], chromosome[i + 2]);
			Vector3 local_lowerBounds = Vector3(chromosome[i], chromosome[i + 1], chromosome[i + 2]);
			if (local_upperBounds.x + epsilon < upperBounds.x) local_upperBounds.x += epsilon;
			if (local_upperBounds.y + epsilon < upperBounds.y) local_upperBounds.y += epsilon;
			if (local_upperBounds.z + epsilon < upperBounds.z) local_upperBounds.z += epsilon;
			if (local_lowerBounds.x - epsilon > lowerBounds.x) local_lowerBounds.x -= epsilon;
			if (local_lowerBounds.y - epsilon > lowerBounds.y) local_lowerBounds.y -= epsilon;
			if (local_lowerBounds.z - epsilon > lowerBounds.z) local_lowerBounds.z -= epsilon;

			pos.RandomVector(local_lowerBounds, local_upperBounds, defEngine);
			chromosome[i] = pos.x;
			chromosome[i + 1] = pos.y;
			chromosome[i + 2] = pos.z;
		}
	}
}

void Individual::SetFitness(double fitness){
	this->fitness = fitness;
}

void Individual::Mutate(){
	Vector3 pos = Vector3();
	std::uniform_real_distribution<double> dblDistro(0, 1);
	for (int i = 0; i < 3 * population->numAtoms; i += 3) {
		if (dblDistro(defEngine) < population->k) {
			double epsilon = population->dmax;// dmax can be set by min_modify command
			Vector3 local_upperBounds = Vector3(chromosome[i], chromosome[i + 1], chromosome[i + 2]);
			Vector3 local_lowerBounds = Vector3(chromosome[i], chromosome[i + 1], chromosome[i + 2]);
			if (local_upperBounds.x + epsilon < upperBounds.x) local_upperBounds.x += epsilon;
			if (local_upperBounds.y + epsilon < upperBounds.y) local_upperBounds.y += epsilon;
			if (local_upperBounds.z + epsilon < upperBounds.z) local_upperBounds.z += epsilon;
			if (local_lowerBounds.x - epsilon > lowerBounds.x) local_lowerBounds.x -= epsilon;
			if (local_lowerBounds.y - epsilon > lowerBounds.y) local_lowerBounds.y -= epsilon;
			if (local_lowerBounds.z - epsilon > lowerBounds.z) local_lowerBounds.z -= epsilon;
			pos.RandomVector(local_lowerBounds, local_upperBounds, defEngine);
			chromosome[i] = pos.x;
			chromosome[i + 1] = pos.y;
			chromosome[i + 2] = pos.z;
		}
	}
}

void Individual::InitFitnessCalculation(){
	//Debug
}
