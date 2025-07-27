/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 11:28:56 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/27 11:28:57 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	draw_circle_rgb(t_var *game, t_ivec2 center, int radius, t_argb rgb)
{
	int	x;
	int	y;
	int	x_squared;
	int	y_squared;
	int	radius_squared;

	if (radius < 0)
		return ;
	radius_squared = radius * radius;
	x = -radius - 1;
	while (++x <= radius)
	{
		y = -radius - 1;
		x_squared = x * x;
		while (++y <= radius)
		{
			y_squared = y * y;
			if (x_squared + y_squared <= radius_squared)
				draw_pixel_rgb(game,
					(t_ivec2){.x = center.x + x, .y = center.y + y}, rgb);
		}
	}
}
