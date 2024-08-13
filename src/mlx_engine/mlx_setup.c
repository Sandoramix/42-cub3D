/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:31:23 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/13 12:29:42 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	update_screensize(t_var *game)
{
	if (WINDOW_HEIGHT <= 0 || WINDOW_WIDTH <= 0)
	{
		mlx_get_screen_size(game->mlx, &game->config.win_width,
			&game->config.win_height);
		return ;
	}
	game->config.win_width = WINDOW_WIDTH;
	game->config.win_height = WINDOW_HEIGHT;
}

static t_state	mlx_init_values(t_var *game)
{
	update_screensize(game);
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
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
	game->config.forearm = mlx_xpm_file_to_image(game->mlx, "assets/sprites/forearms.xpm",
			&game->config._w, &game->config._h);
	if (!game->config.forearm)
		return (pf_errcode(E_MLXIMG), cleanup(game, true, 1), KO);
	game->engine.texture.text_array[0] = game->config.wall_nord;
	game->engine.texture.text_array[1] = game->config.wall_east;
	game->engine.texture.text_array[2] = game->config.wall_west;
	game->engine.texture.text_array[3] = game->config.wall_south;
	return (OK);
}

t_state	mlx_setup(t_var *game)
{
	mlx_init_values(game);
	mlx_hook(game->mlx_win, KeyPress, KeyPressMask, &key_press, game);
	mlx_hook(game->mlx_win, KeyRelease, KeyReleaseMask, &key_release, game);
	mlx_hook(game->mlx_win, DestroyNotify, DestroyAll, mlx_loop_end, game->mlx);
	mlx_loop_hook(game->mlx, &game_loop, game);
	return (OK);
}
