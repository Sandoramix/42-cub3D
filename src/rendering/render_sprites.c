/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 22:20:36 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/18 15:10:21 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	calc_px_pos(t_img *img, int x, int y)
{
	return ((y * img->width + x) * 4);
}

int	is_px_black(char *img, int px)
{
	return ((unsigned char)img[px + 0] == 0
		&& (unsigned char)img[px + 1] == 0
		&& (unsigned char)img[px + 2] == 0);
}

void	copy_px_to_img(t_img *atlas, t_ivec2 atlas_coord,
	t_img *sprite, t_ivec2 sprite_coord)
{
	const int	atl_idx = calc_px_pos(atlas, atlas_coord.x, atlas_coord.y);
	const int	spr_idx = calc_px_pos(sprite, sprite_coord.x, sprite_coord.y);

	atlas->data[atl_idx + 0] = sprite->data[spr_idx + 0];
	atlas->data[atl_idx + 1] = sprite->data[spr_idx + 1];
	atlas->data[atl_idx + 2] = sprite->data[spr_idx + 2];
	atlas->data[atl_idx + 3] = sprite->data[spr_idx + 3];
}

/**
 * @brief It will overwrite the game->frame with the px from the sprite_buf, will
 * traverse the spritebuff cols first, starting from the x coords given,
 * for y it will always place it at the bottom.
 * It will ignore sprite_buf black px and threat them as transparent.
 * @param game game obj
 * @param sprite sprite obj
 * @param startingfrom_x
 */
void	sprite_loader(t_var *game, t_img *sprite, int startingfrom_x)
{
	int	x;
	int	y;

	y = 0;
	while (y < sprite->height)
	{
		x = 0;
		while (x < sprite->width)
		{
			if (!is_px_black(sprite->image->data, calc_px_pos(sprite, x, y)))
			{
				copy_px_to_img(game->frame, (t_ivec2){startingfrom_x + x,
					(game->cnf.window_height - sprite->height) + y},
					sprite, (t_ivec2){x, y});
			}
			x++;
		}
		y++;
	}
}

void	render_sprites(t_var *game, t_playersprites *hands_sprites)
{
	if (!hands_sprites || !hands_sprites->active)
		return ;
	sprite_loader(game, hands_sprites->active, hands_sprites->active_screen_x);
}
