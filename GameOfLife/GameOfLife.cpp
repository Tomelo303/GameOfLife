#include "GameOfLife.h"
#include <random>
#include <fstream>
#include <iterator>


GameOfLife::GameOfLife(int width, int height, int pixel_size, double probability)
	: width(width), height(height), pixel_size(pixel_size), probability(probability)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::bernoulli_distribution bool_dist(probability);
	size_t index = 0;

	for (int H = 0; H < height; H++)
	{
		table.push_back({});

		for (int W = 0; W < width; W++)
		{
			table[H].push_back(bool_dist(rng));
			pixels.emplace_back(sf::Vector2f(pixel_size, pixel_size));
			pixels[index].setPosition(sf::Vector2f(W * pixel_size, H * pixel_size));
			index++;
		}
	}

	updatePixels();
}

void GameOfLife::update()
{
	if (running)
	{
		updateTable();
		updatePixels();
	}
}

void GameOfLife::reset(double probability)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::bernoulli_distribution bool_dist(probability);
	this->probability = probability;

	for (int H = 0; H < height; H++)
		for (int W = 0; W < width; W++)
			table[H][W] = bool_dist(rng);

	updatePixels();
}

void GameOfLife::reset()
{
	reset(probability);
}

void GameOfLife::flipPixelState(const int x, const int y)
{
	size_t index = 0;
	bool found = false;

	while (!found && index < pixels.size())
	{
		sf::Vector2f pos = pixels[index].getPosition();

		if (x >= pos.x && x <= pos.x + pixel_size &&
			y >= pos.y && y <= pos.y + pixel_size)
		{
			int H = index / width;
			int W = index % width;

			table[H][W] = !table[H][W];
			pixels[index].setFillColor(table[H][W] ? sf::Color::White : sf::Color::Black);

			found = true;
		}

		index++;
	}
}

void GameOfLife::saveDensityDataToFile(const std::string& path, unsigned iterations)
{
	std::vector<double> result = {};
	const double N = width * height;
	double counter = 0;

	for (unsigned i = 0; i < iterations; i++)
	{
		for (int H = 0; H < height; H++)
			for (int W = 0; W < width; W++)
				if (table[H][W]) counter++;

		result.push_back(counter / N);
		counter = 0;

		updateTable();
	}

	std::ofstream output_file(path);
	std::ostream_iterator<double> output_iterator(output_file, "\n");
	std::copy(result.begin(), result.end(), output_iterator);
	output_file.close();
}

void GameOfLife::saveDensityDataToFile(const std::string& path, unsigned iteration, unsigned simulations)
{
	std::vector<double> result = {};
	const double N = width * height;
	double counter = 0;

	for (unsigned s = 0; s < simulations; s++)
	{
		for (unsigned i = 0; i < iteration; i++)
			updateTable();

		for (int H = 0; H < height; H++)
			for (int W = 0; W < width; W++)
				if (table[H][W]) counter++;

		result.push_back(counter / N);

		counter = 0;
		reset();
	}

	std::ofstream output_file(path);
	std::ostream_iterator<double> output_iterator(output_file, "\n");
	std::copy(result.begin(), result.end(), output_iterator);
	output_file.close();
}

const std::vector<sf::RectangleShape> GameOfLife::getLivePixels() const
{
	std::vector<sf::RectangleShape> live_pixels;

	for (auto& pixel : pixels)
	{
		if (pixel.getFillColor() == sf::Color::White)
		{
			live_pixels.emplace_back(pixel);
		}
	}

	return live_pixels;
}

void GameOfLife::updateTable()
{
	std::vector<std::vector<bool>> table_copy = table;

	for (int H = 0; H < height; H++)
	{
		for (int W = 0; W < width; W++)
		{
			int counter = 0;
			for (int h = std::max(0, H - 1); h <= std::min(height - 1, H + 1); h++)
			{
				for (int w = std::max(0, W - 1); w <= std::min(width - 1, W + 1); w++)
				{
					if (!(w == W && h == H) && table_copy[h][w])  // Not counting itself
						counter++;

					/*if (table_copy[w][h])  // Counting itself
						counter++;*/
				}
			}

			if (table[H][W])
				if (counter >= 2 && counter <= 3)
					table[H][W] = true;
				else
					table[H][W] = false;
			else
				if (counter == 3)
					table[H][W] = true;
				else
					table[H][W] = false;
		}
	}
}

void GameOfLife::updatePixels()
{
	size_t index = 0;

	for (int H = 0; H < height; H++)
	{
		for (int W = 0; W < width; W++)
		{
			pixels[index].setFillColor(table[H][W] ? sf::Color::White : sf::Color::Black);
			index++;
		}
	}
}
