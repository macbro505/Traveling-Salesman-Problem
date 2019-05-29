#pragma once
#include "City.h"
#include <vector>
#include <algorithm>
struct Neighbours {
	int city_number;
	std::vector <int> neighbour_numbers;
};

class Chromosome
{
public:
	std::vector <City> city_vector;
	std::vector <int> available_cities;
	std::vector <Neighbours> neighbours;
	std::vector <int> least_ful_indexes;
	double distance;
	double fitness;

	Chromosome();
	Chromosome(int ammount_of_cities);
	~Chromosome();
	void random_chromosome(std::vector <City> all_cities);
	void calculate_distance();
	void calculate_fitness();
	void inversion_mutate();
	void make_empty_chromosome();
	void order_crossover(Chromosome parent_1, Chromosome parent_2);
	void edge_recombination_crossover(Chromosome parent_1, Chromosome parent_2);
	void neighbour_vector_iniciation(int size);
	void neighbour_vector_injection(Chromosome parent_1, Chromosome parent_2);
	void delete_from_neighbour_vector(int number_of_city);
};

