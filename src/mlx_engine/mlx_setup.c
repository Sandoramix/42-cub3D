/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:31:23 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/14 01:20:53 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	init_screensize(t_var *game, t_config *cnf)
{
	if (WINDOW_HEIGHT <= 0 || WINDOW_WIDTH <= 0)
	{
		mlx_get_screen_size(game->mlx, &cnf->win_width,
			&cnf->win_height);
		return ;
	}
	cnf->win_width = WINDOW_WIDTH;
	cnf->win_height = WINDOW_HEIGHT;
}

static t_state	init_mlx(t_var *game, t_config *cnf)
{
	init_screensize(game, cnf);
	game->mlx_win = mlx_new_window(game->mlx, cnf->win_width, cnf->win_height,
			cnf->defaults.window_name);
	if (!game->mlx_win)
		return (pf_errcode(E_MLXWIN), cleanup(game, true, 1), KO);
	return (OK);
}

static t_state	init_base_images(t_var *game, t_config *cnf)
{
	game->img = mlx_new_image(game->mlx, cnf->win_width, cnf->win_height);
	if (!game->img)
		return (pf_errcode(E_MLXIMG), cleanup(game, true, 1), KO);
	game->buffer = mlx_get_data_addr(game->img, &game->bpp,
			&game->line_bytes, &game->endian);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
	cnf->forearm = mlx_xpm_file_to_image(game->mlx,
			"assets/sprites/forearms.xpm", &cnf->_w, &cnf->_h);
	if (!cnf->forearm)
		return (pf_errcode(E_MLXIMG), cleanup(game, true, 1), KO);
	cnf->forearm_buff = mlx_get_data_addr(cnf->forearm, &game->bpp,
			&game->line_bytes, &game->endian);
	if (!cnf->forearm_buff)
		return (pf_errcode(E_MLXIMG), cleanup(game, true, 1), KO);
	return (OK);
}

t_state	mlx_setup(t_var *game)
{
	init_mlx(game, &game->config);
	init_base_images(game, &game->config);
	mlx_hook(game->mlx_win, KeyPress, KeyPressMask, &on_keypress, game);
	mlx_hook(game->mlx_win, KeyRelease, KeyReleaseMask, &on_keyrelease, game);
	mlx_hook(game->mlx_win, DestroyNotify, DestroyAll, mlx_loop_end, game->mlx);
	mlx_loop_hook(game->mlx, &game_loop, game);
	return (OK);
}
