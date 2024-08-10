/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:59:50 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/09 14:06:53 by odudniak         ###   ########.fr       */
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

// TODO : split each category in separate file if (it will) needed.
// TODO : split each category in separate file if (it will) needed.

//-PARSING----------------------------------------------------------------------
//-PARSING----------------------------------------------------------------------
t_state		parse(t_var *game, int ac, char **av);
//------------------------------------------------------------------------------
//PLAYER UTILS
void	update_player(t_var *game, int x, int y, t_point angle);
t_point     chr_player_to_angle(char player_c);

//GENERIC UTILS
void		print_missing_config(t_var *game);
bool		is_config_missing(t_var *game);
bool		chr_is_player(char c);
char		get_map_at(t_var *game, int row_idx, int col_idx);


//MLX UTILS
t_state		load_xpm_image(t_var *game, t_img **img, char *path);
//------------------------------------------------------------------------------
// RAYCASTING-------------------------------------------------------------------
void		rendering(t_var *game);
void		init_rendering(t_var *game, int pixel_pos_x);
void		increase_raylen(t_var *game);
void		calc_distance_from_wall(t_var *game);
void		get_wall_coords(t_var *game);
void		calc_relative_line_height(t_var *game);
void		loop_until_hit_wall(t_var *game);
//------------------------------------------------------------------------------

// DRAWING----------------------------------------------------------------------
void		draw_walls(t_var *game, int pixel_pos_x);
void		draw_rectangle(t_var *game, t_point start, t_point end, int color);
void		draw_line(t_var *game, t_dpoint start, t_dpoint end);
void		fill_img_buffer(t_var *game, int x, int y, int color);
//------------------------------------------------------------------------------

double		delta_time(t_var *game);

// MLX CONFIGURATION -----------------------------------------------------------
t_state		mlx_setup(t_var *game);
//------------------------------------------------------------------------------

// EVENTS ----------------------------------------------------------------------
int			game_loop(t_var *game);
int			key_press(int keycode, t_var *game);
int			key_release(int keycode, t_var *game);
//------------------------------------------------------------------------------

// EVENTS HANDLER --------------------------------------------------------------
void		handle_player_movement(t_var *game);
void		handle_player_rotation(t_var *game);
void		handle_camera_rotation(t_var *game, int rotation_dir);
int			handle_wll_collision(t_var *game, double x, double y);

//------------------------------------------------------------------------------


// MATH FUNCTIONS --------------------------------------------------------------
t_dpoint	calculate_point(t_dpoint start, double angle, double distance);
void		copy_dpos(t_dpoint *p1, t_dpoint p2);
void		copy_pos(t_point *p1, t_point p2);
void		add_dpoint(t_dpoint *p1, t_dpoint p2);
void		add_point(t_point *p1, t_point p2);
double		from_angle_to_radiant(double angle);
double		pi(void);
//------------------------------------------------------------------------------
#endif