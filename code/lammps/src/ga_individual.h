#pragma once
#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "ga_vector3.h"
#include <vector>
#include <math.h>
#include <random>

class Population;

class Individual
{
public:
	std::vector <double> chromosome;

	Population* population;

	double fitness; //closer to zero is better

	Vector3 upperBounds, lowerBounds;

	std::default_random_engine& defEngine;

	Individual(Vector3 lowerBounds, Vector3 upperBounds, std::default_random_engine& defaultEngine, Population* population_);

	void SetChromosome(double dataArray[]);

	void RandomizeChromosome();

	void RandomizeCurrentPosition();

	void SetFitness(double fitness);

	void Mutate();

	void InitFitnessCalculation(); //for Debugging only

	friend void swap(Individual &first, Individual &second)
	{
		// enable ADL (not necessary in our case, but good practice)
		using std::swap;

		// by swapping the members of two objects,
		// the two objects are effectively swapped
		swap(first.chromosome, second.chromosome);
		swap(first.fitness, second.fitness);
		swap(first.upperBounds, second.upperBounds);
		swap(first.lowerBounds, second.lowerBounds);
		swap(first.defEngine, second.defEngine);
	}

	Individual& operator=(Individual rhs)
	{
		swap(*this, rhs);
		return *this;
	}

};

inline bool operator==(const Individual& lhs, const Individual& rhs)
{
	if (lhs.fitness == rhs.fitness) return true;
	else return false;
}
inline bool operator!=(const Individual& lhs, const Individual& rhs)
{
	if (lhs.fitness != rhs.fitness) return true;
	else return false;
}
inline bool operator< (const Individual& lhs, const Individual& rhs)
{
	if (lhs.fitness < rhs.fitness) return true;
	else return false;
}
inline bool operator> (const Individual& lhs, const Individual& rhs)
{
	if (lhs.fitness > rhs.fitness) return true;
	else return false;
}
inline bool operator<=(const Individual& lhs, const Individual& rhs)
{
	if (lhs.fitness <= rhs.fitness) return true;
	else return false;
}
inline bool operator>=(const Individual& lhs, const Individual& rhs)
{
	if (lhs.fitness >= rhs.fitness) return true;
	else return false;
}

#endif
