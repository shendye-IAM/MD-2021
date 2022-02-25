#include "ga_population.h"

Population::Population(int numIndividuals, int numAtoms, double p, double k, double dmax, int elites, bool randomInit, Vector3 lowerBounds, Vector3 upperBounds,
                       std::default_random_engine &defEngine) :
	defEngine(defEngine){
	this->numIndividuals = numIndividuals;
	this->p = p;
	this->numAtoms = numAtoms;
	this->k = k;
	this->dmax = dmax;
	this->lowerBounds = lowerBounds;
	this->upperBounds = upperBounds;
	this->randomInit = randomInit;
	this->elites = elites;
}

void Population::SetPopulation(double dataArray[]){
	Individual individual = Individual(lowerBounds, upperBounds, defEngine, this);
	individual.SetChromosome(dataArray);
	for (int i = 0; i < numIndividuals; i++)
	{
		individuals.push_back(individual);
	}
}

void Population::RandomizePopulation(){
	//the original positions are preserved in the first individual
	for (int i = 1; i < numIndividuals; i++)
	{
		individuals[i].RandomizeCurrentPosition();
	}
}

void Population::Selection(){
	TournamentSelection();
}

void Population::TournamentSelection(){
	//2-way tournament
	//elites must be at beginning of the individuals array
	selections.clear();
	const int t_k = 2;
	int bestContender;
	std::uniform_int_distribution<int> dblDistro(elites, numIndividuals-1);
	for (int i = elites; i < numIndividuals; i++) {
		std::pair<int, int> selection;
		bestContender = dblDistro(defEngine);
		for (int j = 0; j < t_k - 1; j++) {
			int contender = dblDistro(defEngine);
			if (individuals[contender] < individuals[bestContender]) bestContender = contender;
		}
		selection.first = bestContender;

		bestContender = dblDistro(defEngine);
		for (int j = 0; j < t_k - 1; j++) {
			int contender = dblDistro(defEngine);
			if (individuals[contender] < individuals[bestContender]) bestContender = contender;
		}
		selection.second = bestContender;

		selections.push_back(selection);
	}
}

void Population::Crossover(){
	std::vector<Individual> temp_individuals = individuals;
	for (int i = elites; i < numIndividuals; i++) {
		temp_individuals[i] = uniformCross(individuals[selections[i - elites].first], individuals[selections[i - elites].second]);
	}
	individuals = temp_individuals;
}

Individual Population::uniformCross(Individual first, Individual second){
	Individual child = first;
	std::uniform_real_distribution<double> dblDistro(0, 1);
	for (int i = 0; i < numAtoms; i++) if (dblDistro(defEngine) < 0.5) child.chromosome[i] = second.chromosome[i];
	return child;
}

void Population::Mutation(){
	//elites must be at beginning of the individuals array
	std::uniform_real_distribution<double> dblDistro(0, 1);
	std::vector<Individual>::iterator it;
	for (int i = elites; i < numIndividuals; i++) {
		if (dblDistro(defEngine) < p) individuals[i].Mutate();
	}
}

void Population::CalculateFitness(){
	//Empty
}

void Population::SortByFitness(){
	std::sort(individuals.begin(), individuals.end());
}

Individual Population::GetFittest(){
	return this->individuals.front();
}

void Population::Print(){
	for (int i=0; i<individuals.size(); i++)
	{
		std::cout << individuals[i].fitness << std::endl;
	}
	std::cout << std::endl;
}
