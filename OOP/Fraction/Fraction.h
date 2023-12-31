#pragma once

class Fraction {
public:
	Fraction();
	Fraction(int numerator, int denominator);
	Fraction sum(const Fraction &summ_2);
	Fraction dif(const Fraction &summ_2);
	Fraction div(const Fraction &devisor);
	Fraction mul(const Fraction &multiplier);

	// Overloads: 

	Fraction  operator +(const Fraction &summ_2);
	Fraction  operator -(const Fraction &summ_2);
	Fraction  operator *(const Fraction &multiplier);
	Fraction operator /(const Fraction &devisor);

	Fraction &operator +=(const Fraction &summ_2);// a = b = c;
	Fraction &operator -=(const Fraction &summ_2);
	Fraction &operator *=(const Fraction &multiplier);
	Fraction &operator /=(const Fraction &devisor);

	char compare(const Fraction compared);

	bool operator <(const Fraction &compare);
	bool operator >(const Fraction &compare);
	bool operator ==(const Fraction &compare);
	bool operator !=(const Fraction &compare);

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