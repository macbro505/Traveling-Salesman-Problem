#include "Chromosome.h"



Chromosome::Chromosome()
{
}

Chromosome::Chromosome(int ammount_of_cities)
{
	for (int i = 0; i < ammount_of_cities; i++) {
		this->available_cities.push_back(i);
	}
	this->distance = 0;
}

void Chromosome::empty_chromosome() {
	City temp;
	for (int i = 0; i < this->available_cities.size(); i++) {
		this->city_vector.push_back(temp.empty_city());
	}
}

Chromosome::~Chromosome()
{
}

void Chromosome::random_chromosome(std::vector <City> all_cities)
{
	std::vector<int>::iterator it;
	int random_number;
	int size = available_cities.size();
	while (available_cities.size() != 1) {
		random_number = rand() % size;
		it = std::find(available_cities.begin(), available_cities.end(), random_number);
		if ((it != available_cities.end()) || (available_cities[available_cities.size()-1] == random_number)) {
			available_cities.erase(it);
			this->city_vector.push_back(all_cities[random_number]);
		}
	}
	this->city_vector.push_back(all_cities[available_cities[0]]);
	//available_cities.erase(available_cities.end());
}

void Chromosome::calculate_distance()
{
	for (auto i = 0; i < city_vector.size(); i++) {
		if (i < city_vector.size() - 1) {
			distance += city_vector[i].calculate_distance(city_vector[i + 1]);
		}
		else {
			distance += city_vector[i].calculate_distance(city_vector[0]);
		}
	}
	calculate_fitness();
}

void Chromosome::calculate_fitness()
{
	fitness = (1 / distance)*1000000;
}

void Chromosome::order_crossover(Chromosome parent_1, Chromosome parent_2)
{
	int x, y;
	x = rand() % (parent_1.city_vector.size()-1);
	do {
		y = rand() % (parent_1.city_vector.size()-1);
	} while (x == y);
	if (x > y) {
		std::swap(x, y);
	}
	std::vector<int>::iterator it;
	this->empty_chromosome();
	for (int i = x; i <= y; i++) {
		this->city_vector[i] = parent_1.city_vector[i];
		it = std::find(available_cities.begin(), available_cities.end(), this->city_vector[i].number);
		available_cities.erase(it);
	}
	int j = 0;
	for (int i = 0; i < parent_2.city_vector.size(); i++) {
		if (j == x) {
			if (y < (this->city_vector.size()-1)) {
				j = y + 1;
			}
			else {
				return;
			}
		}
		it = std::find(available_cities.begin(), available_cities.end(), parent_2.city_vector[i].number);
		if ((it != available_cities.end()) || (available_cities[available_cities.size() - 1] == parent_2.city_vector[i].number)) {
			if (available_cities.size() != 1) {
				available_cities.erase(it);
			}
			this->city_vector[j] = parent_2.city_vector[i];
			j++;
			if (j == this->city_vector.size()) {
				this->calculate_distance();
				this->calculate_fitness();
				return;
			}
		}
	}
}
