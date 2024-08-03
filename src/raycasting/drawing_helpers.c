
#include <cub3D.h>

void drw_img_buff(t_var *game, int x, int y, int color)
{
	int pixel = (y * game->line_bytes) + (x * sizeof(int));
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
				drw_img_buff(game,  pixel_pos_x, y, mlx_get_color_value(game->mlx, 0x0));
			else
				drw_img_buff(game,  pixel_pos_x, y, mlx_get_color_value(game->mlx, 0xFFFFFF));
			y++;
		}
	}
}

void draw_rectangle(t_var *game, t_point start, t_point end, int color)
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
			drw_img_buff(game,  start.x,  start.y, mlx_get_color_value(game->mlx, color));
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
		drw_img_buff(game, (int)next_point.x, (int)next_point.y, mlx_get_color_value(game->mlx, 0x0000FF));
		next_point.x += increment.x;
		next_point.y += increment.y;
		counter++;
	}
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