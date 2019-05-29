#pragma once
#include "City.h"
#include <vector>
#include <iostream>
#include "Chromosome.h"
#include "Population.h"
#include "Elite_Chromosome.h"
#include <windows.h>
#define PERCENTAGE_CONDITION -1
#define MAX_NUMBER_CONDITION 1
#define BOTH_CONDITIONS 0
#define NUMBER_OF_CHROMOSOMES 100
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
	void draw_scene(Chromosome to_draw, int generation, int number_of_generations);
	void main_loop(std::vector <City> cities);
};

