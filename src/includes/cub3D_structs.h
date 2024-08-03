/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:54:29 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/03 08:29:32 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# include <cub3D.h>

enum e_rotation_dir
{
	ROTAT_DIR_RIGHT,
	ROTAT_DIR_LEFT
};

typedef struct s_player_pos
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;

	double	positive_cos_rot_speed;
	double	positive_sin_rot_speed;
	double	neg_cos_rot_speed_pos;
	double	neg_sin_rot_speed_pos;

}	t_player;

typedef struct s_dpoint
{
	double	x;
	double	y;
}	t_dpoint;

typedef struct s_sprite
{
	t_img	*black_sprite;
	t_img	*white_sprite;
	t_img	*mini_player;

	int		mini_player_w;
	int		mini_player_h;

	int		tile_sprite_w;
	int		tile_sprite_h;
}	t_sprite;

// TODO NORMINETTE (NAMES: snake case)
typedef struct s_DDA
{
	double	camera_x;
	double	dir_rayx;
	double	dir_rayy;
	int		screen_size_w_px;
	int		screen_size_h_px;

	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;

	double	wall_dist;
	double	line_h_px;
	double	draw_start_px;
	double	draw_end_px;

	int		step_x;
	int		ste_y;
	int		map_x;
	int		map_y;

	int		hit;
	int		side;

}	t_DDA;

typedef struct s_map_info
{
	char	**map;

	int		**mtxint;
	double	rows_mtx;
	double	cols_mtx;

	char	**file_content;
}	t_map;

typedef struct s_movement
{
	int		up;
	int		down;
	int		right;
	int		left;

	int		rot_left;
	int		rot_right;
}	t_movement;

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

typedef struct s_config
{
//SPRITES------------------------------
	t_img	wall_nord;
	char	*wall_nord_path;

	t_img	wall_east;
	char	*wall_east_path;

	t_img	wall_west;
	char	*wall_west_path;

	t_img	wall_south;
	char	*wall_south_path;
//-------------------------------------

	t_rgb	ceiling;
	char	*ceiling_raw;

	t_rgb	floor;
	char	*floor_raw;
}	t_config;

// "GLOBAL" program's structure.
typedef struct s_var
{
	void			*mlx;
	void			*mlx_win;

	t_player		player_pos;
	t_movement		move;
	t_DDA			dda;
	t_sprite		sprite;
	t_dpoint		plane;
	t_map			mapinfo;

	t_config		config;

	// OTHER
	double			deltatime;
}	t_var;

#endif
