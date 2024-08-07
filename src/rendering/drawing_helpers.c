
#include <cub3D.h>

void fill_img_buffer(t_var *game, int x, int y, int color)
{
	int pixel = (y * game->line_bytes) + (x * sizeof(int));
	game->buffer[pixel + 0] = (color >> 24);
    game->buffer[pixel + 1] = (color >> 16) & 0xFF;
    game->buffer[pixel + 2] = (color >> 8) & 0xFF;
    game->buffer[pixel + 3] = (color) & 0xFF;
}

void draw_walls(t_var *game, int pixel_pos_x)
{
	int y;
	int print_every_tot_line;

	y = game->raycasting.wall_start_px;
	print_every_tot_line = 1;
	if (pixel_pos_x % print_every_tot_line == 0)
	{
		while (y <= game->raycasting.wall_end_px)
		{
			if (game->raycasting.side == CNF_WALL_NORD)
				fill_img_buffer(game,  pixel_pos_x, y, mlx_get_color_value(game->mlx, 0x18000000));
			else if (game->raycasting.side == CNF_WALL_SOUTH)
				fill_img_buffer(game,  pixel_pos_x, y, mlx_get_color_value(game->mlx, 0x00FF0000));
			else if (game->raycasting.side == CNF_WALL_EAST)
				fill_img_buffer(game,  pixel_pos_x, y, mlx_get_color_value(game->mlx, 0x0000FF00));
			else
				fill_img_buffer(game,  pixel_pos_x, y, mlx_get_color_value(game->mlx, 0xFFFFFF00));
			y++;
		}
	}
}

void draw_rectangle(t_var *game, t_point start, t_point end, int color)
{
	while (start.y < end.y)
	{
		start.x = 0;
		while (start.x < end.x)
		{
			fill_img_buffer(game,  start.x, start.y, color);
			start.x++;
		}
		start.y++;
	}
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
		fill_img_buffer(game, (int)next_point.x, (int)next_point.y, 0x0);
		next_point.x += increment.x;
		next_point.y += increment.y;
		counter++;
	}
}

void draw_minimap_rays(t_var *game)
{
	t_dpoint start_px;
	t_dpoint end_px;
	double angle;

	angle = -FOV / 2;
	start_px = (t_dpoint){game->player.x_px + game->plane.x, game->player.y_px + game->plane.y};
	while (angle <= FOV / 2)
	{
		end_px = calculate_point(start_px, angle, game->raycasting.wall_dist);
		draw_line(game, start_px, end_px);
		angle++;
	}
}