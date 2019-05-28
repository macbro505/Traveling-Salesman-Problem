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
	//1920×1080
	//sf::RenderWindow window(sf::VideoMode(1920, 1080), "Traveling salesman problem");
	Drawable main_drawable;
	std::vector <City> city_vector;
	City A(sf::Color::Blue, 0);
	City B(sf::Color::Blue, 1);
	City C(sf::Color::Blue, 2);
	City D(sf::Color::Blue, 3);
	City E(sf::Color::Blue, 4);
	City F(sf::Color::Blue, 5);
	City G(sf::Color::Blue, 6);
	City H(sf::Color::Blue, 7);
	City I(sf::Color::Blue, 8);
	City J(sf::Color::Blue, 9);
	city_vector.push_back(A);
	city_vector.push_back(B);
	city_vector.push_back(C);
	city_vector.push_back(D);
	city_vector.push_back(E);
	city_vector.push_back(F);
	city_vector.push_back(G);
	city_vector.push_back(H);
	city_vector.push_back(I);
	city_vector.push_back(J);
	main_drawable.main_loop(city_vector);

//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//		
//		window.clear();
//		window.display();
//	}

	return 0;
}