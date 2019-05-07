#include "Pixel.h"

/**
 * Pixel class implementation
 */

/**
 * Pixel constructor
 */
Pixel::Pixel(double red, double gre, double blu, int xPos, int yPos) {
	r = red; g = gre; b = blu; // init rgb values
	x = xPos; y = yPos; // init position
}

// getter methods
std::array<double, 3> Pixel::getCol() {
	return std::array<double, 3>{ {r, g, b}};
}
std::array<int, 2> Pixel::getPos() {
	return std::array<int, 2>{ {x, y}};
}
