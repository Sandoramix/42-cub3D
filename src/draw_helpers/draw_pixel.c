/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:57:33 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/27 11:20:01 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// TODO: it should accept an "t_img" and update it's pixels

void	draw_pixel_rgb(t_var *game, t_ivec2 pos, t_argb argb)
{
	int	f_idx;

	if (pos.x < 0 || pos.y < 0
		|| pos.x >= game->frame->width || pos.y >= game->frame->height)
		return ;
	f_idx = bytearray_coord_idx(game->frame, pos);
	*((t_uint *)(game->frame->data + f_idx)) = argb.hex;
}

/**
 * @brief Draw, or said better, put a color inside the game's frame's buffer,
 * but it excludes the black pixels.
 *
 */
void	draw_exclusive_pixel_rgb(t_var *game, t_ivec2 pos, t_argb argb)
{
	int	f_idx;

	if (argb.hex == 0)
		return ;
	if (pos.x < 0 || pos.y < 0
		|| pos.x >= game->frame->width || pos.y >= game->frame->height)
		return ;
	f_idx = bytearray_coord_idx(game->frame, pos);
	*((t_uint *)(game->frame->data + f_idx)) = argb.hex;
}

/**
 * Draw, or said better, put a color inside the "general" image's buffer
 * which is an array of 4 bytes per cell: red-green-blue-alpha colors.
 * Goodbye matrixes, welcome bytearrays.
 *
 * @deprecated
 * You should use `draw_pixel_rgb`
*/
void	draw_pixel(t_var *game, int x, int y, t_uint color)
{
	draw_pixel_rgb(game, (t_ivec2){x, y}, hex_to_argb(color));
}
