#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

using std::ostream;
using std::cout;
using std::endl;

#define PI 3.14159265358979323846

class Vec
{
private:
	float x, y;

public:
	// Default ctor
	Vec()=default;

	// Ctor
	Vec(float x, float y) :x(x), y(y) {}

	// Copy ctor
	Vec(const Vec& rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
	}

	// operator =
	Vec& operator=(const Vec& rhs) {
		if (this != &rhs)
		{
			this->x = rhs.x;
			this->y = rhs.y;
		}
		return *this;
	}

	Vec operator+(const Vec& rhs) const{
		Vec tmp(x + rhs.getX(), y + rhs.getY());
		return tmp;
	}

	Vec operator-(const Vec& rhs) const {
		Vec tmp(x - rhs.getX(), y - rhs.getY());
		return tmp;
	}

	Vec operator*(int scalar) const {
		Vec tmp(x * scalar, y * scalar);
		return tmp;
	}

	// Get X
	float getX() const { return x; }

	// Get Y
	float getY() const { return y; }

	// Vector length
	float length() const {
		return sqrtf(x * x + y * y);
	}

	float distance(const Vec& pos) const {
		float x = this->x - pos.getX();
		float y = this->y - pos.getY();
		x *= x;
		y *= y;
		return sqrtf(x + y);
	}
	
	// Normalize and set magnitude
	void normalize(float m = 1.f) {
		float lenght = length();
		x /= lenght;
		y /= lenght;
		x *= m;
		y *= m;
	}

	// Convert my vector to an sfml vector
	operator sf::Vector2f() const {
		return sf::Vector2f(x, y);
	}
};


// Operator for cout
inline ostream& operator<<(ostream& os, const Vec& rhs) {
	os << "x: " << rhs.getX() << " y: " << rhs.getY() << endl;
	return os;
}