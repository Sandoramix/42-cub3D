/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:46:42 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/13 21:10:43 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

double pi()
{
	return (acos(-1.0));
}

double from_angle_to_radiant(double angle)
{
	return (angle * (pi() / 180));
}

t_rgb	to_rgb(unsigned int color)
{
	t_rgb	res;

	res.hex = color;
	res.color.alpha = color >> 24 & 0xFF;
	res.color.blue = color >> 16 & 0xFF;
	res.color.green = color >> 8 & 0xFF;
	res.color.red = color & 0xFF;
	return (res);
}

unsigned int	color_to_hex(t_color color)
{
	return ((color.alpha << 24) | (color.blue << 16) | (color.green << 8)
		| color.red);
}
