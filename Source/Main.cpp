#include <iostream>
#include <cstdlib>
#include <SFML\Graphics.hpp>

/*
This project is maintained by the  Community on Hopson97's Discord server.
The people who are currently working together on this are:
    KiddieD,
    Esscoder,
    ans66f,
    DCubix,
    DarkCart,
    RagingRabbit,
    kaizi99,
    Pol_hp
*/

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return EXIT_SUCCESS;
}
