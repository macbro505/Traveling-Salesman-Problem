// Traveling salesman problem.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "City.h"
#include "Drawable.h"
#include <vector>
#include "Chromosome.h"

int main()
{
	srand(time(NULL));
	Drawable main_drawable;
	std::vector <City> city_vector;
	for (int i = 0; i < NUMBER_OF_CITIES; i++) {
		City A(sf::Color::Blue, i);
		city_vector.push_back(A);
	}
	main_drawable.main_loop(city_vector);

	return 0;
}