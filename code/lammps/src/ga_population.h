#pragma once
#ifndef POPULATION_H
#define POPULATION_H

#include "ga_individual.h"
#include "ga_vector3.h"
#include <vector>
#include <iostream>
#include <algorithm>

class Population
{
public:
	std::vector <Individual> individuals;

	std::vector<std::pair<int, int>> selections;

	int numIndividuals;

	int numAtoms;

	double p; //probability of mutation of individual

	double k;

	double dmax;

	int elites; //number of best individuals preserved for next generation

	bool randomInit;

	Vector3 lowerBounds;

	Vector3 upperBounds;

	std::default_random_engine& defEngine;

	Population(int numIndividuals, int numAtoms, double p, double k, double dmax, int elites, bool randomInit, Vector3 lowerBounds,
             Vector3 upperBounds,
             std::default_random_engine &defEngine);

	void SetPopulation(double dataArray[]);

	void RandomizePopulation();

	void Selection();

	void TournamentSelection();

	void Crossover();

	Individual uniformCross(Individual first, Individual second);

	void Mutation();

	void CalculateFitness(); 

	void SortByFitness();

	Individual GetFittest();

	void Print();
};

#endif
