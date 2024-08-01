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
    start = (t_dpoint){game->player_pos.x + game->plane.x, game->player_pos.y + game->plane.y };
	while(angle <= FOV/2)
	{
		result = calculate_point(&start, angle, game->dda.wall_dist);
        draw_line(game, start, result);
		angle++;
	}
    
        
}

static void get_multiplication_factor(t_var *game)
{
	game->dda.delta_dist_x = fabs(1 / game->dda.dir_rayx);
	game->dda.delta_dist_y = fabs(1 / game->dda.dir_rayy);

    // printf("delta_dist_x, delta_dist_y %f %f\n",game->dda.delta_dist_x, game->dda.delta_dist_y);
}

static void get_ray_direction(t_var *game, int pixel_pos_x)
{
	game->dda.camera_x = (double)(2 * pixel_pos_x) / (double)game->dda.screen_size_w_px - 1;
	game->dda.dir_rayx = game->player_pos.dir_x + game->plane.x * game->dda.camera_x;
	game->dda.dir_rayy = game->player_pos.dir_y + game->plane.y * game->dda.camera_x;
	//printf("Angle of the ray: %f radians\n", atan2(game->dda.dir_rayy, game->dda.dir_rayx));
}


void copy_player_pos(t_var *game)
{
	game->dda.map_x = (int)game->player_pos.x;
	game->dda.map_y = (int)game->player_pos.y;
}

void set_up_dda_vars(t_var *game, int pixel_pos_x)
{
	copy_player_pos(game);
	get_ray_direction(game, pixel_pos_x);
	get_multiplication_factor(game);
}

void loop_until_hit_wall(t_var *game)
{
	game->dda.hit = 0;
	game->dda.side = 0;
	while (game->dda.hit == 0)
	{
		increase_raylen(game);
		if (game->mapinfo.mtxint[game->dda.map_x][game->dda.map_y] > 0)
			game->dda.hit = 1;
	}
}

void calc_relative_line_height(t_var *game)
{
	game->dda.line_h_px = (int)(game->dda.screen_size_w_px / game->dda.wall_dist);
}

void draw_walls(t_var *game, int pixel_pos_x)
{
	int y = game->dda.draw_start_px;
	int print_every_tot_line = 6;
	if (pixel_pos_x % print_every_tot_line == 0)
	{
		while (y <= game->dda.draw_end_px)
		{
			if (game->dda.side == 1)
				mlx_pixel_put(game->mlx_ptr, game->win_ptr, pixel_pos_x, y, 0xFF0000);
			else
				mlx_pixel_put(game->mlx_ptr, game->win_ptr, pixel_pos_x, y, 0x0000FF);
			y++;
		}
	}
}

void wall_casting(t_var *game, int pixel_pos_x)
{
	while (pixel_pos_x < game->dda.screen_size_w_px)
	{
		set_up_dda_vars(game, pixel_pos_x);
		calc_initial_step_intial_raylen(game);
		loop_until_hit_wall(game);
		calc_distance_from_wall(game);
		calc_relative_line_height(game);
		put_line_h_in_perspective(game);
		draw_walls(game, pixel_pos_x);
		pixel_pos_x++;
	}
}


 void floor_ceiling_casting(t_var *game)
{
	int pixel_pos_y;
	pixel_pos_y = 0;
	int pixel_pos_x;
	pixel_pos_x = 0;

	float rayDirX0;
	float rayDirY0;
	float rayDirX1;
	float rayDirY1;
	float posZ;
	int p;
	float rowDistance;
	float floorStepX;
    float floorStepY;
	float floorX;
    float floorY;
	int cellX;
	int cellY;
	while(pixel_pos_y < game->dda.screen_size_h_px)
	{
		pixel_pos_x = 0;
		rayDirX0 = game->player_pos.x  - game->player_pos.dir_x;
    	rayDirY0 = game->player_pos.y  - game->player_pos.dir_y;
    	rayDirX1 = game->player_pos.x  + game->player_pos.dir_x;
    	rayDirY1 = game->player_pos.y + game->player_pos.dir_y;
		p = pixel_pos_y -  game->dda.screen_size_h_px / 2;
		posZ = 0.5 * game->dda.screen_size_h_px;
		
		rowDistance = posZ / p;
		floorStepX = rowDistance * (rayDirX1 - rayDirX0) / game->dda.screen_size_w_px;
		floorStepY = rowDistance * (rayDirY1 - rayDirY0) / game->dda.screen_size_w_px;
		floorX = game->player_pos.x + rowDistance * rayDirX0;
		floorY = game->player_pos.y + rowDistance * rayDirY0;
		while(pixel_pos_x < game->dda.screen_size_w_px)
		{	
			cellX = (int)(floorX);
        	cellY = (int)(floorY);
			mlx_pixel_put(game->mlx_ptr, game->win_ptr, pixel_pos_x, pixel_pos_y, 0x181818);
			pixel_pos_x++;
		}
		pixel_pos_y++;
	}
} 

void raycasting(t_var *game)
{
	int pixel_pos_x;
	pixel_pos_x = 0;

	game->dda = (t_DDA){0};
	
	
	game->dda.screen_size_w_px = 1600.0;
	game->dda.screen_size_h_px = 1080.0;
	floor_ceiling_casting(game);
	wall_casting(game, pixel_pos_x); 
}