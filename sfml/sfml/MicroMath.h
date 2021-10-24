#pragma once

#include "Entity.h"
#include <math.h>

inline int Sign (int x)
{
	return (x > 0) - (x < 0);
}

inline float Distance (float x1, float y1, float x2, float y2)
{
	return std::sqrt ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

inline bool CircleIntersect (float x1, float y1, float r1, float x2, float y2, float r2)
{
	return Distance (x1, y1, x2, y2) < std::sqrt ((r1 + r2) * (r1 + r2));
}


inline bool CircleIntersect (sf::Vector2f c1, float r1, sf::Vector2f c2, float r2)
{
	return CircleIntersect (c1.x, c1.y, r1, c2.x, c2.y, r2);
}


inline bool RectangleIntersect (float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	return x2 < x1 + w1 && x2 + w2 > x1 && y2 < y1 + h1 && y2 + h2 > y1;
}


inline bool Intersect (Entity const& first, Entity const& second)
{
	return CircleIntersect (first.GetCenter (), 100, second.GetCenter (), 100);
}



/*

// forras https://stackoverflow.com/questions/21089959/detecting-collision-of-rectangle-with-circle
engine.rectCircleColliding = function (rect, circle) {

	let distX = Math.abs(circle.x - rect.x - rect.width / 2);
	let distY = Math.abs(circle.y - rect.y - rect.height / 2);

	if (distX > (rect.width / 2 + circle.r)) {
		return false;
	}
	if (distY > (rect.height / 2 + circle.r)) {
		return false;
	}

	if (distX <= (rect.width / 2)) { return true; }
	if (distY <= (rect.height / 2)) { return true; }
	let dx = distX - rect.width / 2;
	let dy = distY - rect.height / 2;
	return (dx * dx + dy * dy <= (circle.r ** 2));
}


*/