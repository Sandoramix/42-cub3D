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

void copy_px_to_img(char *img, int img_px, char *arms, int forearm_px)
{
	img[img_px + 0] = arms[forearm_px + 0];
	img[img_px + 1] = arms[forearm_px + 1];
	img[img_px + 2] = arms[forearm_px + 2];
	img[img_px + 3] = arms[forearm_px + 3];
}

void render_sprites_basic_pos(t_var *game)
{
	char *arms;
	char *img;
	int img_px;
	int forearm_px;
	int y;
	int x;
	arms = mlx_get_data_addr(game->config.forearm, &game->bpp, &game->line_bytes, &game->endian);
	img = mlx_get_data_addr(game->img, &game->bpp, &game->line_bytes, &game->endian);

	y = 0;
	while(y < game->config.forearm->height)
	{
		x = 0;
		while (x < game->config.forearm->width)
		{
			forearm_px = calc_px_pos(x, y, game->config.forearm); 
			img_px = calc_px_pos((game->config.win_width / 2 - game->config.forearm->width / 2) + x,
				(game->config.win_height - game->config.forearm->height) + y,
				game->img);
			if (!is_px_black( game->config.forearm->image->data, forearm_px))
				copy_px_to_img(img, img_px, arms, forearm_px);
			x++;
		}
		y++;
	}
}

void render_sprites(t_var *game)
{
	render_sprites_basic_pos(game);
}

