#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>


class GameOfLife
{
  private:
	std::vector<sf::RectangleShape> pixels;
	std::vector<std::vector<bool>> table;
	const int pixel_size = 1;
	const int width = 0;
	const int height = 0;
	double probability = 0;
	bool running = true;

  public:
	/// <summary>Class that simulates the "Game of Life" and allows displaying its state at every iteration through the use of sf::RectangleShape.</summary>
	/// <param name="width">- number of pixels on X axis</param>
	/// <param name="height">- number of pixels on Y axis</param>
	/// <param name="pixel_size">- size of each pixel</param>
	/// <param name="probability">- how likely it is for a pixel to start in an alive state</param>
	GameOfLife(int width, int height, int pixel_size, double probability);

	~GameOfLife() = default;


	void update();

	/// <summary>Sets up a new initial state of the simulation.</summary>
	/// <param name="probability">- how likely it is for a pixel to start in an alive state</param>
	void reset(double probability);

	/// <summary>Sets up a new initial state of the simulation with the same probability.</summary>
	void reset();

	/// <summary>Runs or stops the simulation based on the passed value.</summary>
	void setRunning(bool value) { running = value; }

	/// <summary>Flips the state of a pixel being pointed by the mouse cursor.</summary>
	/// <param name="x">- mouse position on X axis</param>
	/// <param name="y">- mouse position on Y axis</param>
	void flipPixelState(const int x, const int y);

	/// <summary>Runs the simulation without its visual representation and saves the density of living pixels at every iteration to a file.</summary>
	/// <param name="path">- path to the file</param>
	/// <param name="iterations">- number of times the simulation is updated</param>
	void saveDensityDataToFile(const std::string& path, unsigned iterations);

	/// <summary>Runs many simulations without their visual representations and saves the density of living pixels to a file at the end of each simulation.</summary>
	/// <param name="path">- path to the file</param>
	/// <param name="iterations">- number of times each simulation is updated</param>
	/// <param name="simulations">- number of simulations to run</param>
	void saveDensityDataToFile(const std::string& path, unsigned iterations, unsigned simulations);

	const std::vector<sf::RectangleShape> getPixels() const { return pixels; }

	const std::vector<sf::RectangleShape> getLivePixels() const;

  private:
	/// <summary>Updates the state of the simulation.</summary>
	void updateTable();

	/// <summary>Updates the states of RectangleShape objects based on data from the table.</summary>
	void updatePixels();
};