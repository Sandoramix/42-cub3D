/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:31:23 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/15 14:50:43 by odudniak         ###   ########.fr       */
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

static t_state	mlx_load_sprites(t_var *game, struct s_cnfsprites *cnf)
{
	cnf->rest = mlx_xpm_file_to_image(game->mlx,
			TEXTURE_RESTING_R, &game->config._w, &game->config._h);
	if (!cnf->rest)
		return (pf_errcode(E_MLXIMG), cleanup(game, true, 1), KO);
	cnf->block = mlx_xpm_file_to_image(game->mlx,
			TEXTURE_BLOCK_R, &game->config._w, &game->config._h);
	if (!cnf->block)
		return (pf_errcode(E_MLXIMG), cleanup(game, true, 1), KO);
	cnf->attack0 = mlx_xpm_file_to_image(game->mlx,
			TEXTURE_ATTACK0_R, &game->config._w, &game->config._h);
	if (!cnf->attack0)
		return (pf_errcode(E_MLXIMG), cleanup(game, true, 1), KO);
	cnf->attack1 = mlx_xpm_file_to_image(game->mlx,
			TEXTURE_ATTACK1_R, &game->config._w, &game->config._h);
	if (!cnf->attack1)
		return (pf_errcode(E_MLXIMG), cleanup(game, true, 1), KO);
	cnf->attack2 = mlx_xpm_file_to_image(game->mlx,
			TEXTURE_ATTACK2_R, &game->config._w, &game->config._h);
	if (!cnf->attack2)
		return (pf_errcode(E_MLXIMG), cleanup(game, true, 1), KO);
	return (OK);
}

//mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
static t_state	init_base_images(t_var *game, t_config *cnf)
{
	game->img = mlx_new_image(game->mlx, cnf->win_width, cnf->win_height);
	if (!game->img)
		return (pf_errcode(E_MLXIMG), cleanup(game, true, 1), KO);
	game->buffer = mlx_get_data_addr(game->img, &game->bpp,
			&game->line_bytes, &game->endian);
	mlx_load_sprites(game, &cnf->hands_sprites);
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
