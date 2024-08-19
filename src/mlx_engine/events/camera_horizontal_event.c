/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_horizontal_event.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:07:52 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/19 15:29:58 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// LISTENERS--------------------------------------------------------------------
void	camera_h_event_pressed(int keycode, t_var *game)
{
	if (keycode == LOOK_LEFT)
		game->event.rot_left = true;
	if (keycode == LOOK_RIGHT)
		game->event.rot_right = true;
}

void	camera_h_event_released(int keycode, t_var *game)
{
	if (keycode == LOOK_LEFT)
		game->event.rot_left = false;
	if (keycode == LOOK_RIGHT)
		game->event.rot_right = false;
}

// HANDLERS---------------------------------------------------------------------

static void	handle_camera_rotation(t_var *game, double dir)
{
	const double	cos_res = cos(dir * game->cnf.rot_lateral_speed);
	const double	sin_res = sin(dir * game->cnf.rot_lateral_speed);
	double			old_dir_y;
	double			old_plane_x;

	old_dir_y = game->player.dir_y;
	game->player.dir_y = old_dir_y * cos_res - game->player.dir_x * sin_res;
	game->player.dir_x = old_dir_y * sin_res + game->player.dir_x * cos_res;
	old_plane_x = game->engine.plane.x;
	game->engine.plane.x = game->engine.plane.x * cos_res
		- game->engine.plane.y * sin_res;
	game->engine.plane.y = old_plane_x * sin_res
		+ game->engine.plane.y * cos_res;
}

void	handle_horizontal_rotation(t_var *game)
{
	const bool	ismouse_inframe = is_mouse_inside_frame(game);

	if (ismouse_inframe && WITH_BONUS)
	{
		if (game->event.mouse_rot_left)
			handle_camera_rotation(game, 1.15f);
		if (game->event.mouse_rot_right)
			handle_camera_rotation(game, -1.15f);
		return ;
	}
	if (game->event.rot_left)
		handle_camera_rotation(game, 1.0);
	if (game->event.rot_right)
		handle_camera_rotation(game, -1.0);
}
