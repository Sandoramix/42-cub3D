#include "cub3D.h"

t_dpoint calc_texture_px_hit(t_var * game)
{
	t_dpoint end;
	t_dpoint start;
	double angle;


	start = (t_dpoint){game->player.x_px + game->plane.x, game->player.y_px + game->plane.y};
	angle = atan2(game->player.dir_x, game->player.dir_y);
	angle *= 180 / pi(); 
	end = calculate_point(start, angle, game->dda.wall_dist);

	return end;
}

void wall_casting(t_var *game)
{
	int pixel_pos_x;

	pixel_pos_x = 0;
	while (pixel_pos_x < game->dda.screen_size_w_px)
	{
		init_rendering(game, pixel_pos_x);
		loop_until_hit_wall(game);
		get_wall_coords(game);
		t_dpoint endpx = calc_texture_px_hit(game);
		draw_walls(game, pixel_pos_x);
		pixel_pos_x++;
	}
}

void floor_ceiling_casting(t_var *game)
{
	const t_point ceiling_start = (t_point){0, 0};
	const t_point ceiling_end = (t_point){WINDOW_WIDTH, WINDOW_HEIGHT / 2 + game->player.offset};
	const t_point floor_start = (t_point){0, WINDOW_HEIGHT / 2 + game->player.offset};
	const t_point floor_end = (t_point){WINDOW_WIDTH, WINDOW_HEIGHT};

	draw_rectangle(game, ceiling_start, ceiling_end, 0xFF000000);
	draw_rectangle(game, floor_start, floor_end, 0x0000FF00);
}

void rendering(t_var *game)
{
	floor_ceiling_casting(game);
	wall_casting(game);

	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
}