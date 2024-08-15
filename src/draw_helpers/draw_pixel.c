/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:57:33 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/15 10:36:14 by rileone          ###   ########.fr       */
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

	dst = game->buffer + (y * game->line_bytes + x * (game->bpp / 8));
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
