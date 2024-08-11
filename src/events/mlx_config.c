/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:11:39 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/09 15:40:38 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>



int	config_event_handling(t_var *game)
{
	if (!mlx_hook(game->mlx_win, KeyPress, KeyPressMask,
			&key_press, game))
		return (pf_errcode(E_MLX), cleanup(game, true, 1), 1);
	if (!mlx_hook(game->mlx_win, KeyRelease, KeyReleaseMask,
			&key_release, game))
		return (pf_errcode(E_MLX), cleanup(game, true, 1), 1);
	if (!mlx_hook(game->mlx_win, DestroyNotify, DestroyAll,
			mlx_loop_end, game->mlx))
		return (pf_errcode(E_MLX), cleanup(game, true, 1), 1);
	mlx_loop_hook(game->mlx, &game_loop, game);
	return (OK);
}

t_state	mlx_setup(t_var *game)
{
	mlx_get_screen_size(game->mlx, &game->config.win_width,
		&game->config.win_height);
	game->mlx_win = mlx_new_window(game->mlx,
			game->config.win_width, game->config.win_height, WINDOW_NAME);
	if (!game->mlx_win)
		return (pf_errcode(E_MLXWIN), cleanup(game, true, 1), KO);
	game->img = mlx_new_image(game->mlx, game->config.win_width,
			game->config.win_height);
	if (!game->img)
		return (pf_errcode(E_MLXIMG), cleanup(game, true, 1), KO);
	game->buffer = mlx_get_data_addr(game->img, &game->bpp,
			&game->line_bytes, &game->endian);
	config_event_handling(game);
	return (OK);
}
