#include "cub3D.h"

t_dpoint calc_texture_px_hit(t_var * game)
{
	t_dpoint end;
	t_dpoint start;
	double angle;


	start = (t_dpoint){game->player.x , game->player.y};
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
		// t_dpoint endpx = calc_texture_px_hit(game);
		// printf("x y %f %f\n", endpx.x, endpx.y);
		
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
	ceiling_end = (t_point){game->dda.screen_size_w_px, game->dda.screen_size_h_px / 2 + game->player.offset};
	floor_start = (t_point){0, game->dda.screen_size_h_px / 2 + game->player.offset};
	floor_end = (t_point){game->dda.screen_size_w_px, game->dda.screen_size_h_px };
	draw_rectangle(game, ceiling_start, ceiling_end, 0x00FF00);
	draw_rectangle(game, floor_start, floor_end, 0xFF0F00 / 10);
}

void rendering(t_var *game)
{
	floor_ceiling_casting(game);
	wall_casting(game);

	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
}