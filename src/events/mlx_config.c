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

int	game_loop(t_var *game)
{
	delta_time(game);
	handle_player_movement(game);
	handle_player_rotation(game);

	rendering(game);
	return (1);
}

void	config_event_handling(t_var *game)
{
	mlx_hook(game->mlx_win, KeyPress, KeyPressMask, &key_press, game);
	mlx_hook(game->mlx_win, KeyRelease, KeyReleaseMask, &key_release, game);
	mlx_hook(game->mlx_win, DestroyNotify, DestroyAll, mlx_loop_end, game->mlx);
	mlx_loop_hook(game->mlx, &game_loop, game);
}

t_state	mlx_setup(t_var *game)
{
	mlx_get_screen_size(game->mlx, &game->config.win_width,
		&game->config.win_height);
	//game->config.win_height = 720.;
	//game->config.win_width = 1280.;

	game->mlx_win = mlx_new_window(game->mlx,
			game->config.win_width, game->config.win_height, WINDOW_NAME);
	ft_printf("WIN_H[%d], WIN_W[%d]\n",
		game->config.win_height, game->config.win_width);
	if (!game->mlx_win)
		return (pf_errcode(E_MLXWIN), cleanup(game, true, 1), KO);
	game->img = mlx_new_image(game->mlx, game->config.win_width,
			game->config.win_height);
	if (!game->img)
		return (pf_errcode(E_MLXIMG), cleanup(game, true, 1), KO);
	game->buffer = mlx_get_data_addr(game->img, &game->bpp,
			&game->line_bytes, &game->endian);
	rendering(game);
	config_event_handling(game);
	return (OK);
}
