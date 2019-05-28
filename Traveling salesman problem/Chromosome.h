#pragma once
#include "City.h"
#include <vector>
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
	void mutate();
	void empty_chromosome();
	void order_crossover(Chromosome parent_1, Chromosome parent_2);
};

