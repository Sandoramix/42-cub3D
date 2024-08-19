/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:59:50 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/19 16:11:43 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <mlx.h>

# ifdef __linux__
#  include <mlx_int.h>
# endif

# include <cub3D_settings.h>
# include <cub3D_structs.h>
# include <cub3D_utils.h>
# include <cub3D_rendering.h>

// CONFIGURATIONS --------------------------------------------------------------
void	init_config(t_config *cnf);
t_state	mlx_setup(t_var *g);

//DEBUG----------------------------------------------------------------------
void	debug_info(t_var *g);
//------------------------------------------------------------------------------

//-PARSING----------------------------------------------------------------------
t_state	parse(t_var *g, int ac, char **av);
//------------------------------------------------------------------------------
int		game_loop(t_var *g);
int		on_keypress(int keycode, t_var *game);
int		on_keyrelease(int keycode, t_var *game);

// EVENT LISTENERS--------------------------------------------------------------
void	player_sprites_event_pressed(int keycode, t_var *game);
void	player_sprites_event_released(int keycode, t_var *game);

void	camera_h_event_pressed(int keycode, t_var *game);
void	camera_h_event_released(int keycode, t_var *game);
void	camera_v_event_pressed(int keycode, t_var *game);
void	camera_v_event_released(int keycode, t_var *game);

void	movement_h_event_pressed(int keycode, t_var *game);
void	movement_h_event_released(int keycode, t_var *game);
void	movement_v_event_pressed(int keycode, t_var *game);
void	movement_v_event_released(int keycode, t_var *game);

// EVENT HANDLERS---------------------------------------------------------------
void	handle_mouse_rotation(t_var *game);

void	handle_player_sprites(t_var *game);

void	handle_vertical_movement(t_var *game);
void	handle_horizontal_movement(t_var *game);

void	handle_vertical_rotation(t_var *game);
void	handle_horizontal_rotation(t_var *game);
//------------------------------------------------------------------------------

#endif