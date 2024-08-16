/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 23:55:04 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/16 23:55:19 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_rgba	hex_to_rgba(t_uint color)
{
	t_rgba	res;

	res.hex = color;
	res.alpha = color >> 24 & 0xFF;
	res.blue = color >> 16 & 0xFF;
	res.green = color >> 8 & 0xFF;
	res.red = color & 0xFF;
	return (res);
}

t_uint	rgba_to_hex(t_rgba color)
{
	return ((color.alpha << 24) | (color.blue << 16) | (color.green << 8)
		| color.red);
}
