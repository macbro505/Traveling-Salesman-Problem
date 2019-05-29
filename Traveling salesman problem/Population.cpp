#include "Population.h"



Population::Population()
{
}

Population::Population(int pop_size, int chromosome_size)
{
	population_size = pop_size;
	for (int i = 0; i < pop_size; i++) {
		chromosome_vector.push_back(add_new_chromosome(chromosome_size));
	}
}


Population::~Population()
{
}

Chromosome Population::add_new_chromosome(int size)
{
	return Chromosome(size);
}

void Population::next_gen()
{
	generation++;
}

void Population::set_size(int size)
{
	population_size = size;
}

int Population::get_best_fitness()
{
	int index = 0;
	double best_fitness = 0;
	for (int i = 0; i < this->population_size; i++) {
		if (best_fitness < this->chromosome_vector[i].fitness) {
			best_fitness = this->chromosome_vector[i].fitness;
			index = i;
		}
	}
	return index;
}

void Population::get_random_population(std::vector <City> all_cities)
{
	for (int i = 0; i < population_size; i++) {
		this->chromosome_vector[i].random_chromosome(all_cities);
		this->chromosome_vector[i].calculate_distance();
	}
	next_gen();
}

void Population::make_new_generation(Population parents)
{
	int probability_of_mutating = 0;
	int parent_1, parent_2;
	for (int i = 0; i < this->population_size; i++) {
		parent_1 = parents.tournament_selection_parent(NUMBER_OF_PARTICIPANTS, NO_PARENT);
		parent_2 = parents.tournament_selection_parent(NUMBER_OF_PARTICIPANTS, parent_1);
		//tutaj dzieje sie magia nowego crossovera #sponsored
		this->chromosome_vector[i].edge_rcombination_crossover(parents.chromosome_vector[parent_1], parents.chromosome_vector[parent_2]);
		//this->chromosome_vector[i].order_crossover(parents.chromosome_vector[parent_1], parents.chromosome_vector[parent_2]);
		//tutaj dzieje sie magia mutacji 
		probability_of_mutating = rand() % 100;
		if (probability_of_mutating <= MUTATION_OCCURENCE_PERCENTAGE) {
			this->chromosome_vector[i].inversion_mutate();
			this->chromosome_vector[i].calculate_distance();
			this->chromosome_vector[i].calculate_fitness();
		}
	}
}

void Population::swap_children_with_parents(Population &children)
{
	this->chromosome_vector.clear();
	for (int i = 0; i < children.chromosome_vector.size(); i++) {
		this->chromosome_vector.push_back(children.chromosome_vector[i]);
	}
	this->next_gen();
	children.chromosome_vector.clear();
	for (int i = 0; i < population_size; i++) {
		children.chromosome_vector.push_back(add_new_chromosome(this->chromosome_vector[0].city_vector.size()));
	}
}

int Population::tournament_selection_parent(int number_of_participants, int first_parent_index)
{
	int random_number;
	std::vector<int> participants;
	std::vector<int>::iterator it;
	int index = -1;
	double max_fitness = 0;
	int i = 0;
	while(i < number_of_participants) {
		random_number = rand() % this->population_size;
		if (random_number != first_parent_index) {
			it = std::find(participants.begin(), participants.end(), random_number);
			if (participants.size() != 0) {
				if ((it == participants.end()) && (participants[participants.size() - 1] != random_number)) {
					participants.push_back(random_number);
					i++;
				}
			}
			else {
				participants.push_back(random_number);
				i++;
			}
		}
	}
	for (int j = 0; j < number_of_participants; j++) {
		if (this->chromosome_vector[participants[j]].fitness > max_fitness) {
			max_fitness = this->chromosome_vector[participants[j]].fitness;
			index = participants[j];
		}
	}
	return index;
}
