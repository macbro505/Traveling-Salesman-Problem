#pragma once
#include "Chromosome.h"
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
	bool check_termination_condition();
	Chromosome show_best_chromosome();
	int show_best_generation();
};

