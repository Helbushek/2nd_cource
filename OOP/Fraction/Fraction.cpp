#pragma once
#include <iostream>
#include "Fraction.h"

Fraction Fraction::summFractions(const Fraction summ_2) {
	Fraction summ;
	summ.numerator = (numerator * summ_2.denominator) + (summ_2.numerator * denominator);
	summ.denominator = denominator * summ_2.denominator;
	return(summ);
}

Fraction Fraction::differenceFractions(const Fraction summ_2) {
	Fraction summ;
	summ.numerator = (numerator * summ_2.denominator) - (summ_2.numerator * denominator);
	summ.denominator = denominator * summ_2.denominator;
	return(summ);
}

void Fraction::print() 
{
	std::cout << numerator << "/" << denominator;
}

Fraction Fraction::devideFractions(const Fraction devisor) 
{
	Fraction quotient;
	quotient.numerator = numerator * devisor.denominator;
	quotient.denominator = denominator * devisor.numerator;

	return(quotient);
}

Fraction Fraction::miltiplyFractions(const Fraction multiplier)
{
	Fraction multiplicator;
	multiplicator.numerator = numerator * multiplier.numerator;
	multiplicator.denominator = denominator* multiplier.denominator;

	return(multiplicator);
}

