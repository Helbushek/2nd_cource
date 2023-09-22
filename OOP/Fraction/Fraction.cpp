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


void Fraction::setNumerator() {
	std::cin >> numerator;
}


void Fraction::setDenominator() {
	int temp;
	std::cin >> temp;
	if (temp == 0) {
		std::cerr << "Fatal error in Fraction::setDenominator, denominator cannot be 0; Division by 0";
	}
	denominator = temp;
}

int Fraction::getNumerator()
{
	return(numerator);
}


int Fraction::getDenominator()
{
	return(denominator);
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



Fraction Fraction::sum	(const Fraction &summ_2) 
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
		std::cerr << "Fatal error in Fraction::sum, denominator cannot be 0; Division by 0";
	}
	return(summ);
	
}

Fraction Fraction::dif(const Fraction &summ_2) 
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
		std::cerr << "Fatal error in Fraction::dif, denominator cannot be 0; Division by 0";
	}
	return(summ);
}


Fraction Fraction::div(const Fraction &devisor) 
{
	Fraction quotient;
	if (devisor.numerator == 0 ) 
	{
		std::cerr << "Fatal error in Fraction::div, denominator cannot be 0; Division by 0";
	}
	quotient.numerator = numerator * devisor.denominator;
	quotient.denominator = denominator * devisor.numerator;

	return(quotient);
}

Fraction Fraction::mul(const Fraction &multiplier)
{
	Fraction multiplicator;
	if (denominator*multiplier.denominator==0) 
	{
		std::cerr << "Fatal error in Fraction::mul, denominator cannot be 0; Division by 0";
	}
	multiplicator.numerator = numerator * multiplier.numerator;
	multiplicator.denominator = denominator* multiplier.denominator;

	return(multiplicator);
}


char Fraction::compare(const Fraction compared) 
{
	float Fraction1, Fraction2;
	Fraction1 = (numerator +.0)/ denominator;
	Fraction2 = (compared.numerator+ .0) / compared.denominator;

	if (Fraction1 > Fraction2) return('>');
	if (Fraction1 < Fraction2) return('<');
	if (Fraction1 == Fraction2) return('=');
	if (Fraction1 != Fraction2) return('!=');
}


bool Fraction::operator <(const Fraction &compare) {
	if (this->compare(compare) == '<') return(true);
	return(false);
}
bool Fraction::operator >(const Fraction &compare) {
	if (this->compare(compare) == '>') return(true);
	return(false);
}
bool Fraction::operator ==(const Fraction &compare) {
	if (this->compare(compare) == '=') return(true);
	return(false);
}
bool Fraction::operator !=(const Fraction &compare) {
	if (this->compare(compare) == '!=') return(true);
	return(false);
}

float max(float first, float second) {
	if (first > second) return(first);
	return(second);
}

void Fraction::reduce() 
{
	if (numerator == denominator) { numerator = 1; denominator = 1; }
	for (int i=2; i<=abs(numerator) && i<=abs(denominator) && i<=max(numerator, denominator)/2; ) 
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
	for (int i = 0; i < accuracy; i++)
		accuracy1 *= 10;
	Fraction totalFraction;
	totalFraction.numerator = fraction * accuracy1;
	totalFraction.denominator = accuracy1;

	return(totalFraction);

}

Fraction Fraction::operator+(const Fraction &summ_2) {
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
		std::cerr << "Fatal error in Fraction::operator+, denominator cannot be 0; Division by 0";
	}
	return(summ);

}
Fraction Fraction::operator-(const Fraction &summ_2) {
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
		std::cerr << "Fatal error in Fraction::operator-, denominator cannot be 0; Division by 0";
	}
	return(summ);
}
Fraction Fraction::operator*(const Fraction &multiplier) {
	Fraction multiplicator;
	if (denominator * multiplier.denominator == 0)
	{
		std::cerr << "Fatal error in Fraction::operator*, denominator cannot be 0; Division by 0";
	}
	multiplicator.numerator = numerator * multiplier.numerator;
	multiplicator.denominator = denominator * multiplier.denominator;

	return(multiplicator);
}
Fraction Fraction::operator/(const Fraction &devisor) {
	Fraction quotient;
	if (devisor.numerator == 0)
	{
		std::cerr << "Fatal error in Fraction::operator/, denominator cannot be 0; Division by 0";
	}
	quotient.numerator = numerator * devisor.denominator;
	quotient.denominator = denominator * devisor.numerator;

	return(quotient);
}

Fraction& Fraction::operator+=(const Fraction &summ_2) {
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
		std::cerr << "Fatal error in Fraction::operator+=, denominator cannot be 0; Division by 0";
	}
	
	return(*this);
}
Fraction& Fraction::operator-=(const Fraction &summ_2) {
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
		std::cerr << "Fatal error in Fraction::operator-=, denominator cannot be 0; Division by 0";
	}
	return(*this);
}
Fraction& Fraction::operator*=(const Fraction &multiplier) {
	if (denominator * multiplier.denominator == 0)
	{
		std::cerr << "Fatal error in Fraction::operator*=, denominator cannot be 0; Division by 0";
	}
	numerator = numerator * multiplier.numerator;
	denominator = denominator * multiplier.denominator;
	return(*this);
}
Fraction& Fraction::operator/=(const Fraction &devisor) {
	if (devisor.numerator == 0)
	{
		std::cerr << "Fatal error in Fraction::operator/=, denominator cannot be 0; Division by 0";
	}
	numerator = numerator * devisor.denominator;
	denominator = denominator * devisor.numerator;
	return(*this);
}