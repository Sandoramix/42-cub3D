/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:54:29 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/04 14:52:05 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# include <cub3D.h>

//------------------------------------------------------------------------------
typedef struct s_color
{
	t_uchar	red;
	t_uchar	green;
	t_uchar	blue;
}	t_color;

typedef union u_rgb
{
	t_color	color;
	int		hex;
}	t_rgb;

typedef struct s_player
{
	double	x_px;
	double	y_px;
	int		x;
	int		y;
	double	dir_x;
	double	dir_y;

	double offset;
	double pos_z;
	double head_pos_z;

	double travel_count;

	double	angle;
}	t_player;

typedef struct s_dpoint
{
	double	x;
	double	y;
}	t_dpoint;

// TODO NORMINETTE (NAMES: snake case)
typedef struct s_raycast
{
	t_point map_coords;
	t_dpoint delta_dist;
	t_dpoint plane;
	t_dpoint ray;
	t_dpoint dir;
	double	camera_x;
	double	wall_dist;
	double	wall_ceil;
	double	wall_floor;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;

}	t_raycast;

typedef struct s_map_info
{
	char	**map;

	int		**mtxint;
	int		rows_mtx;
	int		cols_mtx;

	char	**file_content;
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

	bool		jump;
	bool		crouch;
	bool		has_crouched;

	int			jump_mult;
}	t_movement;


typedef struct s_config
{
//SPRITES------------------------------
	t_img	*wall_nord;
	char	*wall_nord_path;

	t_img	*wall_east;
	char	*wall_east_path;

	t_img	*wall_west;
	char	*wall_west_path;

	t_img	*wall_south;
	char	*wall_south_path;
//-------------------------------------

	t_rgb	ceiling;
	char	*ceiling_raw;

	t_rgb	floor;
	char	*floor_raw;
//TODO WINDOW MEASURES ??
	int		_w;
	int		_h;
}	t_config;

// "GLOBAL" program's structure.
typedef struct s_var
{
	void			*mlx;
	void			*mlx_win;
	void			*img;
	char			*buffer;
	int				bpp;
	int				endian;
	int				line_bytes;
	t_player		player;
	t_movement		move;
	t_raycast		engine;
	t_map			mapinfo;

	t_config		config;

	// OTHER
	double			deltatime;
}	t_var;

#endif
