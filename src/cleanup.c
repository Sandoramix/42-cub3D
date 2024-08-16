/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:11:29 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 00:36:39 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// TODO: SHALL YOU FREE THE WORLD (and every malloc i've done)

static void	safe_destroy_img(void *mlx, t_img *img)
{
	if (!mlx)
		return ;
	if (img)
		mlx_destroy_image(mlx, img);
}

static void	free_config(t_var *game)
{
	if (game->mlx)
	{
		safe_destroy_img(game->mlx, game->config.wall_nord);
		safe_destroy_img(game->mlx, game->config.wall_east);
		safe_destroy_img(game->mlx, game->config.wall_west);
		safe_destroy_img(game->mlx, game->config.wall_south);
		safe_destroy_img(game->mlx, game->config.hands_sprites.attack0);
		safe_destroy_img(game->mlx, game->config.hands_sprites.attack1);
		safe_destroy_img(game->mlx, game->config.hands_sprites.attack2);
		safe_destroy_img(game->mlx, game->config.hands_sprites.rest);
		safe_destroy_img(game->mlx, game->config.hands_sprites.block);
	}
	str_freemtx(game->map.filedata);
	str_freemtx(game->map.map);
	free(game->config.ceiling_raw);
	free(game->config.floor_raw);
	free(game->config.wall_nord_path);
	free(game->config.wall_east_path);
	free(game->config.wall_west_path);
	free(game->config.wall_south_path);
	//TODO: REMOVE ME
	safe_destroy_img(game->mlx, game->img);
}

int	cleanup(t_var *game, bool should_exit, int statuscode)
{
	free_config(game);
	if (game->mlx)
	{
		if (game->mlx_win)
		{
			mlx_clear_window(game->mlx, game->mlx_win);
			mlx_destroy_window(game->mlx, game->mlx_win);
		}
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (should_exit)
		exit(statuscode);
	return (statuscode);
}
