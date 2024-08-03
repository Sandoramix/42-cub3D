/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:54:29 by odudniak          #+#    #+#             */
/*   Updated: 2024/07/31 17:45:25 by odudniak         ###   ########.fr       */
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

	double positive_cos_rot_speed;
	double positive_sin_rot_speed;
	double neg_cos_rot_speed_pos;
	double neg_sin_rot_speed_pos;



}	t_player_pos;

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
	int	screen_size_w_px;
	int	screen_size_h_px;

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
	int up;
	int down;
	int right;
	int left;

	int rot_left;
	int rot_right;
} t_movement;

// "GLOBAL" program's structure.
typedef struct s_var
{
	void			*mlx;
	void			*win_ptr;
	void			*img;
	char			*buffer;
	int				bpp;
	int				endian;
	int				line_bytes;
	t_player_pos	player_pos;
	t_movement		move;
	t_DDA			dda;
	t_sprite		sprite;
	t_dpoint		plane;
	t_map			mapinfo;


	double			deltatime;
}	t_var;

#endif
