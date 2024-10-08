/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:04:04 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/18 15:14:22 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_UTILS_H
# define CUB3D_UTILS_H

# include <cub3D.h>

// PLAYER-----------------------------------------------------------------------
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

// GENERIC----------------------------------------------------------------------
void		print_missing_config(t_var *g);
bool		is_config_missing(t_var *g);

bool		is_point_inside_window(t_var *game, t_dpoint point);
bool		is_mouse_inside_frame(t_var *game);
bool		chr_is_player(char c);
char		get_map_at(t_var *g, int row_idx, int col_idx);
bool		can_player_go_here(t_var *game, double x, double y);

double		delta_time(t_var *g, bool normalize);
//------------------------------------------------------------------------------

// DRAWING----------------------------------------------------------------------
void		draw_rectangle(t_var *g, t_point start, t_point end, t_uint color);
void		draw_rectangle_rgb(t_var *g, t_point start,
				t_point end, t_rgba rgb);
void		draw_pixel(t_var *g, int x, int y, t_uint color);
void		draw_pixel_rgb(t_var *g, int x, int y, t_rgba rgb);
void		draw_line_rgb(t_var *g, t_dpoint start, t_dpoint end, t_rgba rgb);
//------------------------------------------------------------------------------

// MATH-------------------------------------------------------------------------
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