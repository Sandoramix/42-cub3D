/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 22:20:36 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/27 06:02:06 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	copy_px_to_img(t_img *dest, t_ivec2 dest_coord,
	t_img *from, t_ivec2 from_coord)
{
	const int	d_idx = bytearray_coord_idx(dest, dest_coord);
	const int	f_idx = bytearray_coord_idx(from, from_coord);

	*((t_uint *)(dest->data + d_idx)) = *((t_uint *)(from->data + f_idx));
}

/**
 * @brief Draw a sprite on the game's frame.
 * It will ignore `excluded_color` px and threat them as transparent.
 * @param game game obj
 * @param sprite sprite obj
 * @param global_pos global position of the sprite on the game's frame.
 * @param excluded_color color to ignore.
 */
void	draw_exclusive_sprite(t_var *game, t_img *sprite, t_ivec2 global_pos,
	t_argb excluded_color)
{
	t_argb	color;
	int		x;
	int		y;

	y = 0;
	while (y < sprite->height)
	{
		x = 0;
		while (x < sprite->width)
		{
			color = bytearray_get_color(sprite, (t_ivec2){x, y});
			if (!are_colors_equal(excluded_color, color))
			{
				copy_px_to_img(game->frame, (t_ivec2)
				{global_pos.x + x, global_pos.y + y}, sprite, (t_ivec2){x, y});
			}
			x++;
		}
		y++;
	}
}

/**
 * @brief Draw a sprite on the game's frame.
 * @param game game obj
 * @param sprite sprite obj
 * @param global_pos global position of the sprite on the game's frame.
 */
void	draw_sprite(t_var *game, t_img *sprite, t_ivec2 global_pos)
{
	int	x;
	int	y;

	y = 0;
	while (y < sprite->height)
	{
		x = 0;
		while (x < sprite->width)
		{
			copy_px_to_img(game->frame, (t_ivec2)
			{global_pos.x + x, global_pos.y + y}, sprite, (t_ivec2){x, y});
			x++;
		}
		y++;
	}
}

void	render_extra_sprites(t_var *game, t_playersprites *hands_sprites)
{
	if (!hands_sprites || !hands_sprites->active_img)
		return ;
	draw_exclusive_sprite(game, hands_sprites->active_img,
		hands_sprites->active_coords, hex_to_argb(0x000000));
}
