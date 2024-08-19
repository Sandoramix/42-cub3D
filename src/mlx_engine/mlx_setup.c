/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:31:23 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/19 15:33:20 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	init_screensize(t_var *game, t_config *cnf)
{
	if (WINDOW_HEIGHT <= 0 || WINDOW_WIDTH <= 0)
	{
		mlx_get_screen_size(game->mlx, &cnf->window_width,
			&cnf->window_height);
		return ;
	}
	cnf->window_width = WINDOW_WIDTH;
	cnf->window_height = WINDOW_HEIGHT;
}

static t_state	init_mlx(t_var *game, t_config *cnf)
{
	init_screensize(game, cnf);
	game->mlx_win = mlx_new_window(game->mlx,
			cnf->window_width, cnf->window_height, cnf->window_name);
	game->mousepos = (t_point){-1, -1};
	if (!game->mlx_win)
		return (pf_errcode(E_MLXWIN), cleanup(game, true, 1), KO);
	return (OK);
}

static t_state	mlx_load_sprites(t_var *game, struct s_playersprites *cnf)
{
	cnf->rest = mlx_xpm_file_to_image(game->mlx,
			TEXTURE_RESTING_R, &game->cnf._w, &game->cnf._h);
	if (!cnf->rest)
		return (pf_errcode(E_MLXIMG), cleanup(game, true, 1), KO);
	cnf->block = mlx_xpm_file_to_image(game->mlx,
			TEXTURE_BLOCK_R, &game->cnf._w, &game->cnf._h);
	if (!cnf->block)
		return (pf_errcode(E_MLXIMG), cleanup(game, true, 1), KO);
	return (OK);
}

static t_state	init_base_images(t_var *game, t_config *cnf)
{
	game->frame = mlx_new_image(game->mlx,
			cnf->window_width, cnf->window_height);
	if (!game->frame)
		return (pf_errcode(E_MLXIMG), cleanup(game, true, 1), KO);
	mlx_load_sprites(game, &cnf->hands_sprites);
	return (OK);
}

t_state	mlx_setup(t_var *game)
{
	init_mlx(game, &game->cnf);
	init_base_images(game, &game->cnf);
	mlx_hook(game->mlx_win, KeyPress, KeyPressMask, &on_keypress, game);
	mlx_hook(game->mlx_win, KeyRelease, KeyReleaseMask, &on_keyrelease, game);
	mlx_hook(game->mlx_win, DestroyNotify, DestroyAll, mlx_loop_end, game->mlx);
	mlx_loop_hook(game->mlx, &game_loop, game);
	return (OK);
}
