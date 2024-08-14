/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:59:50 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/14 02:13:22 by odudniak         ###   ########.fr       */
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
t_state		mlx_setup(t_var *g);

//DEBUG----------------------------------------------------------------------
void		debug_info(t_var *g);
//------------------------------------------------------------------------------

//-PARSING----------------------------------------------------------------------
t_state		parse(t_var *g, int ac, char **av);
//------------------------------------------------------------------------------

// PLAYER UTILS------------------------
t_dpoint	set_player_dpos(t_var *g, t_dpoint new_pos);
void		init_player(t_var *g, int x, int y, t_point angle);
/**
### Player direction

Convert player's char `player_c` into a direction "vector"

#### Directions are (x; y):

- NORD: (0; -1)
- EAST: (1; 0)
- WEST: (-1; 0)
- SOUTH: (0; 1)

---

#### Return value:

`t_point` which is the direction
 */
t_point		chr_player_to_direction(char player_c);

// GENERIC UTILS-----------------------
void		print_missing_config(t_var *g);
bool		is_config_missing(t_var *g);
bool		chr_is_player(char c);
char		get_map_at(t_var *g, int row_idx, int col_idx);
bool		can_player_go_here(t_var *game, double x, double y);

double		delta_time(t_var *g, bool normalize);
//------------------------------------------------------------------------------

// RENDERING--------------------------------------------------------------------
void		render_base(t_var *g);
void		render_sprites(t_var *g);
void		render_minimap(t_var *g);
void		render_crosshair(t_var *game);

// RAYCASTING--------------------------
void		init_vars(t_var *g, int pixel_pos_x);
void		get_wall_coords(t_var *g);
void		loop_until_hit_wall(t_var *g);
void		calc_texture_coords(t_var *g);

/**
 * @brief Tunnable crosshair, just need to change `cross_thickness`
 * and `cross_length` inside the function xD
 * @note #### TODO add the cursor's parameters inside global configuration.
 * @param game game obj
 */
void		calc_direction(t_var *g);

//------------------------------------------------------------------------------

// DRAWING----------------------------------------------------------------------
void		draw_rectangle(t_var *g, t_point start, t_point end, t_uint color);
void		draw_rectangle_rgb(t_var *g, t_point start, t_point end, t_rgb rgb);
void		draw_line(t_var *g, t_dpoint start, t_dpoint end);
void		draw_pixel(t_var *g, int x, int y, t_uint color);
void		draw_pixel_rgb(t_var *g, int x, int y, t_rgb rgb);
t_rgb		get_texture_color(t_var *g);

//------------------------------------------------------------------------------

// EVENTS ----------------------------------------------------------------------
int			game_loop(t_var *g);
int			on_keypress(int keycode, t_var *game);
int			on_keyrelease(int keycode, t_var *game);

// Should these be in a headerfile?...

void		camera_h_event_pressed(int keycode, t_var *game);
void		camera_h_event_released(int keycode, t_var *game);
void		camera_v_event_pressed(int keycode, t_var *game);
void		camera_v_event_released(int keycode, t_var *game);

void		movement_h_event_pressed(int keycode, t_var *game);
void		movement_h_event_released(int keycode, t_var *game);
void		movement_v_event_pressed(int keycode, t_var *game);
void		movement_v_event_released(int keycode, t_var *game);

// EVENT HANDLERS ---------------------
void		handle_vertical_movement(t_var *game);
void		handle_horizontal_movement(t_var *game);

void		handle_vertical_rotation(t_var *game);
void		handle_horizontal_rotation(t_var *game);
//------------------------------------------------------------------------------

// MATH FUNCTIONS --------------------------------------------------------------
t_dpoint	calculate_point(t_dpoint start, double angle, double distance);

void		copy_dpos(t_dpoint *p1, t_dpoint p2);
void		copy_pos(t_point *p1, t_point p2);

void		add_dpoint(t_dpoint *p1, t_dpoint p2);
void		add_point(t_point *p1, t_point p2);

double		from_angle_to_radiant(double angle);
double		pi(void);

t_uint		color_to_hex(t_color color);
t_rgb		to_rgb(t_uint color);
//------------------------------------------------------------------------------
#endif