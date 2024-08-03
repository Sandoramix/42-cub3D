#include "cub3D.h"

void wall_casting(t_var *game)
{
	int pixel_pos_x;

	pixel_pos_x = 0;
	while (pixel_pos_x < game->dda.screen_size_w_px)
	{
		init_rendering(game, pixel_pos_x);
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
	t_point ceiling_start;
	t_point ceiling_end;
	t_point floor_start;
	t_point floor_end;

	ceiling_start = (t_point){0, 0};
	ceiling_end = (t_point){game->dda.screen_size_w_px, game->dda.screen_size_h_px / 2};
	floor_start = (t_point){0, game->dda.screen_size_h_px / 2};
	floor_end = (t_point){game->dda.screen_size_w_px, game->dda.screen_size_h_px};
	draw_rectangle(game, ceiling_start, ceiling_end, 0x00FF00);
	draw_rectangle(game, floor_start, floor_end, 0xFF0F00 / 10);
}

void rendering(t_var *game)
{
	floor_ceiling_casting(game);
	wall_casting(game);

	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
}