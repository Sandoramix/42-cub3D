/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 13:46:14 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/18 14:25:07 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

bool	is_mouse_inside_frame(t_var *game)
{
	return (game->mousepos.x >= 0 && game->mousepos.y >= 0
		&& game->mousepos.x < game->frame->width
		&& game->mousepos.y < game->frame->height);
}
