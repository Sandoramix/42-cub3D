/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:57:33 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/14 02:10:23 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// TODO: it should accept an "t_img" and update it's pixels

/*
Draw, or said better, put a color inside the "general" image's buffer
which is an array of 4 bytes per cell: red-green-blue-alpha colors.
Goodbye matrixes, welcome bytearrays.
*/
void	draw_pixel_rgb(t_var *game, int x, int y, t_rgb rgb)
{
	char	*dst;

	dst = game->buffer + (y * game->line_bytes + x * (game->bpp / 8));
	dst[0] = rgb.color.red;
	dst[1] = rgb.color.green;
	dst[2] = rgb.color.blue;
	dst[3] = rgb.color.alpha;
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
	draw_pixel_rgb(game, x, y,  to_rgb(color));
}
