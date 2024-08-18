/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_vertical_event.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:07:52 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/18 14:59:12 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// LISTENERS--------------------------------------------------------------------
void	camera_v_event_pressed(int keycode, t_var *game)
{
	if (keycode == LOOK_UP)
		game->event.rot_up = true;
	if (keycode == LOOK_DOWN)
		game->event.rot_down = true;
}

void	camera_v_event_released(int keycode, t_var *game)
{
	if (keycode == LOOK_UP)
		game->event.rot_up = false;
	if (keycode == LOOK_DOWN)
		game->event.rot_down = false;
}

// HANDLERS---------------------------------------------------------------------

static void	apply_smoothness(t_var *game, t_player *player)
{
	const double	smoothness = 0.9;

	if (!game->event.rot_up && !game->event.rot_down)
	{
		if (player->offset > 0)
			player->offset = fmax(player->offset * smoothness, 0.0);
		else if (player->offset < 0)
			player->offset = fmin(player->offset * smoothness, 0.0);
	}
	else
	{
		if (player->offset >= game->cnf.camera_vert_rot_max - 0.1)
			player->offset = game->cnf.camera_vert_rot_max;
		else if (player->offset <= game->cnf.camera_vert_rot_min + 0.1)
			player->offset = game->cnf.camera_vert_rot_min;
	}
}

void	handle_vertical_rotation(t_var *game)
{
	t_player	*player;

	player = &game->player;
	if (game->event.rot_up)
	{
		player->offset += game->cnf.rot_vertical_speed * game->deltatime;
		if (player->offset > game->cnf.camera_vert_rot_max)
			player->offset = game->cnf.camera_vert_rot_max;
	}
	if (game->event.rot_down)
	{
		player->offset -= game->cnf.rot_vertical_speed * game->deltatime;
		if (player->offset < game->cnf.camera_vert_rot_min)
			player->offset = game->cnf.camera_vert_rot_min;
	}
	apply_smoothness(game, player);
}
