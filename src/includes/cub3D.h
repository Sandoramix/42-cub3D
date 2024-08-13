/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:59:50 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/13 22:52:30 by odudniak         ###   ########.fr       */
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

// CONFIGURATIONS --------------------------------------------------------------
void		init_config(t_config *config);
t_state		mlx_setup(t_var *game);

//-PARSING----------------------------------------------------------------------
t_state		parse(t_var *game, int ac, char **av);

t_uint		color_to_hex(t_color color);
t_rgb		to_rgb(t_uint color);
//------------------------------------------------------------------------------
//PLAYER UTILS
t_dpoint	set_player_dpos(t_var *game, t_dpoint new_pos);
void		init_player(t_var *game, int x, int y, t_point angle);
t_point		chr_player_to_angle(char player_c);

//GENERIC UTILS
void		print_missing_config(t_var *game);
bool		is_config_missing(t_var *game);
bool		chr_is_player(char c);
char		get_map_at(t_var *game, int row_idx, int col_idx);

//------------------------------------------------------------------------------
// RAYCASTING-------------------------------------------------------------------
void		render_background(t_var *game);
void		render_walls(t_var *game);
void		render_minimap(t_var *game);
void		render_sprites(t_var *game);

void		init_vars(t_var *game, int pixel_pos_x);
void		get_wall_coords(t_var *game);
void		loop_until_hit_wall(t_var *game);
void		calc_texture_coords(t_var *game);
void		calc_direction(t_var *game);

//------------------------------------------------------------------------------

// DRAWING----------------------------------------------------------------------
void		draw_rectangle(t_var *game, t_point start, t_point end, t_uint color);
void		draw_rectangle_rgb(t_var *game, t_point start, t_point end, t_rgb rgb);
void		draw_line(t_var *game, t_dpoint start, t_dpoint end);
void		draw_px_to_img(t_var *game, int x, int y, t_uint color);
void		draw_px_to_img_rgb(t_var *game, int x, int y, t_rgb rgb);
t_rgb		get_texture_color(t_var *game);

//------------------------------------------------------------------------------

double		delta_time(t_var *game, bool normalize);

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
void		handle_zoom(t_var *game);

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