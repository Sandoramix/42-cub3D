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

char	*dbg_render_player_pos(t_var *game)
{
	char	*y_txt;
	char	*x_txt;
	char	*pos_x;
	char	*pos_y;
	char	*final;

	pos_x = ft_ftoa(game->player.pos.x, 2);
	pos_y = ft_ftoa(game->player.pos.y, 2);
	x_txt = str_join("X: ", pos_x);
	y_txt = str_join(" Y: ", pos_y);
	final = str_join(x_txt, y_txt);
	free(x_txt);
	free(pos_x);
	free(pos_y);
	free(y_txt);
	return (final);
}

char	*dbg_render_player_angle(t_var *game)
{
	char	*text;
	char	*num;

	num = ft_ftoa(atan2(game->player.dir.y, game->player.dir.x) * 180 / pi(),
			2);
	text = str_join("Angle: ", num);
	free(num);
	return (text);
}
