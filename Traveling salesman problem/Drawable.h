#pragma once
#include "City.h"
#include <vector>
#include <iostream>
#include "Chromosome.h"
#include "Population.h"
class Drawable
{
	sf::ContextSettings settings;
	sf::RenderWindow window;
	sf::Font Font;
	sf::Text text;
	std::string text_string;
	sf::Texture texture;
	sf::Sprite sprite;
	
public:
	Drawable();
	~Drawable();
	void draw_city(City city);
	void draw_link(std::vector <City> cities, int first, int second);
	void main_loop(std::vector <City> cities);
};

