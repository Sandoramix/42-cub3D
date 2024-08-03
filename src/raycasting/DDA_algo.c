#include <libft.h>
#include "cub3D.h"

int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

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

static void write_into_buffer(t_var *game, int x, int y, int color)
{
	int pixel = (y * game->line_bytes) + (x * sizeof(int)	);
	game->buffer[pixel + 0] = (color >> 24);
    game->buffer[pixel + 1] = (color >> 16) & 0xFF;
    game->buffer[pixel + 2] = (color >> 8) & 0xFF;
    game->buffer[pixel + 3] = (color) & 0xFF;
}


void draw_line(t_var *game, t_dpoint start, t_dpoint end)
{
	t_dpoint delta;
	t_dpoint increment;
	t_dpoint next_point;
	int pixels;
	int counter;

	delta = (t_dpoint){end.x - start.x, end.y - start.y};
	pixels = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	increment = (t_dpoint){delta.x / pixels, delta.y / pixels};
	next_point = (t_dpoint){start.x, start.y};
	counter = 0;
	while (counter < pixels)
	{
		write_into_buffer(game, (int)next_point.x, (int)next_point.y, mlx_get_color_value(game->mlx, 0x0000FF));
		// mlx_pixel_put(game->mlx, game->win_ptr, (int)next_point.x, (int)next_point.y, 0x0000FF); // Color white
		next_point.x += increment.x;
		next_point.y += increment.y;
		counter++;
	}

	/*  printf("Drawing line from (%f, %f) to (%f, %f)\n", start.x, start.y, end.x, end.y); */
}

void draw_minimap_rays(t_var *game)
{
	t_dpoint start;
	t_dpoint result;
	double angle;

	angle = -FOV / 2;
	start = (t_dpoint){game->player_pos.x + game->plane.x, game->player_pos.y + game->plane.y};
	while (angle <= FOV / 2)
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
	// printf("Angle of the ray: %f radians\n", atan2(game->dda.dir_rayy, game->dda.dir_rayx));
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
void write_into_buffe(t_var *game, int x, int y, int color)
{
	int pixel = (y * game->line_bytes) + (x * sizeof(int)	);
	game->buffer[pixel + 0] = (color >> 24);
    game->buffer[pixel + 1] = (color >> 16) & 0xFF;
    game->buffer[pixel + 2] = (color >> 8) & 0xFF;
    game->buffer[pixel + 3] = (color) & 0xFF;
}


void draw_walls(t_var *game, int pixel_pos_x)
{
	int y = game->dda.draw_start_px;
	int print_every_tot_line = 1;
	if (pixel_pos_x % print_every_tot_line == 0)
	{
		while (y <= game->dda.draw_end_px)
		{
			if (game->dda.side == 1)
				write_into_buffe(game,  pixel_pos_x, y, mlx_get_color_value(game->mlx, 0x0));
				// mlx_pixel_put(game->mlx, game->win_ptr, pixel_pos_x, y, 0XFF0000);
			else
				write_into_buffe(game,  pixel_pos_x, y, mlx_get_color_value(game->mlx, 0xFFFFFF));

				// mlx_pixel_put(game->mlx, game->win_ptr, pixel_pos_x, y, 0X0000FF);
			y++;
		}
	}
}

void wall_casting(t_var *game)
{
	int pixel_pos_x;

	pixel_pos_x = 0;
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
void rite_into_buffe(t_var *game, int x, int y, int color)
{
	int pixel = (y * game->line_bytes) + (x * sizeof(int)	);
	game->buffer[pixel + 0] = (color >> 24);
    game->buffer[pixel + 1] = (color >> 16) & 0xFF;
    game->buffer[pixel + 2] = (color >> 8) & 0xFF;
    game->buffer[pixel + 3] = (color) & 0xFF;
}


void print_rectangle(t_var *game, t_point start, t_point end, int color)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (start.y < end.y)
	{
		start.x = 0;
		while (start.x < end.x)
		{
			rite_into_buffe(game,  start.x,  start.y, mlx_get_color_value(game->mlx, color));
			// mlx_pixel_put(game->mlx, game->win_ptr, start.x, start.y, color);
			start.x++;
		}
		start.y++;
	}
}

void floor_ceiling_casting(t_var *game)
{
	t_point ceiling_start;
	t_point ceiling_end;
	t_point floor_start;
	t_point floor_end;

	ceiling_start = (t_point){0, 0};
	ceiling_end = (t_point){game->dda.screen_size_w_px, game->dda.screen_size_h_px / 2};
	floor_start = (t_point){0, game->dda.screen_size_h_px / 2};
	floor_end = (t_point){game->dda.screen_size_w_px, game->dda.screen_size_h_px};
	print_rectangle(game, ceiling_start, ceiling_end, 0x00FF00);
	print_rectangle(game, floor_start, floor_end, 0xFF0000);
}

void raycasting(t_var *game)
{
	floor_ceiling_casting(game);
	wall_casting(game);
}