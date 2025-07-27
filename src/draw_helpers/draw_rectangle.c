/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rectangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:56:14 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/27 11:17:20 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// TODO: it should accept an "t_img" and update it's pixels

/**
 * @brief Draw a rectangle with the given start and end coordinates.
 * It will also swap the coordinates if the start is bigger than the end.
 * @param game game struct.
 * @param start start coordinate.
 * @param end end coordinate.
 * @param rgb rgb color.
 * @note #### TODO: it should accept an "t_img" and update it's pixels
 */
void	draw_rectangle_rgb(t_var *game, t_ivec2 start, t_ivec2 end, t_argb rgb)
{
	int			start_x;

	if (start.x > end.x)
		int_swap(&start.x, &end.x);
	if (start.y > end.y)
		int_swap(&start.y, &end.y);
	start_x = start.x;
	while (start.y <= end.y)
	{
		start.x = start_x;
		while (start.x <= end.x)
		{
			draw_pixel_rgb(game, start, rgb);
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
	draw_rectangle_rgb(game, start, end, hex_to_argb(color));
}
