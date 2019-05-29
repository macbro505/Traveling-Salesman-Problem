#pragma once
#include "City.h"
#include <vector>
#include <algorithm>
class Chromosome
{
public:
	std::vector <City> city_vector;
	std::vector <int> available_cities;
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
};

