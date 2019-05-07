#pragma once
#include <array>

/**
 * Pixel class declaration
 */

class Pixel {
private:
	double r, g, b;
	int x, y;
public:
	Pixel(double red, double gre, double blu, int xPos, int yPos);
	std::array<double, 3> getCol();
	std::array<int, 2> getPos();
};