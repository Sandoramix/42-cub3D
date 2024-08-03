/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:11:29 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/03 13:36:11 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// TODO: SHALL YOU FREE THE WORLD (and every malloc i've done)

static void	free_config(t_var *game)
{
	if (game->mlx)
	{
		mlx_destroy_image(game->mlx, game->config.wall_nord);
		mlx_destroy_image(game->mlx, game->config.wall_east);
		mlx_destroy_image(game->mlx, game->config.wall_west);
		mlx_destroy_image(game->mlx, game->config.wall_south);
	}
	str_freemtx(game->mapinfo.file_content);
	str_freemtx(game->mapinfo.map);
	free(game->config.ceiling_raw);
	free(game->config.floor_raw);
	free(game->config.wall_nord_path);
	free(game->config.wall_east_path);
	free(game->config.wall_west_path);
	free(game->config.wall_south_path);
}

int	cleanup(t_var *game, bool should_exit, int statuscode)
{
	free_config(game);
	if (game->mlx)
	{
		mlx_clear_window(game->mlx, game->mlx_win);
		mlx_destroy_window(game->mlx, game->mlx_win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (should_exit)
		exit(statuscode);
	return (statuscode);
}