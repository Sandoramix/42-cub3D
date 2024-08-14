#include <cub3D.h>
int calc_px_pos(int x, int y, t_img *img)
{
	return (y * img->width + x) * 4;
}


int is_px_black(char *img, int px)
{
	if ((unsigned char)img[px + 0] == 0 &&
			(unsigned char)img[px + 1] == 0 &&
			(unsigned char)img[px + 2] == 0)
			return (1);
	return (0);
}

void copy_px_to_img(char *game_img, int game_img_px, char *sprite, int sprite_px)
{
	game_img[game_img_px + 0] = sprite[sprite_px + 0];
	game_img[game_img_px + 1] = sprite[sprite_px + 1];
	game_img[game_img_px + 2] = sprite[sprite_px + 2];
	game_img[game_img_px + 3] = sprite[sprite_px + 3];
}


/**
 * @brief It will overwrite the game->img with the px from the sprite_buf, will
 * traverse the spritebuff cols first, starting from the x coords given, 
 * for y it will always place it at the bottom. 
 * It will ignore sprite_buf black px and threat them as transparent.
 * 		
 * @param game game obj
 * @param sprite sprite obj
 * @param sprite_buf sprite buffer
 */
void sprite_loader(t_var *game,t_img *sprite, char* sprite_buf, int startingfrom_x)
{
	int img_px;
	char *img;
	int x;
	int y;

	img = mlx_get_data_addr(game->img, &game->bpp, &game->line_bytes, &game->endian);
	y = 0;
	while(y < sprite->height)
	{
		x = 0;
		while (x < sprite->width)
		{
			img_px = calc_px_pos(startingfrom_x + x,
				(game->config.win_height - sprite->height) + y, game->img);
			if (!is_px_black( sprite->image->data, calc_px_pos(x, y, sprite)))
				copy_px_to_img(img, img_px, sprite_buf, calc_px_pos(x, y, sprite));
			x++;
		}
		y++;
	}
}


void render_sprites(t_var *game)
{
	const int hands_start_px = (game->config.win_width / 2 - game->config.forearm->width / 2);
	sprite_loader(game, game->config.forearm, game->config.forearm_buff, hands_start_px);
}
