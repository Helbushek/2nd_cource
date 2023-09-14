#pragma once

class Fraction {
public:
	Fraction();

	Fraction summ(const Fraction summ_2);
	Fraction difference(const Fraction summ_2);
	Fraction devide(const Fraction devisor);
	Fraction miltiply(const Fraction multiplier);
	Fraction reduce();

	char compare(const Fraction compared);

	int getNumerator();
	int getDenominator();

	void print();
	void set();

	double convertToDouble();
	Fraction convertFromDouble(double fraction, int accuracy);

	int numerator;
	int denominator;

};