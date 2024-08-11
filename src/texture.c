#include "cub3D.h"

void calc_texture_coords(t_var *game)
{
	t_raycast *engine;
	t_player *player;

	engine = &game->engine;
	player = &game->player;
	if (engine->side == CNF_WALL_WEST || engine->side == CNF_WALL_EAST)
		engine->texture.wallX = player->y_px + engine->wall_dist * engine->dir.y; //waall coordinates dove ho colpito il muro
	else
		engine->texture.wallX = player->x_px + engine->wall_dist * engine->dir.x; //waall coordinates dove ho colpito il muro

	engine->texture.wallX -= floor((engine->texture.wallX)); //questo serve a portarlo in un range tra 1 e 64 credo? lets go i guess lets fucking go 
	engine->texture.x = (int)(engine->texture.wallX * 64.0); // text coordinate X

	if ((engine->side == CNF_WALL_WEST || engine->side == CNF_WALL_SOUTH)) // mirroring della texture
		engine->texture.x = 64 - engine->texture.x - 1;

	engine->texture.scale = 1.0 * 64 / engine->wall_height; // scaling per la distanza
	engine->texture.scaled_textpos= (engine->wall_ceil - (
				game->config.win_height / 2
				+ player->offset
				+ ((player->pos_z + player->head_pos_z) / engine->wall_dist))
			+ game->engine.wall_height / 2)
		* game->engine.texture.scale;

}

int get_texture_color(t_var *game)
{
	t_img	*texture;

	texture = game->engine.texture.text_array[game->engine.side];
	game->engine.texture.pixel = texture->data
		+ (game->engine.texture.y
			* texture->size_line)
		+ (game->engine.texture.x
			* (texture->bpp / 8));
	return *(int *)game->engine.texture.pixel;
}