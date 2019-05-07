#pragma once
#include "Fractal.h"
#include "ComplexNumber.h"

/**
 * Set class declaration
 */

class Set : public Fractal {
private:
	void findPixel(int, int, ComplexNumber);
	void findPoints();
	ComplexNumber iterate(ComplexNumber, ComplexNumber);
public:
	Set(int, int, char);
	void recalculateSet();
	void resetDefaults();
};