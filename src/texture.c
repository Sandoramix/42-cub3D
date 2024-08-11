#include "cub3D.h"

void calc_texture_coords(t_var *game)
{
	if (game->engine.side == CNF_WALL_WEST || game->engine.side == CNF_WALL_EAST)
		game->engine.texture.wallX = game->player.y_px + game->engine.wall_dist * game->engine.dir.y; //waall coordinates dove ho colpito il muro
	else
		game->engine.texture.wallX = game->player.x_px + game->engine.wall_dist * game->engine.dir.x; //waall coordinates dove ho colpito il muro

	game->engine.texture.wallX -= floor((game->engine.texture.wallX)); //questo serve a portarlo in un range tra 1 e 64 credo? lets go i guess lets fucking go 
	game->engine.texture.x = (int)(game->engine.texture.wallX * 64.0); // text coordinate X

	if ((game->engine.side == CNF_WALL_WEST || game->engine.side == CNF_WALL_SOUTH)) // mirroring della texture
		game->engine.texture.x = 64 - game->engine.texture.x - 1;

	game->engine.texture.scale = 1.0 * 64 / game->engine.wall_height; // scaling per la distanza
	game->engine.texture.scaled_textpos= (game->engine.wall_ceil - (game->config.win_height / 2 + game->player.offset + ((game->player.pos_z + game->player.head_pos_z) / game->engine.wall_dist)) + game->engine.wall_height / 2) * game->engine.texture.scale;

}

int get_texture_color(t_var *game)
{
	game->engine.texture.pixel = game->engine.texture.text_array[game->engine.side]->data
		+ (game->engine.texture.y
			* game->engine.texture.text_array[game->engine.side]->size_line)
		+ (game->engine.texture.x
			* (game->engine.texture.text_array[game->engine.side]->bpp / 8));
	return *(int *)game->engine.texture.pixel;
}