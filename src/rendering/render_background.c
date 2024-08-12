/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:51:44 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/11 23:51:54 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void render_background(t_var *game)
{
	const t_point	ceiling_start = (t_point){0, 0};
	const t_point	ceiling_end = (t_point){game->config.win_width,
		game->config.win_height / 2 + game->player.offset};
	const t_point	floor_start = (t_point){0,
		game->config.win_height / 2 + game->player.offset};
	const t_point	floor_end = (t_point){game->config.win_width,
		game->config.win_height};

	draw_rectangle(game, ceiling_start, ceiling_end,
		(t_rgb){game->config.ceiling.hex});
	draw_rectangle(game, floor_start, floor_end,
		(t_rgb){game->config.floor.hex});
}