#include "Fractal.h"

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

/**
 * Implementation of the Fractal class
 */

/**
 * Fractal constructor
 * @params w, h - width and height
 * @param t - type of fractal
 */
Fractal::Fractal(int w, int h, char t) {
	// init width and height
	setWidth(w); setHeight(h);
	// how intense colors are
	setIntensity(3);
	// what type of fractal
	setType(t);
}

// getter methods
int Fractal::getWidth() {
	return width;
}
int Fractal::getHeight() {
	return height;
}
int Fractal::getDepth() {
	return depth;
}
int Fractal::getIntensity() {
	return intensity;
}
double Fractal::getMinReal() {
	return minReal;
}
double Fractal::getMaxReal() {
	return maxReal;
}
double Fractal::getMinImag() {
	return minImag;
}
double Fractal::getMaxImag() {
	return maxImag;
}
double Fractal::getRealFactor() {
	return realFactor;
}
double Fractal::getImagFactor() {
	return imagFactor;
}
char Fractal::getType() {
	return type;
}
std::list<Pixel> Fractal::getPixels() {
	return listPixels;
}

// setter methods
void Fractal::setWidth(int w) {
	width = w;
}
void Fractal::setHeight(int h) {
	height = h;
}
void Fractal::setDepth(int d) {
	depth = d;
}
void Fractal::setIntensity(int i) {
	intensity = i;
}
void Fractal::setMinReal(double nR) {
	minReal = nR;
}
void Fractal::setMaxReal(double mR) {
	maxReal = mR;
}
void Fractal::setMinImag(double nI) {
	minImag = nI;
}
void Fractal::setMaxImag(double mI) {
	maxImag = mI;
}
void Fractal::setRealFactor(double rF) {
	realFactor = rF;
}
void Fractal::setImagFactor(double iF) {
	imagFactor = iF;
}
void Fractal::setType(char t) {
	type = t;
}

// zooming function
void Fractal::zoom(char type, int x, int y) {
	// zoom in is 3x, zoom out is 1/3x
	double factor = (type == 'i') ? 0.33 : 3.00;
	// width is based on the reals
	float newWidth = (float)((getMaxReal() - getMinReal()) * factor);
	// height on the imaginary
	float newHeight = (float)((getMaxImag() - getMinImag()) * factor);
	// find new bounds in real axis
	float newBoundX = (float)(getMinReal() + ((getMaxReal() - getMinReal()) / width) * x);
	// new bounds in imag axis
	float newBoundY = (float)(getMinImag() + ((getMaxImag() - getMinImag()) / height) * y);
	// redefine the boundaries (area zoomed to), stick to 3x zoom
	setMinReal(newBoundX - (newWidth / 3));
	setMaxReal(newBoundX + (newWidth / 3));
	setMinImag(newBoundY - (newHeight / 3));
	setMaxImag(newBoundY + (newHeight / 3));
	// factors change based on the above
	setRealFactor((getMaxReal() - getMinReal()) / (width - 1));
	setImagFactor((getMaxImag() - getMinImag()) / (height - 1));
}

/**
 * Color Finder method
 * will find the color of a given pixel based on depth
 * @params x, y - the x,y position of the pixel
 * @param i - how many iterations needed to be unbound
 */
void Fractal::findColor(int i, int x, int y) {
	// higher fidelity needs higher intensity
	double iF = getDepth() / (double)(64);
	// iC is an intensifier for a certain color
	double iC = min(1.0, (getIntensity() * iF * (double)(i) / getDepth()));
	if (i < (getDepth() / 4)) { // varying red
		listPixels.push_back(Pixel(iC, 0.0, 0.0, x, y));
	} else if (i < (getDepth() / 3)) { // varying purple
		listPixels.push_back(Pixel(iC, 0.0, iC, x, y));
	} else if (i < (getDepth() / 2)) { // varying blue
		listPixels.push_back(Pixel(0.0, 0.0, iC, x, y));
	} else if (i < (getDepth() / 1)) { // varying grey
		listPixels.push_back(Pixel((1.0-iC), (1.0 - iC), (1.0 - iC), x, y));
	} else { // black
		listPixels.push_back(Pixel(0.0, 0.0, 0.0, x, y));
	}
}

/**
 * List Destroyer
 */
void Fractal::resetList() {
	listPixels.clear();
}
