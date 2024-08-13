/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:29:26 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/12 14:46:22 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	game_loop(t_var *game)
{
	delta_time(game);
	handle_player_movement(game);
	handle_player_rotation(game);
	//render_background(game);
	render_walls(game);
	render_minimap(game);
	if (mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0))
		return (pf_errcode(E_MLXIMG), cleanup(game, true, 1), 1);
	return (1);
}
