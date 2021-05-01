#pragma once
#include "Vector.h"

class Boundary
{
	Vec a, b;
public:
	// Default ctor
	Boundary() = default;

	// Ctor
	Boundary(Vec a, Vec b) :a(a), b(b) {}

	Vec getA() const { return a; }
	Vec getB() const { return b; }

	// Draw function
	void draw(sf::RenderTarget* window) {
		sf::Vertex line[] =
		{
			sf::Vertex(a),
			sf::Vertex(b)
		};
		window->draw(line, 2, sf::Lines);
	}
};

