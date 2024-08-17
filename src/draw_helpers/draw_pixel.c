/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:57:33 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 15:54:05 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// TODO: it should accept an "t_img" and update it's pixels

/*
Draw, or said better, put a color inside the "general" image's buffer
which is an array of 4 bytes per cell: red-green-blue-alpha colors.
Goodbye matrixes, welcome bytearrays.
*/
void	draw_pixel_rgb(t_var *game, int x, int y, t_rgba rgba)
{
	char	*dst;

	dst = game->frame->data
		+ (y * game->frame->size_line + x * (game->frame->bpp / 8));
	dst[0] = rgba.red;
	dst[1] = rgba.green;
	dst[2] = rgba.blue;
	dst[3] = rgba.alpha;
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
	draw_pixel_rgb(game, x, y, hex_to_rgba(color));
}
