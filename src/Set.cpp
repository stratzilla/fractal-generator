#include "Set.h"

/**
 * Set class implementation
 */

/**
 * Set constructor
 */
Set::Set(int w, int h, char t) : Fractal::Fractal(w, h, t) {
	// boundaries of the display window, keeping aspect, etc
	setMinReal(-2.0); setMaxReal(2.0); setMinImag(-2.0); setMaxImag(2.0);
	// factor is how divisible a complex number can be
	setRealFactor((getMaxReal() - getMinReal()) / (getWidth() - 1));
	setImagFactor((getMaxImag() - getMinImag()) / (getHeight() - 1));
}

/**
 * Point Finder method
 * will exhaust all possible pixel coords and devise
 * a complex number therein to which to calculate the set
 */
void Set::findPoints() {
	for (int i = 0; i < getHeight(); i++) { // for each y
		for (int j = 0; j < getWidth(); j++) { // for each x
			/**
			 * construct a new complex number
			 * this will exhaust all possible complex numbers
			 * that are renderable through the system
			 */
			double imag = getMaxImag() - (i * getImagFactor());
			double real = getMinReal() + (j * getRealFactor());
			// then find what the pixel will be
			findPixel(j, i, ComplexNumber(real, imag));
		}
	}
}


/**
 * Finds pixels within the defined set
 * will exhaust all possible complex numbers from findPoints()
 * @params x, y - position
 * @param c - the complex number
 */
void Set::findPixel(int x, int y, ComplexNumber c) {
	ComplexNumber z = c.getCopy(); // copy of c as z
	int i = 0; // for depth coloring
	/**
	 * continually iterate the rule of the set on z
	 * until it breaks out of the loop, either be being unbounded or
	 * through limitation on maximal depth (64 default)
	 *
	 * disregard the empty loop; its purpose is to find
	 * the depth at which i will break out of the loop
	 * ultimately giving us an i denoting the depth for coloring
	 */
	for (; i < getDepth() && z.getMod() <= 5; i++, z = iterate(z, c));
	// based on number of iterations, find a color
	findColor(i, x, y);
}

/**
 * Iteration method
 * performs some arithmetic on params to define the set
 * @params z, c - complex numbers to define the set
 */
ComplexNumber Set::iterate(ComplexNumber z, ComplexNumber c) {
	switch (getType()) {
	case 'm':
		// Mandelbrot Set := z_(n+1) = z_n^2 + c
		return (z ^ 2) + c;
	case 'b':
		// Burning Ship Set := z_(n+1) = |z_n^2| + c
		return (z.abso() ^ 2) + c;
	case 'j':
		// Julia Set := z_(n+1) = z_n^2 + k (eg. k = -0.835 - 0.232i)
		return (z ^ 2) + ComplexNumber(-0.835, -0.232);
	/**
	 * the below are "custom" fractals insofar as I've defined
	 * some arbitrary arithmetic describing the set. If they have
	 * canonical names I'm unsure, it's just through experimentation
	 */
	case 't':
		// a "tri-winged" Mandelbrot := z_(n+1) = z_n^4 + c
		return (z ^ 4) + c;
	case 's':
		// two boxes swirling := z_(n+1) = -z^3 + w (if c = a+bi, w = b+ai)
		return (z.neg() ^ 3) + c.inv();
	case 'v':
		// "tri-winged" vein := -w^2 + z (if z = a+bi, w = b+ai)
		return (z.inv().neg() ^ 2) + z;
	case 'f':
		// two fists := z_(n+1) = -|w|^2 - c^2 + (-0.530+0.267i) (if z = a+bi, w = b+ai)
		return (z.abso().inv().neg() ^ 2) - (c ^ 2) + ComplexNumber(-0.530, 0.267);
	case 'r':
		// two ring pops := z_(n+1) = z^3 + zc^2 - c^3 - z
		return (z ^ 3) + (z * (c ^ 2)) - (c ^ 3) - z;
	case 'x':
		// shurikens := z_(n+1) = (z^2 - z^3) + (-0.372 + 0.519i)
		return ((z ^ 2) - (z ^ 3)) + ComplexNumber(-0.372, 0.519);
	case 'c':
		// clover := z_(n+1) = z^4 + (-0.835 - 0.232i)
		return (z ^ 4) + ComplexNumber(-0.835, -0.232);
	}
	return z; // it should never get here
}

/**
 * Set Recalculation method
 * will reset set contents and recalculate
 * using new rules if applicable
 */
void Set::recalculateSet() {
	resetList(); // don't redraw old pixels
	findPoints(); // find the pixels again
}

/**
 * Reset method
 * will reset all environment variables to default
 */
void Set::resetDefaults() {
	// boundaries of the display window, keeping aspect, etc
	setMinReal(-2.0); setMaxReal(2.0); setMinImag(-2.0); setMaxImag(2.0);
	// factor is how divisible a complex number can be
	setRealFactor((getMaxReal() - getMinReal()) / (getWidth() - 1));
	setImagFactor((getMaxImag() - getMinImag()) / (getHeight() - 1));
	// reset intensity
	setIntensity(3);
	// recalculate the set
	recalculateSet();
}