#pragma once
#include "Chromosome.h"
#define MAX_PERCENTAGE_OF_NO_IMPROVEMENT_SUCCESIVE_GENERATIONS 80
#define MAX_NUMBER_OF_GENERATIONS 150
#define PERCENTAGE_CONDITION -1
#define MAX_NUMBER_CONDITION 1
#define BOTH_CONDITIONS 0
class Elite_Chromosome
{
public:
	std::vector<Chromosome> elite_chromosome_vector;
	std::vector<int> generation_vector;
	int no_improvement_counter;
	double best_fitness;
	int best_index;
	Elite_Chromosome();
	~Elite_Chromosome();
	void add_new_elite_chromosome(Chromosome new_member, int generation);
	bool check_termination_condition(int condions);
	Chromosome show_best_chromosome();
	int show_best_generation();
};

