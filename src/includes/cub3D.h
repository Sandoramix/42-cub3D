/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:59:50 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 15:28:26 by odudniak         ###   ########.fr       */
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
void		init_config(t_config *cnf);
t_state		mlx_setup(t_var *g);

//DEBUG----------------------------------------------------------------------
void		debug_info(t_var *g);
//------------------------------------------------------------------------------

//-PARSING----------------------------------------------------------------------
t_state		parse(t_var *g, int ac, char **av);
//------------------------------------------------------------------------------

// PLAYER UTILS------------------------
t_dpoint	set_player_map_dpos(t_var *g, t_dpoint new_pos);
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

bool		is_point_inside_window(t_var *game, t_dpoint point);
bool		chr_is_player(char c);
char		get_map_at(t_var *g, int row_idx, int col_idx);
bool		can_player_go_here(t_var *game, double x, double y);

double		delta_time(t_var *g, bool normalize);
//------------------------------------------------------------------------------

// RENDERING--------------------------------------------------------------------
void		render_base(t_var *g);
void		render_sprites(t_var *g, struct s_cnfsprites *sprites);
void		render_minimap(t_var *g);
/**
 * @brief Tunnable crosshair, just need to change `cross_thickness`
 * and `cross_length` inside the function xD
 * @note #### TODO add the cursor's parameters inside global configuration.
 * @param game game obj
 */
void		render_crosshair(t_var *game);

// RAYCASTING--------------------------
void		init_vars(t_var *game, t_raycast *eng, t_player *pl, int x);
void		get_wall_coords(t_var *g, t_raycast *eng, t_wall *wall);
void		loop_until_hit_wall(t_var *g);
//------------------------------------------------------------------------------
// TEXTURE---------------------------------------------------------------------
int			calc_text_x(t_var *g);
int			calc_text_y(t_var *game);
void		calc_scaled_textpos(t_var *game,
				t_raycast *engine, t_player *player);
t_rgba		get_texture_color(t_var *g, int tex_x, int tex_y);

//------------------------------------------------------------------------------
void		calc_direction(t_raycast *eng, t_player *pl);

//------------------------------------------------------------------------------

// DRAWING----------------------------------------------------------------------
void		draw_rectangle(t_var *g, t_point start, t_point end, t_uint color);
void		draw_rectangle_rgb(t_var *g, t_point start,
				t_point end, t_rgba rgb);
void		draw_pixel(t_var *g, int x, int y, t_uint color);
void		draw_pixel_rgb(t_var *g, int x, int y, t_rgba rgb);
void		draw_line_rgb(t_var *g, t_dpoint start, t_dpoint end, t_rgba rgb);
//------------------------------------------------------------------------------

// EVENTS ----------------------------------------------------------------------
int			game_loop(t_var *g);
int			on_keypress(int keycode, t_var *game);
int			on_keyrelease(int keycode, t_var *game);

// Should these be in a headerfile?...

int			on_mouse_click(int button, int x, int y, void *game);
void		player_sprites_event_pressed(int keycode, t_var *game);
void		player_sprites_event_released(int keycode, t_var *game);

void		camera_h_event_pressed(int keycode, t_var *game);
void		camera_h_event_released(int keycode, t_var *game);
void		camera_v_event_pressed(int keycode, t_var *game);
void		camera_v_event_released(int keycode, t_var *game);

void		movement_h_event_pressed(int keycode, t_var *game);
void		movement_h_event_released(int keycode, t_var *game);
void		movement_v_event_pressed(int keycode, t_var *game);
void		movement_v_event_released(int keycode, t_var *game);

// EVENT HANDLERS ---------------------
void		handle_mouse_rotation(t_var *game, t_mouse *mouse);

void		handle_player_sprites(t_var *game);

void		handle_vertical_movement(t_var *game);
void		handle_horizontal_movement(t_var *game);

void		handle_vertical_rotation(t_var *game);
void		handle_horizontal_rotation(t_var *game);
//------------------------------------------------------------------------------

// MATH FUNCTIONS --------------------------------------------------------------
t_dpoint	get_destpoint(t_dpoint start, double angle,
				double distance, double units);
double		calc_wall_px_hit(t_var *game);

void		copy_dpos(t_dpoint *p1, t_dpoint p2);
void		copy_pos(t_point *p1, t_point p2);

double		direction_to_angle(double x, double y);
double		angle_to_radiant(double angle);
double		pi(void);

t_uint		rgba_to_hex(t_rgba color);
t_rgba		hex_to_rgba(t_uint color);

double		normalize_to_one(double num);
//------------------------------------------------------------------------------
#endif