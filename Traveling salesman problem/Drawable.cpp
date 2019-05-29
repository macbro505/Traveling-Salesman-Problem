#include "Drawable.h"


Drawable::Drawable()
{
	//sf::RenderWindow window(sf::VideoMode(1920, 1080), "Traveling salesman problem");
	//settings.antialiasingLevel = 16;
	window.create(sf::VideoMode(SCREEN_WIDHT, SCREEN_HEIGHT), "Traveling salesman problem", sf::Style::Default, settings);
	// Load from a font file on disk
	if (!Font.loadFromFile("Arial_Black.ttf"))
	{
		std::cout << "Font error" << std::endl;
	}
	text.setFont(Font);
	text.setCharacterSize(14);
	//texture.loadFromFile("quick.jpg");
	texture.loadFromFile("tlo2.jpg");
	sf::Vector2u size = texture.getSize();
	texture.setSmooth(true);
	sprite.setTexture(texture);
	sprite.setScale(float(SCREEN_WIDHT) / float(size.x), float(SCREEN_HEIGHT) / float(size.y));
	//sprite.setOrigin(size.x / 2, size.y / 2);
}


Drawable::~Drawable()
{
}

void Drawable::draw_city(City city)
{
	text_string ="("+ std::to_string(city.x) + "," + std::to_string(city.y)+")";
	text.setString(text_string);
	text.setPosition(sf::Vector2f(city.coords.x-25, city.coords.y-20));
	text.setFillColor(city.shape.getFillColor());
	window.draw(text);
	window.draw(city.shape);

}

void Drawable::draw_link(std::vector <City> cities, int first, int second)
{
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(cities[first].coords.x + 7, cities[first].coords.y + 7)),
		sf::Vertex(sf::Vector2f(cities[second].coords.x + 7, cities[second].coords.y + 7))
	};
	window.draw(line, 2, sf::Lines);
}

void Drawable::draw_scene(Chromosome to_draw, int generation, int number_of_generations, sf::Color colour)
{
	window.clear();
	window.draw(sprite);
	for (int i = 0; i < to_draw.city_vector.size(); i++) {
		if (i != (to_draw.city_vector.size() - 1)) {
			draw_link(to_draw.city_vector, i, i + 1);
		}
		else {
			draw_link(to_draw.city_vector, i, 0);
		}
	}
	for (auto i = 0; i < to_draw.city_vector.size(); i++) {
		draw_city(to_draw.city_vector[i]);
	}
	if (colour == sf::Color::Green) {
		text_string = "Current generation: " + std::to_string(generation) + " out of: " + std::to_string(number_of_generations) + " generations" + "			Total distance: " + std::to_string(to_draw.distance) + "		Fitness: " + std::to_string(to_draw.fitness);
		text.setString(text_string);
		//text.setPosition(sf::Vector2f(1100, 20));
		text.setPosition(sf::Vector2f(SCREEN_WIDHT - 920, 20));
		text.setFillColor(colour);
	}
	else {
		text_string = "TERMINATED				Current generation: " + std::to_string(generation) + " out of: " + std::to_string(number_of_generations) + " generations" + "			Total distance: " + std::to_string(to_draw.distance) + "		Fitness: " + std::to_string(to_draw.fitness);
		text.setString(text_string);
		//text.setPosition(sf::Vector2f(1100, 20));
		text.setPosition(sf::Vector2f(SCREEN_WIDHT - 1100, 20));
		text.setFillColor(colour);
	}
	window.draw(text);
	window.display();
}



void Drawable::main_loop(std::vector <City> cities)
{
	bool terminated = false;
	Population children(NUMBER_OF_CHROMOSOMES, cities.size());
	Population population(NUMBER_OF_CHROMOSOMES, cities.size());
	population.get_random_population(cities);
	Elite_Chromosome elite_chrom;
	int index = population.get_best_fitness();

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (!terminated) {
			draw_scene(population.chromosome_vector[index], population.generation, population.generation, sf::Color::Green);
			elite_chrom.add_new_elite_chromosome(population.chromosome_vector[index], population.generation);
		}
		else {
			draw_scene(elite_chrom.show_best_chromosome(), elite_chrom.show_best_generation(), population.generation, sf::Color::Red);
		}
		//

		if (elite_chrom.check_termination_condition() == false) {
			children.make_new_generation(population);
			population.swap_children_with_parents(children);
		}
		else {
			terminated = true;
		}
	}
}
