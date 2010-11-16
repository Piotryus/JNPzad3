/*
 * rational.cc
 *
 *  Created on: 2010-11-14
 *      Author: piotr
 */
#include <iostream>
#include <cstdio>
#include "rational.h"

using namespace std;


/*	this is the greatest common divisor function
 */
long gcd(unsigned long a, unsigned long b){
	if(b == 0UL)
		return a;
	else
		return gcd(b, a % b);
}

/*unsigned long abs(long a){
	return a >= 0 ? a : -a;
}*/

const Rational Rational::Zero(){
	static const Rational zero = Rational(0L);
	return zero;
}

const Rational Rational::One(){
	static const Rational one = Rational(1L);
	return one;
}

Rational::Rational(){
	numerator = 0L;
	denominator = 1UL;
	isRational = true;
}

Rational::Rational (long l){
	numerator = l;
	denominator = 1UL;
	isRational = true;
}

Rational::Rational(long n, unsigned long d){
	numerator = n;
	denominator = d;
	if (numerator != 0 && denominator != 0){
		numerator /= gcd(abs(n), d);
		denominator /= gcd(abs(n), d);
	}
	isRational = (denominator != 0UL);
}

Rational::Rational(const Rational& r){
	numerator = r.numerator;
	denominator = r.denominator;
	isRational = r.isRational;
}

void Rational::opposite(){
	numerator = -numerator;

	return;
}

void Rational::reciprocal(){
	long temp = numerator;

	numerator = temp >= 0 ? denominator : -denominator;	//what about this conversion and sign?
	denominator = temp >= 0? temp : -temp;
	/* swap values, check if it is still proper number */
	if (denominator == 0)
		isRational = false;

	return;
}

Rational& Rational::operator+=(const Rational& x){
						//check later for Nan additon!!
	if (!x.isRational){
		isRational = false;
	}
	long lcm = (denominator * x.denominator)/gcd(denominator, x.denominator);
		//least common multiple
	numerator = (numerator * x.denominator + x.numerator * denominator)
			/gcd(denominator, x.denominator);
	denominator = lcm;
	return *this;
}

Rational& Rational::operator -=(const Rational& x){
	Rational minus(x);
	minus.opposite();
	*this += minus;
	return *this;
}

Rational& Rational::operator *=(const Rational& x){
	if (!x.isRational){
		isRational = false;
	}
	numerator *= x.numerator /gcd(denominator, x.numerator); //what about minus?
	denominator *= x.denominator /gcd(numerator, x.denominator);
	return *this;
}

Rational& Rational::operator /=(const Rational& x){
	Rational divide(x);
	divide.reciprocal();
	*this *= divide;
	return *this;
}

const bool Rational::operator <=(const Rational& x) const{
		return isRational && x.isRational
		&& numerator * x.denominator <= x.numerator * denominator;
}

const bool Rational::operator <(const Rational& x) const{
		return isRational && x.isRational
		&& numerator * x.denominator < x.numerator * denominator;
}

const bool Rational::operator >(const Rational& x) const{
		return isRational && x.isRational
		&& x< *this;
}

const bool Rational::operator >=(const Rational& x) const{
		return isRational && x.isRational
		&& x <= *this;
}

const bool Rational::operator ==(const Rational& x) const{
	return isRational && x.isRational
	&& numerator * x.denominator == x.numerator * denominator;
}

const bool Rational::operator !=(const Rational& x) const{
	return isRational && x.isRational
	&& !(*this == x);
}

const bool operator <(const long& l, const Rational& r){
	return r > l;
}

const bool operator >(const long& l, const Rational& r){
	return r < l;
}

const bool operator >=(const long& l, const Rational& r){
	return r <= l;
}

const bool operator <=(const long& l, const Rational& r){
	return r >= l;
}

const bool operator ==(const long& l, const Rational& r){
	return r == l;
}

const bool operator !=(const long& l, const Rational& r){
	return r != l;
}

bool Rational::isNumber() const{
	return isRational;
}

const Rational& Rational::operator -(){
	opposite();
	return *this;
}

ostream& operator<<(ostream& os, const Rational& r) {
  if (r.isRational){
	  if (abs(r.numerator) / r.denominator > 0){
		  if (r.numerator < 0)
			  os << "-";
		  os << abs(r.numerator) /r.denominator;
		  if (abs(r.numerator) % r.denominator > 0 && r.numerator > 0)
			  os << "+";
	  } else if (abs(r.numerator) % r.denominator == 0){
			  os << 0L;
		  }
	  if (abs(r.numerator) % r.denominator > 0){
		  if (r.numerator < 0)
			  os << "-";
		  os << abs(r.numerator) % r.denominator << "/" <<r.denominator;
	  }

  } else
	  os << "NaN";
  return os;
}

bool Rational::boolean_test() const{
	//cout << "Rational::boolean_test()" << endl;
	return isRational && numerator != Rational::Zero();
}

int main() {
	Rational a;
	cout << a << endl;
	Rational b(a);
	cout << b << endl;
	Rational c(5L);
	cout << c << endl;
	Rational d(8L, 0UL);
	cout << d << endl;
	d = 1 / d;
	cout << d << endl;
	if (a <= b)
		cout << d << endl;
	if (c)
		cout << d << endl;
	if (d)
		cout << a << endl;
}
