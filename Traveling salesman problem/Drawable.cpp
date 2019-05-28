#include "Drawable.h"


Drawable::Drawable()
{
	//sf::RenderWindow window(sf::VideoMode(1920, 1080), "Traveling salesman problem");
	//settings.antialiasingLevel = 16;
	window.create(sf::VideoMode(1920, 1080), "Traveling salesman problem", sf::Style::Default, settings);
	// Load from a font file on disk
	if (!Font.loadFromFile("Arial_Black.ttf"))
	{
		std::cout << "Font error" << std::endl;
	}
	text.setFont(Font);
	text.setCharacterSize(12);
	//texture.loadFromFile("quick.jpg");
	texture.loadFromFile("tlo.jpg");
	sf::Vector2u size = texture.getSize();
	sprite.setTexture(texture);
	//sprite.setOrigin(size.x / 2, size.y / 2);
}


Drawable::~Drawable()
{
}

void Drawable::draw_city(City city)
{
	text_string ="("+ std::to_string(city.x) + "," + std::to_string(city.y)+")";
	text.setString(text_string);
	text.setPosition(sf::Vector2f(city.coords.x-20, city.coords.y-15));
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



void Drawable::main_loop(std::vector <City> cities)
{
	int poop = 0;
	Population children(100, cities.size());
	Population population(100, cities.size());
	population.get_random_population(cities);
	int index = population.get_best_fitness();

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(sprite);
		draw_link(population.chromosome_vector[index].city_vector, 0, 1);
		draw_link(population.chromosome_vector[index].city_vector, 1, 2);
		draw_link(population.chromosome_vector[index].city_vector, 2, 3);
		draw_link(population.chromosome_vector[index].city_vector, 3, 4);
		draw_link(population.chromosome_vector[index].city_vector, 4, 5);
		draw_link(population.chromosome_vector[index].city_vector, 5, 6);
		draw_link(population.chromosome_vector[index].city_vector, 6, 7);
		draw_link(population.chromosome_vector[index].city_vector, 7, 8);
		draw_link(population.chromosome_vector[index].city_vector, 8, 9);
		draw_link(population.chromosome_vector[index].city_vector, 9, 0);
		for (auto i = 0; i < population.chromosome_vector[index].city_vector.size(); i++) {
			draw_city(population.chromosome_vector[index].city_vector[i]);
		}
		text_string = "Generation: "+ std::to_string(population.generation) +"			Total distance: " + std::to_string(population.chromosome_vector[index].distance);
		text.setString(text_string);
		text.setPosition(sf::Vector2f(1500,50));
		text.setFillColor(sf::Color::Green);
		window.draw(text);
		window.display();
		//
		if (poop == 0) {
			children.make_new_generation(population);
			//przenies children do populacji i wyzeruj children 
			poop = 1;
		}
	}
}
