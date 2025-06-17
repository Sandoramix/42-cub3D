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
t_dvec2		update_player_pos(t_var *game, t_dvec2 new_pos);
void		init_player(t_var *g, int x, int y);
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

`t_ivec2` which is the direction
 */
t_dvec2		get_player_direction(char player_c);

// GENERIC----------------------------------------------------------------------
void		print_missing_config(t_var *g);
bool		is_config_missing(t_var *g);

bool		is_point_inside_window(t_var *game, t_dvec2 point);
bool		is_mouse_inside_frame(t_var *game);
bool		chr_is_player(char c);
char		get_map_at(t_var *g, int row_idx, int col_idx);
bool		can_player_go_here(t_var *game, double x, double y);

double		delta_time(t_var *g, bool normalize);
//------------------------------------------------------------------------------

// DRAWING----------------------------------------------------------------------
void		draw_rectangle(t_var *g, t_ivec2 start, t_ivec2 end, t_uint color);
void		draw_rectangle_rgb(t_var *g, t_ivec2 start,
				t_ivec2 end, t_rgba rgb);
void		draw_pixel(t_var *g, int x, int y, t_uint color);
void		draw_pixel_rgb(t_var *g, int x, int y, t_rgba rgb);
void		draw_line_rgb(t_var *g, t_dvec2 start, t_dvec2 end, t_rgba rgb);
//------------------------------------------------------------------------------

// MATH-------------------------------------------------------------------------
t_dvec2		get_destpoint(t_dvec2 start, double angle,
				double distance, double units);
double		calc_wall_px_hit(t_var *game);

void		dvec2_cpy(t_dvec2 *dest, t_dvec2 src);
void		ivec2_cpy(t_ivec2 *dest, t_ivec2 src);

double		direction_to_angle(double x, double y);
double		angle_to_radiant(double angle);
double		pi(void);

t_uint		rgba_to_hex(t_rgba color);
t_rgba		hex_to_rgba(t_uint color);

double		normalize_to_one(double num);
//------------------------------------------------------------------------------
#endif