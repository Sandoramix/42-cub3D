/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:59:50 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/02 18:18:45 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <mlx.h>
# include <mlx_int.h>

# include <cub3D_settings.h>
# include <cub3D_structs.h>

// TODO split each category in separate file if (it will) needed.

// PARSING----------------------------------------------------------------------
t_state	parse(t_var *game, int ac, char **av);
//------------------------------------------------------------------------------
//UTILS

void	print_missing_config(t_var *game);
bool	is_config_missing(t_var *game);
//------------------------------------------------------------------------------
// RAYCASTING-------------------------------------------------------------------
void	raycasting(t_var *game);
void	calc_initial_step_intial_raylen(t_var *game);
void	increase_raylen(t_var *game);
void	calc_distance_from_wall(t_var *game);
void	put_line_h_in_perspective(t_var *game);
//------------------------------------------------------------------------------

double	delta_time(t_var *game);

// MLX CONFIGURATION -----------------------------------------------------------
void	mlx_configuration(t_var *game);
//------------------------------------------------------------------------------

// EVENTS HANDLING--------------------------------------------------------------
int		game_loop(t_var *game);
void	rotate_camera(t_var *game, int rotation_dir);
int		key_press(int keycode, t_var *game);
int		key_release(int keycode, t_var *game);

//------------------------------------------------------------------------------

#endif