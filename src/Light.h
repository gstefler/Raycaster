#pragma once

#include "Ray.h"

class Light
{
	Ray* rays;
	Vec* hits;
	Vec pos;
	int length;
	int numOfIntersections;

	Vec unitVecFromAngle(float angle) {
		float rad = angle * PI / 180;
		return { sinf(rad), cosf(rad) };
	}
public:
	Light() = default;
	Light(Vec pos, float inc = 1) :pos(pos), length((int)(360 / inc))
	{
		rays = new Ray[length];
		hits = new Vec[length];
		int i = 0;
		for (float a = 0; a < 360; a += inc)
		{
			rays[i++] = Ray(&(this->pos), unitVecFromAngle(a));
		}
	}

	void setPos(const Vec pos) {
		this->pos = pos;
	}

	void cast(const Boundary* walls, int numOfWalls) {
		numOfIntersections = 0;
		for (int i = 0; i < length; i++)
		{
			float closest = 10000.f;
			for (int j = 0; j < numOfWalls; j++)
			{
				// Get the intersection point between two walls, null if they don't meet
				Vec* intersectionPoint = rays[i].cast(walls[j]);
				if (intersectionPoint)
				{
					if (intersectionPoint->distance(pos) < closest)
					{
						hits[numOfIntersections] = *intersectionPoint;
						closest = intersectionPoint->distance(pos);
					}
					delete intersectionPoint;
				}
			}
			numOfIntersections++;
		}
	}

	void draw(sf::RenderTarget* window, sf::CircleShape* cent) {
		cent->setPosition(pos.getX() - cent->getGlobalBounds().width / 2.f,
			pos.getY() - cent->getGlobalBounds().height / 2.f
		);
		window->draw(*cent);
		for (int i = 0; i < numOfIntersections; i++)
		{

			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(pos), sf::Color(255, 255, 0, 150)),
				sf::Vertex(sf::Vector2f(hits[i]), sf::Color(255, 255, 0, 150))
			};
			window->draw(line, 2, sf::Lines);
		}
	}


	~Light()
	{
		delete[] rays;
		delete[] hits;
	}
};

