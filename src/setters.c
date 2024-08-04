/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:10:20 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/04 11:11:47 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	update_player(t_var *game, int x, int y, double angle)
{
	if (!game)
		return ;
	game->player.x = x;
	game->player.y = y;
	game->player.angle = angle;
}
