/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:29:16 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 01:30:17 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	draw_line_rgb(t_var *game, t_dpoint start, t_dpoint end, t_rgba rgb)
{
	t_dpoint	delta;
	t_dpoint	increment;
	t_dpoint	next_point;
	int			pixels;
	int			counter;

	delta = (t_dpoint){end.x - start.x, end.y - start.y};
	pixels = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	increment = (t_dpoint){delta.x / pixels, delta.y / pixels};
	next_point = (t_dpoint){start.x, start.y};
	counter = -1;
	while (++counter < pixels && is_point_inside_window(game, next_point))
	{
		draw_pixel_rgb(game, next_point.x, next_point.y, rgb);
		next_point.x += increment.x;
		next_point.y += increment.y;
	}
}
