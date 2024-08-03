/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:11:29 by odudniak          #+#    #+#             */
/*   Updated: 2024/07/31 17:53:35 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	cleanup(t_var *game, bool should_exit, int statuscode)
{
	str_freemtx(game->mapinfo.file_content);
	str_freemtx(game->mapinfo.map);

	if (game->mlx)
	{
		mlx_clear_window(game->mlx, game->win_ptr);
		mlx_destroy_window(game->mlx, game->win_ptr);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (should_exit)
		exit(statuscode);
	return (statuscode);
}