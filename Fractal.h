#pragma once
#include "Pixel.h"
#include <list>

/**
 * Fractal class declaration
 */

class Fractal {
private:
	std::list<Pixel> listPixels;
	int width, height;
	int depth, maxDepth;
	int intensity;
	double minReal, maxReal;
	double minImag, maxImag;
	double realFactor, imagFactor;
	char type;
public:
	Fractal(int, int, char);
	int getWidth();
	int getHeight();
	int getDepth();
	int getIntensity();
	double getMinReal();
	double getMaxReal();
	double getMinImag();
	double getMaxImag();
	double getRealFactor();
	double getImagFactor();
	char getType();
	std::list<Pixel> getPixels();
	void setWidth(int);
	void setHeight(int);
	void setDepth(int);
	void setIntensity(int);
	void setMinReal(double);
	void setMaxReal(double);
	void setMinImag(double);
	void setMaxImag(double);
	void setRealFactor(double);
	void setImagFactor(double);
	void setType(char);
	void zoom(char, int, int);
	void findColor(int, int, int);
	void resetList();
};