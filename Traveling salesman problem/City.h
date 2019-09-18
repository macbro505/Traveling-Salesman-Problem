#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Properties.h"
class City
{
public:
	int x;
	int y;
	int number;
	sf::Vector2f coords;
	sf::CircleShape shape;

	City empty_city();
	City(sf::Color color, int number);
	City();
	void draw_coords();
	double calculate_distance(City destination);
	~City();
};

