/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:46:42 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/15 10:36:30 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

double	pi(void)
{
	return (acos(-1.0));
}

double	angle_to_radiant(double angle)
{
	return (angle * (pi() / 180));
}

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

double	normalize_to_one(double num)
{
	return (num - floor(num));
}
