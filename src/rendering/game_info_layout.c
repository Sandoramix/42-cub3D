/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_info_layout.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 05:15:37 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/27 05:22:16 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	game_info_layout(t_var *game)
{
	void		*mlx_win;
	const int	bottom_offset = game->cnf.window_height - 4;
	char		*fps;

	mlx_win = game->mlx_win;
	fps = ft_itoa(1 / game->deltatime);
	mlx_string_put(game->mlx, mlx_win, 4, bottom_offset, 0xFFFFFF, "FPS: ");
	mlx_string_put(game->mlx, mlx_win, 32, bottom_offset, 0xFFFFFF, fps);
	free(fps);
}