#pragma once

/**
 * Complex Number class declaration
 */

class ComplexNumber {
private:
	double real;
	double imag;
public:
	ComplexNumber(double, double);
	double getReal();
	double getImag();
	void setReal(double);
	void setImag(double);
	double getMod();
	ComplexNumber neg();
	ComplexNumber inv();
	ComplexNumber abso();
	ComplexNumber operator+ (ComplexNumber);
	ComplexNumber operator- (ComplexNumber);
	void operator+= (ComplexNumber);
	void operator-= (ComplexNumber);
	ComplexNumber operator* (ComplexNumber);
	ComplexNumber operator^ (int);
	bool operator== (ComplexNumber);
	ComplexNumber getCopy();
};