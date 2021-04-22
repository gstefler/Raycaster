#pragma once
#include "Vector.h"
#include "Boundary.h"

class Ray
{
	Vec* pos;
	Vec dir;
public:
	Ray() = default;
	Ray(Vec* pos, Vec dir = {1.f, 0.f}) :pos(pos), dir(dir) {}
	Ray& operator=(const Ray& rhs) {
		if (this != &rhs)
		{
			this->pos = rhs.pos;
			this->dir = rhs.dir;
		}
		return *this;
	}

	void draw(sf::RenderTarget* window) {
		sf::Vertex line[] =
		{
			sf::Vertex(*pos),
			sf::Vertex(*pos + dir * 10)
		};
		window->draw(line, 2, sf::Lines);
	}

	void lookAt(Vec dir) {
		this->dir = dir - *pos;
		this->dir.normalize();
	}

	Vec* cast(const Boundary& wall) {
		float x1 = wall.getA().getX();
		float y1 = wall.getA().getY();
		float x2 = wall.getB().getX();
		float y2 = wall.getB().getY();

		float x3 = pos->getX();
		float y3 = pos->getY();
		float x4 = pos->getX() + dir.getX();
		float y4 = pos->getY() + dir.getY();

		float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
		if (den == 0) return nullptr;

		float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
		float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

		if (t > 0.f && t < 1.f && u > 0.f)
		{
			Vec* inter = new Vec;
			*inter = { x1 + t * (x2 - x1), y1 + t * (y2 - y1) };
			return inter;
		}
		return nullptr;
	}
};

