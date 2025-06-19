/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_crosshair.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 02:11:13 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 15:24:59 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

char		*dbg_render_player_pos(t_var *game);
char		*dbg_render_player_angle(t_var *game);

static char	*dbg_render_fps(t_var *game)
{
	char	*text;
	char	*num;

	num = ft_itoa(1 / game->deltatime);
	text = str_join("FPS: ", num);
	free(num);
	return (text);
}

static char	*dbg_render_mousepos(t_var *game)
{
	char	*pos_x;
	char	*pos_y;
	char	*final;

	pos_x = ft_ftoa(game->mousepos.x, 2);
	pos_y = ft_ftoa(game->mousepos.y, 2);
	final = str_join("Mouse X: ", pos_x);
	final = str_freejoin(final, " Y: ");
	final = str_freejoin(final, pos_y);
	free(pos_x);
	free(pos_y);
	return (final);
}

static char	**allocate_infos(t_var *game)
{
	char	**res;

	res = ft_calloc(6, sizeof(char *));
	if (!res)
		return (pf_errcode(E_MALLOC), cleanup(game, true, 1), NULL);
	res[0] = str_dup("DEBUG_MODE");
	res[1] = dbg_render_fps(game);
	res[2] = dbg_render_player_pos(game);
	res[3] = dbg_render_player_angle(game);
	res[4] = dbg_render_mousepos(game);
	return (res);
}

void	debug_info(t_var *game)
{
	char	**infos;

	if (!game->event.debug)
		return ;
	infos = allocate_infos(game);
	mlx_string_put(game->mlx, game->mlx_win, 16,
		game->cnf.window_height - 200, 0xFFFFFF, infos[0]);
	mlx_string_put(game->mlx, game->mlx_win, 16,
		game->cnf.window_height - 80, 0xFFFFFF, infos[1]);
	mlx_string_put(game->mlx, game->mlx_win, 16,
		game->cnf.window_height - 100, 0xFFFFFF, infos[2]);
	mlx_string_put(game->mlx, game->mlx_win, 16,
		game->cnf.window_height - 120, 0xFFFFFF, infos[3]);
	mlx_string_put(game->mlx, game->mlx_win, 16,
		game->cnf.window_height - 60, 0xFFFFFF, infos[4]);
	str_freemtx(infos);
}
