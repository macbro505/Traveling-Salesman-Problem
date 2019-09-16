#pragma once
#include "City.h"
#include <vector>
#include <iostream>
#include "Chromosome.h"
#include "Population.h"
#include "Elite_Chromosome.h"
#include <windows.h>
#include <fstream>
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
	void draw_scene(Chromosome to_draw, int generation, int number_of_generations, sf::Color colour);
	void main_loop(std::vector <City> cities);
	void save_result(Elite_Chromosome elite_chrom);
};

