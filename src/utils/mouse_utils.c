/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 13:46:14 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/19 15:32:38 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

bool	is_mouse_inside_frame(t_var *game)
{
	mlx_mouse_get_pos(game->mlx, game->mlx_win,
		&game->mousepos.x, &game->mousepos.y);
	return (game->mousepos.x >= 0 && game->mousepos.y >= 0
		&& game->mousepos.x < game->frame->width
		&& game->mousepos.y < game->frame->height);
}
