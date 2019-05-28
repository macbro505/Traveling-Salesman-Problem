#include "City.h"
#include <cmath>


City City::empty_city()
{
	return City();
}

City::City(sf::Color color, int number)
{
	shape.setRadius(10.f);
	shape.setFillColor(color);
	draw_coords();
	this->coords.x = x;
	this->coords.y = y;
	shape.setPosition(coords);
	this->number = number;
}

City::City()
{
	shape.setRadius(10.f);
	shape.setFillColor(sf::Color::Black);
	this->coords.x = 0.f;
	this->coords.y = 0.f;
	shape.setPosition(coords);
	this->number = 0;
}



void City::draw_coords()
{
	x = (rand() % 1820)+30;
	y = (rand() % 980)+30;
}

double City::calculate_distance(City destination)
{
	return sqrt(pow(double(this->x - destination.x), 2) + pow(double(this->y - destination.y), 2));
}


City::~City()
{
}
