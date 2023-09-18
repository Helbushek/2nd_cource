#pragma once

class Fraction {
public:
	Fraction();

	Fraction sum(const Fraction summ_2);
	Fraction dif(const Fraction summ_2);
	Fraction div(const Fraction devisor);
	Fraction mul(const Fraction multiplier);
	

	char compare(const Fraction compared);
	 
	int getNumerator();
	int getDenominator();

	void setNumerator();
	void setDenominator();

	void reduce();

	void print();
	void set();

	float convertToFloat();
	Fraction convertFromFloat(float fraction, int accuracy);

private:
	int numerator;
	int denominator;

};