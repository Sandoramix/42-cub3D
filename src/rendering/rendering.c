#include "cub3D.h"

void render_walls(t_var *game)
{
	int x;
	int y;
	t_texture *tex;

	tex = &game->engine.texture;
	x = 0;
	tex->text_array[0] = game->config.wall_nord;
	tex->text_array[1] = game->config.wall_east;
	tex->text_array[2] = game->config.wall_west;
	tex->text_array[3] = game->config.wall_south;

	while (x <= game->config.win_width)
	{
		init_vars(game, x);
		calc_direction(game);
		loop_until_hit_wall(game);
		get_wall_coords(game);
		calc_texture_coords(game);
		y = game->engine.wall_ceil;
		while(y <= game->engine.wall_floor)
		{
			tex->y = (int)tex->scaled_textpos & (tex->text_array[game->engine.side]->height - 1); //serve a tenerlo in range
			tex->scaled_textpos += tex->scale;
			draw_px_to_img(game, x, y, ((t_rgb){get_texture_color(game)}));
			y++;
		}
		x++;
	}
}

void render_background(t_var *game)
{
	const t_point	ceiling_start = (t_point){0, 0};
	const t_point	ceiling_end = (t_point){game->config.win_width,
		game->config.win_height / 2 + game->player.offset};
	const t_point	floor_start = (t_point){0,
		game->config.win_height / 2 + game->player.offset};
	const t_point	floor_end = (t_point){game->config.win_width,
		game->config.win_height};

	draw_rectangle(game, ceiling_start, ceiling_end, (t_rgb){game->config.ceiling.hex});
	draw_rectangle(game, floor_start, floor_end, (t_rgb){game->config.floor.hex});
}