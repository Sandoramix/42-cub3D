/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:54:29 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/18 15:10:28 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# include <libft.h>

# ifdef __linux__
#  include <mlx_int.h>
# else

typedef void	t_img;
typedef void	t_xvar;

# endif

//------------------------------------------------------------------------------

typedef struct u_rgb
{
	t_uint		hex;
	t_uchar		red;
	t_uchar		green;
	t_uchar		blue;
	t_uchar		alpha;
}	t_rgba;

typedef struct s_player
{
	double	x_px;
	double	y_px;
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;

	double	offset;
	double	pos_z;
	double	head_pos_z;

}	t_player;

typedef struct s_dvec2
{
	double	x;
	double	y;
}	t_dvec2;


typedef struct s_texure
{
	t_img	*hit_texture;
	int		x;
	int		y;
	char	*pixel;
	int		color;
	double	wall_px;
	double	scale;
	double	scaled_textpos;
}	t_texture;

typedef struct s_wall
{
	int			height;
	double		dist;
	int			ceil;
	int			floor;
}	t_wall;

typedef struct s_raycast
{
	t_texture	texture;
	t_ivec2		map_coords;
	t_dvec2		delta_dist;
	t_dvec2		plane;
	t_dvec2		ray;
	t_dvec2		dir;
	double		camera_x;
	t_wall		wall;
	t_ivec2		step;
	int			side;
	int			step_count;
	bool		ray_hit;
}	t_raycast;

typedef struct s_map_info
{
	char	**map;

	int		**mtxint;
	int		rows_mtx;
	int		cols_mtx;

	char	**filedata;
}	t_map;

typedef struct s_movement
{
	bool		up;
	bool		down;
	bool		right;
	bool		left;

	bool		rot_left;
	bool		rot_right;
	bool		rot_up;
	bool		rot_down;

	bool		mouse_rot_left;
	bool		mouse_rot_right;

	bool		jump;
	bool		is_jumping;
	bool		crouch;
	bool		has_crouched;

	bool		block;

	int			jump_mult;
}	t_event;

typedef struct s_playersprites
{
	t_img	*active;
	int		active_screen_x;
	t_img	*rest;
	t_img	*block;
}	t_playersprites;

typedef struct s_config
{
	//FILE-CONFIGS---------------------
	//CONSTANTS--------------
	int				max_raycast_steps;

	//WALL-SPRITES-----------
	t_img			*wall_nord;
	char			*wall_nord_path;

	t_img			*wall_south;
	char			*wall_south_path;

	t_img			*wall_east;
	char			*wall_east_path;

	t_img			*wall_west;
	char			*wall_west_path;

	//CEILING-FLOOR-COLORS---
	t_rgba			ceiling;
	char			*ceiling_raw;

	t_rgba			floor;
	char			*floor_raw;
	//---------------------------------
	//SPRITES--------------------------
	t_playersprites	hands_sprites;
	//---------------------------------
	//WINDOW MEASURES------------------
	int				window_height;
	int				window_width;

	//MAP-UPSCALE-MODIFIERS------------
	int				tilesize;
	double			plane_limit;

	// MINIMAP-------------------------
	double			minimap_window_scale;
	int				minimap_tilesize;
	double			minimap_tilesize_player;
	double			minimap_zoom;
	double			minimap_zoom_max;
	double			minimap_zoom_min;
	//---------------------------------
	// MODIFIERS-----------------------
	double			rot_lateral_speed;
	double			rot_vertical_speed;

	double			speed;
	double			speed_mult;

	double			jump_force;
	double			jump_limit;

	double			squat_offset;

	double			camera_vert_rot_min;
	double			camera_vert_rot_max;
	//---------------------------------
	char			*window_name;

	//PRIVATE/UNUSED VARIABLES---------
	int				_w;
	int				_h;
	//---------------------------------
}	t_config;

// "GLOBAL" program's structure.
typedef struct s_var
{
	t_xvar			*mlx;
	void			*mlx_win;
	t_img			*frame;

	t_map			map;
	t_player		player;
	t_event			event;

	t_raycast		engine;
	t_ivec2			mousepos;

	t_config		cnf;

	// OTHER
	double			deltatime;
}	t_var;

#endif
