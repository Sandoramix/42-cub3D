/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deltatime.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:47:18 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/14 02:33:05 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

double	delta_time(t_var *game, bool normalize)
{
	const float				min_limit = 0.0167f;
	const float				max_limit = 100.0f;
	static struct timeval	last = {0, 0};
	struct timeval			current;
	double					delta_time;

	gettimeofday(&current, NULL);
	if (last.tv_sec == 0 && last.tv_usec == 0)
	{
		last = current;
		game->deltatime = 0;
		return (0.0);
	}
	delta_time = (current.tv_sec - last.tv_sec)
		+ (current.tv_usec - last.tv_usec) / 1000000.0;
	if (normalize && delta_time < min_limit)
		delta_time = min_limit;
	if (normalize && delta_time > max_limit)
		delta_time = max_limit;
	last = current;
	game->deltatime = delta_time;
	return (delta_time);
}
