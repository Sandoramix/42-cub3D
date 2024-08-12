#include "cub3D.h"

void	calc_texture_coords(t_var *game)
{
	t_raycast *engine;
	t_player *player;
	t_texture *tex;
	int half_wall;
	int half_win_h;

	engine = &game->engine;
	player = &game->player;
	tex = &game->engine.texture;
	half_win_h = game->config.win_height / 2.0;
	half_wall = game->engine.wall_height / 2.0;
	if (isinf(engine->dir.x) || isinf(engine->dir.y))
		return;
	if (engine->side == CNF_WALL_WEST || engine->side == CNF_WALL_EAST)
		tex->wall_px = player->y_px / TILE_SIZE + engine->wall_dist * engine->dir.y; //waall coordinates dove ho colpito il muro
	else
		tex->wall_px = player->x_px / TILE_SIZE + engine->wall_dist * engine->dir.x; //waall coordinates dove ho colpito il muro
	
	tex->wall_px -= floor(tex->wall_px); //questo serve a portarlo in un range tra 1 e 64 credo? lets go i guess lets fucking go 
	tex->x = (int)(tex->wall_px * (double)TILE_SIZE); // text coordinate X
	
	if ((engine->side == CNF_WALL_WEST || engine->side == CNF_WALL_EAST)) // mirroring della texture
		tex->x = TILE_SIZE - tex->x - 1;

	tex->scale = 1.0 * (double)TILE_SIZE / (double)engine->wall_height;
	tex->scaled_textpos= (engine->wall_ceil - (
				half_win_h
				+ player->offset
				+ ((player->pos_z + player->head_pos_z)
					/ engine->wall_dist))
			+ half_wall)
		* game->engine.texture.scale;
}

t_uint get_texture_color(t_var *game)
{
	t_img			*texture;
	t_uint			color;

	texture = game->engine.texture.text_array[game->engine.side];
	game->engine.texture.pixel = texture->data
		+ (game->engine.texture.y
			* texture->size_line)
		+ (game->engine.texture.x
			* 4);
	color = *game->engine.texture.pixel;
	return (color);
}
