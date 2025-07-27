/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 23:55:04 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/27 06:02:46 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/**
 * @brief Compare two colors' values.
 * @param a first color
 * @param b second color
 * @return true if the colors are equal, false otherwise
 */
bool	are_colors_equal(t_argb a, t_argb b)
{
	return (a.hex == b.hex);
}

t_argb	hex_to_argb(t_uint color)
{
	t_argb	res;

	res.hex = color;
	res.alpha = color >> 24 & 0xFF;
	res.blue = color >> 16 & 0xFF;
	res.green = color >> 8 & 0xFF;
	res.red = color & 0xFF;
	return (res);
}

t_uint	argb_to_hex(t_argb color)
{
	return ((color.alpha << 24)
		| (color.blue << 16)
		| (color.green << 8)
		| color.red);
}
