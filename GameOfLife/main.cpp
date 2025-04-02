#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "GameOfLife.h"


int main()
{
	// Wizualna reprezentacja gry w ¿ycie

	double probability = 0.50;
	bool game_running = false;

	GameOfLife game(100, 100, 8, probability);
	game.setRunning(game_running);

	sf::RenderWindow window(sf::VideoMode(800, 800), "Game of Life");
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{

			// Closing event
			case sf::Event::Closed:
				window.close();
				break;

			// Key pressed events
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				// Close the window
				case sf::Keyboard::Escape:
					window.close();
					break;

				// Pause/Unpause the game
				case sf::Keyboard::Space:
					game_running = !game_running;
					game.setRunning(game_running);
					break;

				// Reset the simulation with a new initial state
				case sf::Keyboard::R:
					game.reset(probability);
					break;

				// Reset the simulation with an empty initial state
				case sf::Keyboard::E:
					game.reset(0.0);
					break;

				default:
					break;
				}
				break;

			// Mouse button pressed events
			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					game.flipPixelState(
						sf::Mouse::getPosition(window).x,
						sf::Mouse::getPosition(window).y
					);
					break;

				default:
					break;
				}
				break;

			default:
				break;
			}
		}

		game.update();

		std::vector<sf::RectangleShape> pixels = game.getLivePixels();

		window.clear();
		for (auto& pixel : pixels)
			window.draw(pixel);
		window.display();
	}

	// Zadanie 2
	// Kilka wykresów przy ustalonym p0 = 0.5
	/*game.setRunning(false);
	game.reset(0.5);
	game.saveDensityDataToFile("./density1_05.txt", 1000);
	game.reset();
	game.saveDensityDataToFile("./density2_05.txt", 1000);
	game.reset();
	game.saveDensityDataToFile("./density3_05.txt", 1000);
	game.reset();
	game.saveDensityDataToFile("./density4_05.txt", 1000);*/

	// Skrajne przebiegi dla p0 = 0.05 i p0 = 0.95
	/*game.reset(0.05);
	game.saveDensityDataToFile("./density_005.txt", 100);

	game.reset(0.95);
	game.saveDensityDataToFile("./density_095.txt", 100);*/

	// Wartoœæ graniczna gêstoœci ¿ywych komórek dla czasów t > 1000
	/*game.reset(0.1);
	game.saveDensityDataToFile("./density_long_01.txt", 2000);

	game.reset(0.3);
	game.saveDensityDataToFile("./density_long_03.txt", 2000);

	game.reset(0.6);
	game.saveDensityDataToFile("./density_long_06.txt", 2000);

	game.reset(0.75);
	game.saveDensityDataToFile("./density_long_075.txt", 2000);

	game.reset(0.8);
	game.saveDensityDataToFile("./density_long_08.txt", 2000);*/

	// Zadanie 3
	/*GameOfLife game_10x10(10, 10, 1, 0.5);
	game_10x10.saveDensityDataToFile("./density_10x10.txt", 1000, 100);

	std::cout << "10x10 DONE\n";

	GameOfLife game_100x100(100, 100, 1, 0.5);
	game_100x100.saveDensityDataToFile("./density_100x100.txt", 1000, 100);

	std::cout << "100x100 DONE\n";

	GameOfLife game_200x200(200, 200, 1, 0.5);
	game_200x200.saveDensityDataToFile("./density_200x200.txt", 1000, 100);

	std::cout << "200x200 DONE\n";*/


	return 0;
}