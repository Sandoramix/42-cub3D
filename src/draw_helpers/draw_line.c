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

void	draw_line_rgb(t_var *game, t_dvec2 start, t_dvec2 end, t_rgba rgb)
{
	t_dvec2	delta;
	t_dvec2	increment;
	t_dvec2	next_point;
	int			pixels;
	int			counter;

	delta = (t_dvec2){end.x - start.x, end.y - start.y};
	pixels = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	increment = (t_dvec2){delta.x / pixels, delta.y / pixels};
	next_point = (t_dvec2){start.x, start.y};
	counter = -1;
	while (++counter < pixels && is_point_inside_window(game, next_point))
	{
		draw_pixel_rgb(game, next_point.x, next_point.y, rgb);
		next_point.x += increment.x;
		next_point.y += increment.y;
	}
}
