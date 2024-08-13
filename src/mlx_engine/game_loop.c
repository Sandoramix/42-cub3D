/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:29:26 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/13 12:40:44 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	render_fps(t_var *game)
{
	char	*text;
	char	*num;

	num = ft_itoa(1 / game->deltatime);
	text = str_join("FPS: ", num);
	free(num);
	mlx_string_put(game->mlx, game->mlx_win, 16, game->config.win_height - 16, 0xFFFFFF, text);
	free(text);
}

int	game_loop(t_var *game)
{
	delta_time(game);
	handle_player_movement(game);
	handle_player_rotation(game);
	//render_background(game);
	render_walls(game);
	render_minimap(game);
	render_sprites(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
	render_fps(game);
	return (1);
}
