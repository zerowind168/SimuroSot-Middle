#pragma once
#include <vector>
#include "Referee.h"

struct Vector2D
{
	double x, y;

	Vector2D operator-(const Vector2D& rhs) const noexcept
	{
		return Vector2D{ x - rhs.x, y - rhs.y };
	}

	Vector2D operator-() const noexcept
	{
		return Vector2D{ -x, -y };
	}

	double operator*(const Vector2D& rhs) const noexcept
	{
		return x * rhs.x + y * rhs.y;
	}

	double Cross(const Vector2D& rhs) const noexcept
	{
		return x * rhs.y - y * rhs.x;
	}
	Vector2D::Vector2D(double x1, double y1)
	{
		x = x1;
		y = y1;
	}
	Vector2D::Vector2D()
	{
		x = 0;
		y = 0;
	}
};

class Square
{
	Vector2D point1, point2, point3, point4;
	std::vector<std::pair<Vector2D, Vector2D>> getLines();
public:
	Vector3D getPos();
	Vector2D robotPosition;
	Square();
	Square(Vector2D robotPosition, float angleInDegree = 0, float HRL = 3.9335);
	/*Square(Vector3D robotPosition, float angleInDegree = 0, float HRL = 3.9335);*/
	bool IsCrossedBy(Square& square);
};