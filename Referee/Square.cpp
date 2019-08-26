#include "Square.h"
#define _USE_MATH_DEFINES
#include <cmath>

bool LineCross(Vector2D a, Vector2D b, Vector2D c, Vector2D d) noexcept
{
	const auto ac = c - a;
	const auto ad = d - a;
	const auto bc = c - b;
	const auto bd = d - b;
	const auto ca = -ac;
	const auto cb = -bc;
	const auto da = -ad;
	const auto db = -bd;

	if (std::abs(ac.Cross(ad)) < 1e-6 && std::abs(bc.Cross(bd)) < 1e-6)
	{
		return (ac * bc <= 0) || (ad * bd) <= 0 ||
			   (ca * da <= 0) || (cb * db) <= 0;
	}

	return (ac.Cross(ad)) * (bc.Cross(bd)) <= 0 &&
		   (ca.Cross(cb)) * (da.Cross(db)) <= 0;
}

std::vector<std::pair<Vector2D, Vector2D>> Square::getLines()
{
	return {
		{point1, point3}, {point1, point4},
		{point3, point2}, {point4, point2},
	};
}

Square::Square(Vector2D robotPosition, float angleInDegree = 0, float hrl = 3.9335)
{
	const double robotRadius = hrl * 1.414;

	while (angleInDegree > 45)
	{
		angleInDegree -= 90;
	}
	while (angleInDegree < -45)
	{
		angleInDegree += 90;
	}

	double point1X = robotPosition.x + robotRadius * std::cos(angleInDegree * M_PI / 180);
	double point1Y = robotPosition.y + robotRadius * std::sin(angleInDegree * M_PI / 180);
	double point2X = robotPosition.x - robotRadius * std::cos(angleInDegree * M_PI / 180);
	double point2Y = robotPosition.y - robotRadius * std::sin(angleInDegree * M_PI / 180);
	point1 = {point1X, point1Y};
	point2 = {point2X, point2Y};
}

bool Square::IsCrossedBy(Square& square)
{
	for (auto line_a_b : getLines())
	{
		auto a = line_a_b.first;
		auto b = line_a_b.second;
		for (auto line_c_d : square.getLines())
		{
			auto c = line_c_d.first;
			auto d = line_c_d.second;
			if (LineCross(a, b, c, d))
			{
				return true;
			}
		}
	}

	return false;
}
