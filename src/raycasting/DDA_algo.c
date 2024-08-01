#include <libft.h>
#include "cub3D.h"


double pi()
{
	return (acos(-1.0));
}

double from_angle_to_radiant(double angle)
{
	return (angle * (pi() / 180));
}

t_dpoint calculate_point(t_dpoint *start, double angle, double distance)
{
	t_dpoint end;

	if (angle < 0)
		angle = 360 + angle;
	end.x = (start->x + (distance * cos(from_angle_to_radiant(angle))) * 64);
	end.y = (start->y + (distance * sin(from_angle_to_radiant(angle))) * 64);
	
	return end;
}

void draw_line(t_var *game, t_dpoint start, t_dpoint end) {
    t_dpoint delta;
	t_dpoint increment;
	t_dpoint next_point;
	int pixels;
	int counter;
	
	delta = (t_dpoint){end.x - start.x, end.y - start.y};
	pixels = sqrt((delta.x * delta.x) + (delta.y  * delta.y ));
	increment = (t_dpoint){delta.x / pixels, delta.y  / pixels};
	next_point = (t_dpoint){start.x, start.y};
	counter = 0;
	while(counter < pixels) {
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, (int)next_point.x, (int)next_point.y, 0x0000FF); // Color white
		next_point.x += increment.x;
		next_point.y += increment.y;
		counter++;
	}





   /*  printf("Drawing line from (%f, %f) to (%f, %f)\n", start.x, start.y, end.x, end.y); */
}

 void draw_minimap_rays(t_var *game) {
    t_dpoint start;
    t_dpoint result;
    double angle;

	angle = -FOV/2;
    start = (t_dpoint){game->playerPos.pos_x + game->plane.x, game->playerPos.pos_y + game->plane.y };
	while(angle <= FOV/2)
	{
		result = calculate_point(&start, angle, game->dda_helper.perpWallDist);
        draw_line(game, start, result);
		angle++;
	}
    
        
}

static void DDA_core_logic(t_var *game , int x)
{
	calc_initial_step_intial_raylen(game);
	game->dda_helper.hit_wall = 0;
	game->dda_helper.side = 0;
	while (game->dda_helper.hit_wall == 0)
	{
		increase_raylen(game);
		if (game->mapinfo.mtxint[game->dda_helper.mapX][game->dda_helper.mapY] > 0)
			game->dda_helper.hit_wall = 1;
	}
	calc_distance_from_wall(game);
	game->dda_helper.lineHeight = (int)(game->dda_helper.screenSize / game->dda_helper.perpWallDist);
	calc_perspective(game);

	
	int y = game->dda_helper.draw_start;
	int print_every_tot_line = 6;
	if (x % print_every_tot_line == 0)
	{
		while (y <= game->dda_helper.draw_end)
		{
			mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, 0xFF0000);
			y++;
		}
	}

}

static void get_multiplication_factor(t_var *game)
{
		game->dda_helper.deltaDistX = fabs(1 / game->dda_helper.rayDirX);
		game->dda_helper.deltaDistY = fabs(1 / game->dda_helper.rayDirY);

	//printf("deltaDistX, deltaDistY %f %f\n",game->dda_helper.deltaDistX, game->dda_helper.deltaDistY);
}

static void get_ray_direction(t_var *game, int pixel_pos_x)
{
	game->dda_helper.cameraX = (double)(2 * pixel_pos_x) / (double)game->dda_helper.screenSize - 1;
	game->dda_helper.rayDirX = game->playerPos.dir_x + game->plane.x * game->dda_helper.cameraX;
	game->dda_helper.rayDirY = game->playerPos.dir_y + game->plane.y * game->dda_helper.cameraX;
	//printf("Angle of the ray: %f radians\n", atan2(game->dda_helper.rayDirY, game->dda_helper.rayDirX));
}

void calculate_DDA(t_var *game)
{
	int pixel_pos_x;

	game->dda_helper = (t_DDA){0};
	pixel_pos_x = 0;
	game->dda_helper.screenSize = 1600.0;
	while (pixel_pos_x < game->dda_helper.screenSize)
	{
		get_ray_direction(game, pixel_pos_x);
		game->dda_helper.mapX = (int)game->playerPos.pos_x;
		game->dda_helper.mapY = (int)game->playerPos.pos_y;
		get_multiplication_factor(game);
		DDA_core_logic(game,  pixel_pos_x);
		pixel_pos_x++;
	}
}