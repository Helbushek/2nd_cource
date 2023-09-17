#pragma once

class Fraction {
public:
	Fraction();

	Fraction summ(const Fraction summ_2);
	Fraction difference(const Fraction summ_2);
	Fraction devide(const Fraction devisor);
	Fraction multiply(const Fraction multiplier);
	

	char compare(const Fraction compared);
	 
	int getNumerator();
	int getDenominator();

	void reduce();

	void print();
	void set();

	float convertToFloat();
	Fraction convertFromFloat(float fraction, int accuracy);

	int numerator;
	int denominator;

};