#include <libft.h>
#include <cub3D.h>

int **cmtxtoimtx(char **mtx, int col, int row)
{
	int **intMtx;
	int counterRow;
	int counterCol;

	intMtx = ft_calloc(row, sizeof(int *));
	if (!intMtx)
		return NULL;
	counterRow = 0;
	counterCol = 0;
	while (counterRow < row)
	{
		intMtx[counterRow] = ft_calloc(col, sizeof(int));
		counterCol = 0;
		while (counterCol < col)
		{
			intMtx[counterRow][counterCol] = mtx[counterRow][counterCol] - '0';
			counterCol++;
		}
		counterRow++;
	}
	return intMtx;
}

// int game_loop(t_var *game)
// {
// 	(void)game;
// 	return 1;
// }

// void rotate_camera(t_var *game, int rotation_dir)
// {
// 	double old_dir_x;
// 	double old_plane_x;

// 	if (rotation_dir == ROTAT_DIR_RIGHT)
// 	{
// 		old_dir_x = game->player_pos.dir_x;
// 		game->player_pos.dir_x = game->player_pos.dir_x * game->player_pos.neg_cos_rot_speed_pos
// 		- game->player_pos.dir_y * game->player_pos.neg_sin_rot_speed_pos; 
// 		game->player_pos.dir_y = old_dir_x * game->player_pos.neg_sin_rot_speed_pos + game->player_pos.dir_y * game->player_pos.neg_cos_rot_speed_pos;
// 		old_plane_x = game->plane.x;
// 		game->plane.x = game->plane.x  * game->player_pos.neg_cos_rot_speed_pos - game->plane.y *  game->player_pos.neg_sin_rot_speed_pos;
// 		game->plane.y = old_plane_x *  game->player_pos.neg_sin_rot_speed_pos + game->plane.y * game->player_pos.neg_cos_rot_speed_pos; 
// 	}
// 	else
// 	{
// 		old_dir_x = game->player_pos.dir_x;
// 		game->player_pos.dir_x = game->player_pos.dir_x * game->player_pos.positive_cos_rot_speed 
// 		- game->player_pos.dir_y * game->player_pos.positive_sin_rot_speed; 
// 		game->player_pos.dir_y = old_dir_x * game->player_pos.positive_sin_rot_speed + game->player_pos.dir_y * game->player_pos.positive_cos_rot_speed;
// 		old_plane_x = game->plane.x;
// 		game->plane.x = game->plane.x  * game->player_pos.positive_cos_rot_speed - game->plane.y *  game->player_pos.positive_sin_rot_speed;
// 		game->plane.y = old_plane_x *  game->player_pos.positive_sin_rot_speed + game->plane.y * game->player_pos.positive_cos_rot_speed; 
// 	}

// }


// int key_press(int keycode, t_var *game)
// {
//    /*  printf("key pressed %d\n", keycode);
//     printf("[BEFORE] player position(%f, %f)\n", game->player_pos.x, game->player_pos.y); */
// 	if (keycode == KEY_W)
//         game->move.up = 1;
// 	if (keycode == KEY_S)
//         game->move.down = 1;
// 	if (keycode == KEY_A)
//         game->move.left = 1;
// 	if (keycode == KEY_D)
//         game->move.right = 1;
// 	/*check rotazione*/
// 	if (keycode == XK_Left)
//         game->move.rot_left = 1;
// 	if (keycode == XK_Right)
//         game->move.rot_right = 1;
// 	/*movimento */
// 	if (game->move.up)
// 	    game->player_pos.y -= VELOCITY /* * game->deltatime  */;
// 	if (game->move.down)
// 	    game->player_pos.y += VELOCITY /* * game->deltatime  */;
// 	if (game->move.left)
// 	    game->player_pos.x -= VELOCITY /* * game->deltatime  */;
// 	if (game->move.right)
//         game->player_pos.x += VELOCITY /* * game->deltatime  */;
// 	/**direzione */
// 	if (game->move.rot_left)
// 		rotate_camera(game , ROTAT_DIR_LEFT);
// 	if (game->move.rot_right)
// 		rotate_camera(game , ROTAT_DIR_RIGHT);


// 	raycasting(game);
// 	 game->move.rot_left = 0;
// 	 game->move.rot_right = 0;
//    /*  printf("[AFTER] player position(%f, %f)\n", game->player_pos.x, game->player_pos.y); */
//     return 0;
// }

// int key_release(int keycode, t_var *game)
// {
//     if (keycode == KEY_W)
//         game->move.up = 0;
//     if (keycode == KEY_S)
//         game->move.down = 0;
//     if (keycode == KEY_A)
//         game->move.left = 0;
//     if (keycode == KEY_D)
//         game->move.right = 0;
//     return 0;
// }



char **read_file()
{
	char	**mtx;
	int		fd;

	
	if(!file_exists("../assets/maps/mappa.cub"))
	{
		/*messaggio errore  e clean up*/
	}
	fd = open("../assets/maps/mappa.cub", O_RDONLY);
	/*check fd*/
	mtx = ft_readfile(fd, false);
	return (mtx);
}


void mlx_handling(t_var *game)
{
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, 1600, 1080, "UrMom");



	/* game->sprite.white_sprite = mlx_xpm_file_to_image(game->mlx_ptr,
			"../assets/sprites/white_sprite.xpm",
			&game->sprite.tile_sprite_w, &game->sprite.tile_sprite_h);
	game->sprite.black_sprite = mlx_xpm_file_to_image(game->mlx_ptr,
			"../assets/sprites/black_sprite.xpm",
			&game->sprite.tile_sprite_w, &game->sprite.tile_sprite_h);
	game->sprite.mini_player = mlx_xpm_file_to_image(game->mlx_ptr,
		"../assets/sprites/player_minimap.xpm",
			&game->sprite.mini_player_w, &game->sprite.mini_player_h); */



	
	

}

void init_hardcoded_value(t_var *game)
{
	game->player_pos.x = 3;
	game->player_pos.y = 2;


	printf("Player Position x: %.5f\nPlayer Position y: %.5f\n", game->player_pos.x, game->player_pos.y);
	
	/*gestire direzione il player is facing in base al parsing*/
	game->player_pos.dir_x = cos(PLAYER_ANGLE);
	game->player_pos.dir_y = sin(PLAYER_ANGLE);

	/* printf("player dir %f, %f\n", game->player_pos.dir_x, game->player_pos.dir_y); */

	game->plane.x = 0.0;	 // sul piano x non c' e alcun offset
	game->plane.y = 0.66; 	// offset di 0.66unita sull asse delle Y

	game->sprite.tile_sprite_w = TILE_SIZE;
	game->sprite.tile_sprite_h = TILE_SIZE;
	game->sprite.mini_player_w = MINIMAP_TILE_SIZE;
	game->sprite.mini_player_h = MINIMAP_TILE_SIZE;

    double rotSpeed = delta_time(game) + 0.05; //the constant value is in radians/second
	/* printf("rotation speed %f\n", rotSpeed); */
	game->player_pos.positive_cos_rot_speed = cos(rotSpeed);
	game->player_pos.positive_sin_rot_speed = sin(rotSpeed);
	game->player_pos.neg_cos_rot_speed_pos = cos(-rotSpeed);
	game->player_pos.neg_sin_rot_speed_pos = sin(-rotSpeed);
	game->dda.screen_size_w_px = 1600.0;
	game->dda.screen_size_h_px = 1080.0;
}

void parsing(t_var *game)
{
	char **tmp_mtx;

	tmp_mtx = read_file();
	if(!tmp_mtx)
		cleanup(game, true, KO);

	game->mapinfo.rows_mtx = str_mtxlen(tmp_mtx);
	game->mapinfo.cols_mtx = str_ilen(tmp_mtx[0]);
	game->mapinfo.mtxint = cmtxtoimtx(tmp_mtx, game->mapinfo.cols_mtx, game->mapinfo.rows_mtx);
	if (!game->mapinfo.mtxint)
		cleanup(game, true, KO);
}

int main(/* int ac, char **av */)
{
	struct s_var game;

	game = (struct s_var){0};
	
	parsing(&game);
	mlx_handling(&game);
	init_hardcoded_value(&game); 
	raycasting(&game);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &key_press, &game);
    mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask, &key_release, &game);
	mlx_hook(game.win_ptr, 17, 0, mlx_loop_end, game.mlx_ptr);
	mlx_loop_hook(game.mlx_ptr, &game_loop, &game);
	mlx_loop(game.mlx_ptr);
}