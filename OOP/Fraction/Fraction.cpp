#pragma once
#include <iostream>
#include "Fraction.h"

Fraction Fraction::summ_fractions(const Fraction summ_2) {
	Fraction summ;
	summ.numerator = (numerator * summ_2.denominator) + (summ_2.numerator * denominator);
	summ.denominator = denominator * summ_2.denominator;
	return(summ);
}

Fraction Fraction::difference_fractions(const Fraction summ_2) {
	Fraction summ;
	summ.numerator = (numerator * summ_2.denominator) - (summ_2.numerator * denominator);
	summ.denominator = denominator * summ_2.denominator;
	return(summ);
}

void Fraction::print() {
	std::cout << numerator << "/" << denominator;
}

