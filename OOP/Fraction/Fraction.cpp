#pragma once
#include <iostream>
#include "Fraction.h"

Fraction::Fraction() 
{
	numerator = 0;
	denominator = 1;
}

Fraction Fraction::summ	(const Fraction summ_2) 
{
	Fraction summ;
	summ.numerator = (numerator * summ_2.denominator) + (summ_2.numerator * denominator);
	summ.denominator = denominator * summ_2.denominator;
	return(summ);
}

Fraction Fraction::difference(const Fraction summ_2) 
{
	Fraction summ;
	summ.numerator = (numerator * summ_2.denominator) - (summ_2.numerator * denominator);
	summ.denominator = denominator * summ_2.denominator;
	return(summ);
}


void Fraction::set() 
{
	std::cin >> numerator >> denominator;
}

void Fraction::print() 
{
	std::cout << numerator << "/" << denominator;
}

Fraction Fraction::devide(const Fraction devisor) 
{
	Fraction quotient;
	quotient.numerator = numerator * devisor.denominator;
	quotient.denominator = denominator * devisor.numerator;

	return(quotient);
}

Fraction Fraction::miltiply(const Fraction multiplier)
{
	Fraction multiplicator;
	multiplicator.numerator = numerator * multiplier.numerator;
	multiplicator.denominator = denominator* multiplier.denominator;

	return(multiplicator);
}

int Fraction::getNumerator() 
{
	return(numerator);
}


int Fraction::getDenominator() 
{
	return(denominator);
}



char Fraction::compare(const Fraction compared) 
{
	double Fraction1, Fraction2;
	Fraction1 = numerator / denominator;
	Fraction2 = compared.numerator / compared.denominator;

	if (Fraction1 > Fraction2) return('>');
	if (Fraction1 < Fraction2) return('<');
	if (Fraction1 == Fraction2) return('=');
	if (Fraction1 != Fraction2) return('!=');
}

Fraction Fraction::reduce() 
{
	Fraction reduced;
	reduced.numerator = numerator;
	reduced.denominator = denominator;
	for (int i=2; i<abs(reduced.numerator) && i<abs(reduced.denominator); i++) 
	{
		if (reduced.numerator%i==0 && reduced.denominator%i==0) 
		{
			reduced.numerator = numerator / i;
			reduced.denominator = denominator / i;
			i = 2;
		}
	}
	return(reduced);
}

double Fraction::convertToDouble() 
{
	return(numerator / denominator);
}

Fraction Fraction::convertFromDouble(double fraction, int accuracy) 
{
	Fraction totalFraction;
	totalFraction.numerator = (int)fraction * 10 ^ accuracy;
	totalFraction.denominator = 10 ^ accuracy;

	return(totalFraction);

}