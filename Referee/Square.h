#pragma once
#include <vector>

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
};

class Square
{
	Vector2D point1, point2, point3, point4;
	std::vector<std::pair<Vector2D, Vector2D>> getLines();
public:
	Square(Vector2D robotPosition, float angleInDegree = 0, float HRL = 3.9335);
	bool IsCrossedBy(Square& square);
};