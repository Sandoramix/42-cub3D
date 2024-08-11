#include "cub3D.h"

void render_wall(t_var *game)
{
	int x;
	game->engine.texture.text_array[0] = game->config.wall_nord;
	game->engine.texture.text_array[1] = game->config.wall_east;
	game->engine.texture.text_array[2] = game->config.wall_west;
	game->engine.texture.text_array[3] = game->config.wall_south;

	x = 0;
	while (x <= game->config.win_width)
	{
		init_render(game, x);
		loop_until_hit_wall(game);
		get_wall_coords(game);
		calc_texture_coords(game);
		for (int y = game->engine.wall_ceil; y <= game->engine.wall_floor; y++)
		{
			game->engine.texture.y = (int)game->engine.texture.scaled_textpos & (64 - 1); // text coordinate Y
			game->engine.texture.scaled_textpos += game->engine.texture.scale;
			draw_px_to_img(game, x, y, get_texture_color(game));
		}
		x++;
	}
}

void render_background(t_var *game)
{
	const t_point ceiling_start = (t_point){0, 0};
	const t_point ceiling_end = (t_point){game->config.win_width, game->config.win_height / 2 + game->player.offset};
	const t_point floor_start = (t_point){0, game->config.win_height / 2 + game->player.offset};
	const t_point floor_end = (t_point){game->config.win_width, game->config.win_height};

	draw_rectangle(game, ceiling_start, ceiling_end, game->config.ceiling.hex);
	draw_rectangle(game, floor_start, floor_end, game->config.floor.hex);
}

void render(t_var *game)
{
	render_background(game);
	render_wall(game);

	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
}