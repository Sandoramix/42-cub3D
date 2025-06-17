/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rectangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:56:14 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/15 10:35:33 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// TODO: it should accept an "t_img" and update it's pixels

void	draw_rectangle_rgb(t_var *game, t_ivec2 start, t_ivec2 end, t_rgba rgb)
{
	const int	start_x = start.x;

	while (start.y <= end.y)
	{
		start.x = start_x;
		while (start.x <= end.x)
		{
			draw_pixel_rgb(game, start.x, start.y, rgb);
			start.x++;
		}
		start.y++;
	}
}

/**
 * @deprecated
 * You should use `draw_rectangle_rgb`
 */
void	draw_rectangle(t_var *game, t_ivec2 start, t_ivec2 end, t_uint color)
{
	draw_rectangle_rgb(game, start, end, hex_to_rgba(color));
}
