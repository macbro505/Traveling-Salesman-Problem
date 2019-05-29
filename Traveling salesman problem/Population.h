#pragma once
#include "Chromosome.h"
#define NO_PARENT -1
#define NUMBER_OF_PARTICIPANTS 10
#define MUTATION_OCCURENCE_PERCENTAGE 15
class Population
{

public:
	std::vector<Chromosome> chromosome_vector;
	int generation;
	int population_size;
	Population();
	Population(int population_size, int chromosome_size);
	~Population();
	Chromosome add_new_chromosome(int size);
	void next_gen();
	void set_size(int size);
	int get_best_fitness();
	void get_random_population(std::vector <City> all_cities);
	void make_new_generation(Population parents);
	void swap_children_with_parents(Population &children);
	int tournament_selection_parent(int number_of_participants, int first_parent_index);
};

