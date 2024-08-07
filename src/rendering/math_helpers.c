#include <cub3D.h>
void copy_dpos(t_dpoint *p1, t_dpoint p2)
{
	p1->x = p2.x;
	p1->y = p2.y;
}

void copy_pos(t_point *p1, t_point p2)
{
	p1->x = p2.x;
	p1->y = p2.y;
}

void add_dpoint(t_dpoint *p1, t_dpoint p2)
{
	p1->x += p2.x;
	p1->y += p2.y;
}
void add_point(t_point *p1, t_point p2)
{
	p1->x += p2.x;
	p1->y += p2.y;
}
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
	end.x = (start.x + (distance * cos(from_angle_to_radiant(angle))) * TILE_SIZE);
	end.y = (start.y + (distance * sin(from_angle_to_radiant(angle))) * TILE_SIZE);

	return end;
}