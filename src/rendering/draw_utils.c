
#include <cub3D.h>

void draw_px_to_img(t_var *game, int x, int y, t_rgb rgb)
{
	int pixel;

	pixel = (y * game->line_bytes) + (x * 4);
	game->buffer[pixel + 0] = rgb.color.red;
	game->buffer[pixel + 1] = rgb.color.green;
	game->buffer[pixel + 2] = rgb.color.blue;
	game->buffer[pixel + 3] = rgb.color.alpha;
}

void draw_rectangle(t_var *game, t_point start, t_point end, t_rgb rgb)
{
	while (start.y < end.y)
	{
		start.x = 0;
		while (start.x < end.x)
		{
			draw_px_to_img(game, start.x, start.y, rgb);
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
		draw_px_to_img(game, (int)next_point.x, (int)next_point.y, (t_rgb){0x0});
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
	start_px = (t_dpoint){game->player.x_px + game->engine.plane.x, game->player.y_px + game->engine.plane.y};
	while (angle <= FOV / 2)
	{
		end_px = calculate_point(start_px, angle, game->engine.wall_dist);
		draw_line(game, start_px, end_px);
		angle++;
	}
}