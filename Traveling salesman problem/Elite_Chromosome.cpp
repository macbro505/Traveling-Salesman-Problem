#include "Elite_Chromosome.h"



Elite_Chromosome::Elite_Chromosome()
{
	int no_improvement_counter = 0;
	double best_fitness = 0;
}


Elite_Chromosome::~Elite_Chromosome()
{
}

void Elite_Chromosome::add_new_elite_chromosome(Chromosome new_member, int generation)
{
	this->elite_chromosome_vector.push_back(new_member);
	this->generation_vector.push_back(generation);
	if (this->best_fitness < new_member.fitness) {
		this->best_fitness = new_member.fitness;
		this->no_improvement_counter = 0;
		this->best_index = (this->elite_chromosome_vector.size() - 1);
	}
	else {
		this->no_improvement_counter++;
	}
}

bool Elite_Chromosome::check_termination_condition()
{
	if (1 == MAX_NUMBER_CONDITION ) {
		if (this->generation_vector[this->generation_vector.size() - 1] == MAX_NUMBER_OF_GENERATIONS) {
			return true;
		}
	}
	if (1 == PERCENTAGE_CONDITION ) {
		double percentage = ((double(no_improvement_counter) / this->generation_vector.size())* 100);
		if (percentage > MAX_PERCENTAGE_OF_NO_IMPROVEMENT_SUCCESIVE_GENERATIONS && this->generation_vector.size()>15) {
			return true;
		}
	}
	return false;
}

Chromosome Elite_Chromosome::show_best_chromosome()
{
	return this->elite_chromosome_vector[best_index];
}

int Elite_Chromosome::show_best_generation()
{
	return this->generation_vector[best_index];
}
