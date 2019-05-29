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

void Chromosome::make_empty_chromosome() {
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

void Chromosome::inversion_mutate()
{
	int x, y;
	x = rand() % (this->city_vector.size() - 1);
	do {
		y = rand() % (this->city_vector.size() - 1);
	} while (x == y);
	if (x > y) {
		std::swap(x, y);
	}
	while (x < y) {
		if (x != y) {
			std::iter_swap(this->city_vector.begin() + x, this->city_vector.begin() + y);
			x++;
			y--;
		}
	}
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
	this->make_empty_chromosome();
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

void Chromosome::edge_recombination_crossover(Chromosome parent_1, Chromosome parent_2)
{
	int j = 0;
	neighbour_vector_iniciation(parent_1.city_vector.size());
	neighbour_vector_injection(parent_1, parent_2);
	this->make_empty_chromosome();
	if (rand() % 1 == 1) {
		this->city_vector[0] = parent_1.city_vector[0];
	}
	else {
		this->city_vector[0] = parent_2.city_vector[0];
	}
	this->delete_from_neighbour_vector(this->city_vector[0].number);
	int child_index = 1;
	while (this->neighbours.size() != 0) {
		int min_size = 5;
		int index = -1;
		for (int i = 0; i < this->neighbours.size(); i++) {
			if (this->neighbours[i].neighbour_numbers.size() < min_size) {
				min_size = this->neighbours[i].neighbour_numbers.size();
				index = i;
				this->least_ful_indexes.clear();
			}
			else if (min_size== this->neighbours[i].neighbour_numbers.size()) {
				this->least_ful_indexes.push_back(i);
			}
		}
		if (this->least_ful_indexes.size() > 0) {
			this->least_ful_indexes.push_back(index);
			index = this->least_ful_indexes[rand() % least_ful_indexes.size()];
			this->least_ful_indexes.clear();
		}
		int j = 0;
		while (parent_1.city_vector[j].number != this->neighbours[index].city_number) {
			j++;
		}
		this->city_vector[child_index] = parent_1.city_vector[j];
		this->delete_from_neighbour_vector(this->city_vector[child_index].number);
		child_index++;
	}
	this->calculate_distance();
	this->calculate_fitness();
	return;
}


void Chromosome::neighbour_vector_iniciation(int size)
{
	for (int i = 0; i < size; i++) {
		Neighbours neighbour;
		neighbour.city_number = i;
		this->neighbours.push_back(neighbour);
	}
}

void Chromosome::neighbour_vector_injection(Chromosome parent_1, Chromosome parent_2)
{
	int j = 0;
	int number_of_city;
	std::vector<int>::iterator it;
	for (int i = 0; i < parent_1.city_vector.size(); i++) {
		number_of_city = parent_1.city_vector[i].number;
		while (this->neighbours[j].city_number != number_of_city) {
			j++;
		}
		if (i != 0) {
			if (this->neighbours[j].neighbour_numbers.size() != 0) {
				it = std::find(this->neighbours[j].neighbour_numbers.begin(), this->neighbours[j].neighbour_numbers.end(), parent_1.city_vector[i - 1].number);
				if ((it == this->neighbours[j].neighbour_numbers.end()) && (this->neighbours[j].neighbour_numbers[this->neighbours[j].neighbour_numbers.size() - 1] != (parent_1.city_vector[i - 1].number))) {
					this->neighbours[j].neighbour_numbers.push_back(parent_1.city_vector[i - 1].number);
				}
			}
			else {
				this->neighbours[j].neighbour_numbers.push_back(parent_1.city_vector[i - 1].number);
			}
		}
		if (i != (parent_1.city_vector.size() - 1)) {
			if (this->neighbours[j].neighbour_numbers.size() != 0) {
				it = std::find(this->neighbours[j].neighbour_numbers.begin(), this->neighbours[j].neighbour_numbers.end(), parent_1.city_vector[i + 1].number);
				if ((it == this->neighbours[j].neighbour_numbers.end()) && (this->neighbours[j].neighbour_numbers[this->neighbours[j].neighbour_numbers.size() - 1] != (parent_1.city_vector[i + 1].number))) {
					this->neighbours[j].neighbour_numbers.push_back(parent_1.city_vector[i + 1].number);
				}
			}
			else {
				this->neighbours[j].neighbour_numbers.push_back(parent_1.city_vector[i + 1].number);
			}
		}
		j = 0;
		number_of_city = parent_2.city_vector[i].number;
		while (this->neighbours[j].city_number != number_of_city) {
			j++;
		}
		if (i != 0) {
			if (this->neighbours[j].neighbour_numbers.size() != 0) {
				it = std::find(this->neighbours[j].neighbour_numbers.begin(), this->neighbours[j].neighbour_numbers.end(), parent_2.city_vector[i - 1].number);
				if ((it == this->neighbours[j].neighbour_numbers.end()) && (this->neighbours[j].neighbour_numbers[this->neighbours[j].neighbour_numbers.size() - 1] != (parent_2.city_vector[i - 1].number))) {
					this->neighbours[j].neighbour_numbers.push_back(parent_2.city_vector[i - 1].number);
				}
			}
			else {
				this->neighbours[j].neighbour_numbers.push_back(parent_2.city_vector[i - 1].number);
			}
		}
		if (i != (parent_2.city_vector.size() - 1)) {
			if (this->neighbours[j].neighbour_numbers.size() != 0) {
				it = std::find(this->neighbours[j].neighbour_numbers.begin(), this->neighbours[j].neighbour_numbers.end(), parent_2.city_vector[i + 1].number);
				if ((it == this->neighbours[j].neighbour_numbers.end()) && (this->neighbours[j].neighbour_numbers[this->neighbours[j].neighbour_numbers.size() - 1] != (parent_2.city_vector[i + 1].number))) {
					this->neighbours[j].neighbour_numbers.push_back(parent_2.city_vector[i + 1].number);
				}
			}
			else {
				this->neighbours[j].neighbour_numbers.push_back(parent_2.city_vector[i + 1].number);
			}
		}
		j = 0;
	}
}

void Chromosome::delete_from_neighbour_vector(int number_of_city)
{
	std::vector<int>::iterator it;
	std::vector<Neighbours>::iterator it_neighbour;
	int i = 0;
	if (this->neighbours.size() == 1) {
		this->neighbours.clear();
		return;
	}
	while (this->neighbours[i].city_number != number_of_city) {
		i++;
	}
	it_neighbour = this->neighbours.begin() + i;
	this->neighbours.erase(it_neighbour);
	for (int j = 0; j < this->neighbours.size(); j++) {
		it = std::find(this->neighbours[j].neighbour_numbers.begin(), this->neighbours[j].neighbour_numbers.end(), number_of_city);
		if ((it != this->neighbours[j].neighbour_numbers.end()) || (this->neighbours[j].neighbour_numbers[this->neighbours[j].neighbour_numbers.size() - 1] == number_of_city)) {
			if (this->neighbours[j].neighbour_numbers.size() != 1) {
				this->neighbours[j].neighbour_numbers.erase(it);
			}
			else {
				this->neighbours[j].neighbour_numbers.clear();
			}
		}
	}
}
