#include <cub3D.h>

double pi()
{
	return (acos(-1.0));
}

double from_angle_to_radiant(double angle)
{
	return (angle * (pi() / 180));
}

t_dpoint calculate_point(t_dpoint start, double angle, double distance)
{
	t_dpoint end;

	if (angle < 0)
		angle = 360 + angle;
	end.x = (start.x + (distance * cos(from_angle_to_radiant(angle))) * 64);
	end.y = (start.y + (distance * sin(from_angle_to_radiant(angle))) * 64);

	return end;
}