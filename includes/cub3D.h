#ifndef CUB3D_H
# define CUB3D_H

#include <libft.h>
#include <mlx.h>
#include <mlx_int.h>


#define TEXTURE_SIZE 64 
#define TEXTURE_HALF_SIZE 32
#define SIZE_MINI_PLAYER 8

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900


#define PLANEX 0.0
#define PLANEY 0.66

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100

#define N 78
#define W 87
#define E 69
#define S 83

#define FLOOR 0
#define WALL 1

#define VELOCITY 1000
#define DELTA_TIME 1

typedef struct s_playerPos
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
} t_playerPos;

typedef struct s_dpoint
{
	double x;
	double y;
} t_dpoint;

typedef struct s_sprite
{
	void *black_sprite;
	void *white_sprite;
	void *mini_player;


	int mini_player_w;
	int mini_player_h;

	int tile_sprite_w;
	int tile_sprite_h;
} t_sprite;

typedef struct s_DDA
{
	double cameraX;
	double rayDirX;
	double rayDirY;
	double screenSize;

	double sideDistX;
	double sideDistY;
	double pixelPosX;
	double deltaDistX;
	double deltaDistY;

	double perpWallDist;
	double lineHeight;
	double draw_start;
	double draw_end;

	int stepX;
	int stepY;
	int mapX;
	int mapY;

	int hit_wall;
	int side;

} t_DDA;

typedef struct s_map_info
{
	int **mtxint;
	double rows_mtx;
	double cols_mtx;
} t_map_info;

// "GLOBAL" program's structure.
typedef struct s_var
{
	t_playerPos playerPos;
	t_DDA dda_helper;
	t_sprite sprite;
	t_dpoint plane;
	t_map_info mapinfo;
	int **mtxint;
	double rows_mtx;
	double cols_mtx;
	void *mlx_ptr;
	void *win_ptr;
} t_var;

//Player position structure

/* typedef struct s_playerPos{
    float x;
    float y;
} t_playerPos;


// "GLOBAL" program's structure.
struct s_var
{
   struct s_playerPos *playerPos;
}; */


void calculate_DDA(t_var *game);
void calc_initial_step_intial_raylen(t_var *game);
void increase_raylen(t_var *game);
void calc_distance_from_wall(t_var *game);
void calc_perspective(t_var *game);



#endif
