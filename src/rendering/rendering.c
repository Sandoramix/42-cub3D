#include "cub3D.h"

t_dpoint calc_texture_px_hit(t_var * game)
{
	t_dpoint end;
	t_dpoint start;
	double angle;


	start = (t_dpoint){game->player.x_px + game->engine.plane.x, game->player.y_px + game->engine.plane.y};
	angle = atan2(game->player.dir_x, game->player.dir_y);
	angle *= 180 / pi(); 
	end = calculate_point(start, angle, game->engine.wall_dist);

	return end;
}

void wall_casting(t_var *game)
{
	int pixel_pos_x;

	pixel_pos_x = 0;
	while (pixel_pos_x <= game->config.win_width)
	{
		init_rendering(game, pixel_pos_x);
		loop_until_hit_wall(game);
		get_wall_coords(game);
		//t_dpoint endpx = calc_texture_px_hit(game);
		draw_walls(game, pixel_pos_x);
		pixel_pos_x++;
	}
}

void	floor_ceiling_casting(t_var *game)
{
	const t_point	ceiling_start = (t_point){0, 0};
	const t_point	ceiling_end = (t_point)
	{game->config.win_width, game->config.win_height / 2 + game->player.offset};
	const t_point	floor_start = (t_point)
	{0, game->config.win_height / 2 + game->player.offset};
	const t_point	floor_end = (t_point){game->config.win_width, game->config.win_height};

	draw_rectangle(game, ceiling_start, ceiling_end, game->config.ceiling.hex);
	draw_rectangle(game, floor_start, floor_end, game->config.floor.hex);
}

void	rendering(t_var *game)
{
	floor_ceiling_casting(game);
	wall_casting(game);

	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
}