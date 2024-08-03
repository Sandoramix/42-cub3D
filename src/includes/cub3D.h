/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:59:50 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/03 13:37:56 by odudniak         ###   ########.fr       */
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

// TODO split each category in separate file if (it will) needed.

// PARSING----------------------------------------------------------------------
t_state	parse(t_var *game, int ac, char **av);
t_state	parse_configs(t_var *game);
// PARSING UTILS
char	**get_config_pointed_str(t_var *game, t_cnf type);
/**
 * @brief Get a pointer of given type's configuration, it can be either
 * `t_img *` or `t_rgb *`
 */
void	*get_config_pointed_data(t_var *game, t_cnf type);

t_cnf	parse_identify_cnf(char *line);
bool	parse_config_val_is_path(t_cnf type);
bool	is_filepath_valid(char *line, int line_n, char *path);
//------------------------------------------------------------------------------
//GENERIC UTILS

void	print_missing_config(t_var *game);
bool	is_config_missing(t_var *game);

//MLX UTILS
t_state	load_xpm_image(t_var *game, t_img **img, char *path);
//------------------------------------------------------------------------------
// RAYCASTING-------------------------------------------------------------------
void	raycasting(t_var *game);
void 	init_raycasting(t_var *game, int pixel_pos_x);
void	increase_raylen(t_var *game);
void	calc_distance_from_wall(t_var *game);
void	put_line_h_in_perspective(t_var *game);
void	calc_relative_line_height(t_var *game);
void 	loop_until_hit_wall(t_var *game);
//------------------------------------------------------------------------------

// DRAWING----------------------------------------------------------------------
void 	draw_walls(t_var *game, int pixel_pos_x);
void 	draw_rectangle(t_var *game, t_point start, t_point end, int color);
void 	draw_line(t_var *game, t_dpoint start, t_dpoint end);
void 	drw_img_buff(t_var *game, int x, int y, int color);
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

// MATH FUNCTIONS --------------------------------------------------------------
t_dpoint	calculate_point(t_dpoint *start, double angle, double distance);
double		from_angle_to_radiant(double angle);
double		pi();
//------------------------------------------------------------------------------
#endif