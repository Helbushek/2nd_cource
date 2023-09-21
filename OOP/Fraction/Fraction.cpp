#pragma once
#include <iostream>
#include "Fraction.h"

Fraction::Fraction() 
{
	numerator = 1;
	denominator = 1;
}

Fraction:: Fraction(int numerator, int denominator) {
	Fraction::numerator = numerator;
	Fraction::denominator = denominator;
}

Fraction Fraction::sum	(const Fraction summ_2) 
{
	Fraction summ;
	if (denominator != summ_2.denominator) 
	{
		summ.numerator = (numerator * summ_2.denominator) + (summ_2.numerator * denominator);
		summ.denominator = denominator * summ_2.denominator;
		return(summ);
	}
	summ.numerator = numerator + summ_2.numerator;
	summ.denominator = denominator;
	if (summ.denominator == 0)
	{
		std::cerr << "Fatal error in::Fraction, denominator cannot be 0; Division by 0";
		exit;
	}
	return(summ);
	
}

Fraction Fraction::dif(const Fraction summ_2) 
{
	Fraction summ;
	if (denominator != summ_2.denominator)
	{
		summ.numerator = (numerator * summ_2.denominator) - (summ_2.numerator * denominator);
		summ.denominator = denominator * summ_2.denominator;
	}
	else {
		summ.numerator = numerator - summ_2.numerator;
		summ.denominator = denominator;
	}
	if (summ.denominator == 0) 
	{
		std::cerr << "Fatal error in::Fraction, denominator cannot be 0; Division by 0";
		exit;
	}
	return(summ);
}

void Fraction::setNumerator() {
	std::cin >> numerator;
}


void Fraction::setDenominator() {
	int temp;
	std::cin >> temp;
	if (temp == 0) {
		std::cerr << "Fatal error in ::Fraction, denominator cannot be 0; Division by 0";
		exit;
	}
	denominator = temp;
}

void Fraction::set() 
{
	setNumerator();
	setDenominator();
}

void Fraction::print() 
{
	std::cout << numerator << "/" << denominator;
}

Fraction Fraction::div(const Fraction devisor) 
{
	Fraction quotient;
	if (devisor.numerator == 0 ) 
	{
		std::cerr << "Fatal error in ::Fraction, denominator cannot be 0; Division by 0";
		exit;
	}
	quotient.numerator = numerator * devisor.denominator;
	quotient.denominator = denominator * devisor.numerator;

	return(quotient);
}

Fraction Fraction::mul(const Fraction multiplier)
{
	Fraction multiplicator;
	if (denominator*multiplier.denominator==0) 
	{
		std::cerr << "Fatal error in ::Fraction, denominator cannot be 0; Division by 0";
		exit;
	}
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

void Fraction::reduce() 
{
	Fraction reduced;
	for (int i=2; i<=abs(numerator) && i<=abs(denominator); ) 
	{
		if (numerator%i==0 && denominator%i==0) 
		{
			numerator = numerator / i;
			denominator = denominator / i;
			i = 2;
			continue;
		}
		i++;
	}
}

float Fraction::convertToFloat() 
{
	float result = 0.0;
	if (denominator != 0) {
		result = (numerator*1.0) / denominator;
	}
	else result = INT_MIN;
	return(result);
}

Fraction Fraction::convertFromFloat(float fraction, int accuracy) 
{
	int accuracy1=1;
	for (int i = 0; i < accuracy; i++) accuracy1 *= 10;
	Fraction totalFraction;
	totalFraction.numerator = fraction * accuracy1;
	totalFraction.denominator = accuracy1;

	return(totalFraction);

}

Fraction& Fraction::operator+(const Fraction summ_2) {
	Fraction summ;
	if (denominator != summ_2.denominator)
	{
		summ.numerator = (numerator * summ_2.denominator) + (summ_2.numerator * denominator);
		summ.denominator = denominator * summ_2.denominator;
	}
	else {
		summ.numerator = numerator + summ_2.numerator;
		summ.denominator = denominator;
	}
	if (summ.denominator == 0)
	{
		std::cerr << "Fatal error in::Fraction, denominator cannot be 0; Division by 0";
		exit;
	}
	return(summ);

}
Fraction& Fraction::operator-(const Fraction summ_2) {
	Fraction summ;
	if (denominator != summ_2.denominator)
	{
		summ.numerator = (numerator * summ_2.denominator) - (summ_2.numerator * denominator);
		summ.denominator = denominator * summ_2.denominator;
	}
	else {
		summ.numerator = numerator - summ_2.numerator;
		summ.denominator = denominator;
	}
	if (summ.denominator == 0)
	{
		std::cerr << "Fatal error in::Fraction, denominator cannot be 0; Division by 0";
		exit;
	}
	return(summ);
}
Fraction& Fraction::operator*(const Fraction multiplier) {
	Fraction multiplicator;
	if (denominator * multiplier.denominator == 0)
	{
		std::cerr << "Fatal error in ::Fraction, denominator cannot be 0; Division by 0";
		exit;
	}
	multiplicator.numerator = numerator * multiplier.numerator;
	multiplicator.denominator = denominator * multiplier.denominator;

	return(multiplicator);
}
Fraction& Fraction::operator/(const Fraction devisor) {
	Fraction quotient;
	if (devisor.numerator == 0)
	{
		std::cerr << "Fatal error in ::Fraction, denominator cannot be 0; Division by 0";
		exit;
	}
	quotient.numerator = numerator * devisor.denominator;
	quotient.denominator = denominator * devisor.numerator;

	return(quotient);
}

void Fraction::operator+=(const Fraction summ_2) {
	if (denominator != summ_2.denominator)
	{
		numerator = (numerator * summ_2.denominator) + (summ_2.numerator * denominator);
		denominator = denominator * summ_2.denominator;
	}
	else {
		numerator = numerator + summ_2.numerator;
		denominator = denominator;
	}
	if (denominator == 0)
	{
		std::cerr << "Fatal error in::Fraction, denominator cannot be 0; Division by 0";
		exit;
	}
	

}
void Fraction::operator-=(const Fraction summ_2) {
	if (denominator != summ_2.denominator)
	{
		numerator = (numerator * summ_2.denominator) - (summ_2.numerator * denominator);
		denominator = denominator * summ_2.denominator;
	}
	else {
		numerator = numerator - summ_2.numerator;
		denominator = denominator;
	}
	if (denominator == 0)
	{
		std::cerr << "Fatal error in::Fraction, denominator cannot be 0; Division by 0";
		exit;
	}
	
}
void Fraction::operator*=(const Fraction multiplier) {
	if (denominator * multiplier.denominator == 0)
	{
		std::cerr << "Fatal error in ::Fraction, denominator cannot be 0; Division by 0";
		exit;
	}
	numerator = numerator * multiplier.numerator;
	denominator = denominator * multiplier.denominator;

}
void Fraction::operator/=(const Fraction devisor) {
	if (devisor.numerator == 0)
	{
		std::cerr << "Fatal error in ::Fraction, denominator cannot be 0; Division by 0";
		exit;
	}
	numerator = numerator * devisor.denominator;
	denominator = denominator * devisor.numerator;

}