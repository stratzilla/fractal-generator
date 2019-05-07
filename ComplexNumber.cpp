#include "ComplexNumber.h"

/**
 * I reuse the same param 'op' several times. This is the operand
 * following the operator. For example, two complex numbers a and b
 * in the case of a+b, b is op
 *
 * a lot of the program's speed (or lack thereof) comes from here
 * as a lot of computations are done, I tried to maximize efficiency
 * for example, n+n is faster to compute than n*2
 * likewise n*n is faster than n^2
 *
 * I could have done some exceptionally cool spirals
 * by implementing complex to the power of complex
 * but this is just too complicated
 * 
 * a complex number is typically represented with a
 * real component and an imaginary component
 * for example, a+bi; a is the real component, while
 * bi is the imaginary component. b in this example is a scalar
 * leading bi to be a scalar factor of the imaginary constant i
 */

// constructor for ComplexNumber
ComplexNumber::ComplexNumber(double r, double i) {
	real = r; imag = i;
}

// getter methods
double ComplexNumber::getReal() {
	return real;
}
double ComplexNumber::getImag() {
	return imag;
}

// setter methods
void ComplexNumber::setReal(double r) {
	real = r;
}
void ComplexNumber::setImag(double i) {
	imag = i;
}

// modulus method
double ComplexNumber::getMod() {
	/**
	* the modulus of a complex number is the distance
	* between it and the origin (0+0i) in the real/imag plane
	* I use rectilinear metrics because the triangle
	* inequality still holds in this metric space
	* euclidean: mod_c = sqrt(c_r^2 + c_i^2)
	* rectilinear: mod_c = c_r^2 + c_i^2
	* this is mostly a preferential choice, although it
	* does reduce the computational cost
	*/
	return (getReal() * getReal()) + (getImag() * getImag());
}

/**
* since complex numbers have some different arithmetic
* I need to redefine the arithmetic functions
*/

// negative, (a+bi) becomes (-a-bi)
ComplexNumber ComplexNumber::neg() {
	return ComplexNumber(-(getReal()), -(getImag()));
}

// inverse, (a+bi) becomes (b+ai)
ComplexNumber ComplexNumber::inv() {
	return ComplexNumber(getImag(), getReal());
}

// absolute magnitude, (a+bi) becomes (|a|+|b|i)
ComplexNumber ComplexNumber::abso() {
	double r = (getReal() < 0) ? -getReal() : getReal();
	double i = (getImag() < 0) ? -getImag() : getImag();
	return ComplexNumber(r, i);
}

// sum of complex numbers
ComplexNumber ComplexNumber::operator+ (ComplexNumber op) {
	double r = (getReal() + op.getReal());
	double i = (getImag() + op.getImag());
	return ComplexNumber(r, i);
}

// reinitialize as sum
void ComplexNumber::operator+= (ComplexNumber op) {
	setReal(getReal() + op.getReal());
	setImag(getImag() + op.getImag());
}

// subtraction of complex numbers
ComplexNumber ComplexNumber::operator- (ComplexNumber op) {
	// a - b is equivalent to a + (-b)
	return operator+(op.neg());
}

// reinitialize as subtraction
void ComplexNumber::operator-= (ComplexNumber op) {
	operator+=(op.neg());
}

// multiplication of complex numbers
ComplexNumber ComplexNumber::operator* (ComplexNumber op) {
	// (a+bi)(c+di) = ac + adi + bci - bd
	double r = ((getReal() * op.getReal()) - (getImag() * op.getImag()));
	double i = ((getReal() * op.getImag()) + (getImag() * op.getReal()));
	return ComplexNumber(r, i);
}

// exponentiation of complex number to real exponent
ComplexNumber ComplexNumber::operator^ (int d) {
	ComplexNumber c = ComplexNumber(getReal(), getImag());
	// exponentiation is repeated self multiplication
	for (int j = 1; j < d; j++) {
		c = c * getCopy();
	}
	return c;
}

// equality
bool ComplexNumber::operator== (ComplexNumber op) {
	return (getReal() == op.getReal() && getImag() == op.getImag());
}

// copies a complex number
ComplexNumber ComplexNumber::getCopy() {
	return ComplexNumber(getReal(), getImag());
}