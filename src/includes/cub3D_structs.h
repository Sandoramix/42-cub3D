/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:54:29 by odudniak          #+#    #+#             */
/*   Updated: 2024/07/31 17:08:35 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# include <cub3D.h>

typedef struct s_playerPos
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
}	t_playerPos;

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
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	screenSize;

	double	sideDistX;
	double	sideDistY;
	double	pixelPosX;
	double	deltaDistX;
	double	deltaDistY;

	double	perpWallDist;
	double	lineHeight;
	double	draw_start;
	double	draw_end;

	int		stepX;
	int		stepY;
	int		mapX;
	int		mapY;

	int		hit_wall;
	int		side;

}	t_DDA;

typedef struct s_map_info
{
	char	**map;

	int		**mtxint;
	double	rows_mtx;
	double	cols_mtx;
}	t_map;

// "GLOBAL" program's structure.
typedef struct s_var
{
	void			*mlx_ptr;
	void			*win_ptr;

	t_playerPos		playerPos;
	t_DDA			dda_helper;
	t_sprite		sprite;
	t_dpoint		plane;
	t_map			mapinfo;


	double			deltatime;
}	t_var;

#endif
