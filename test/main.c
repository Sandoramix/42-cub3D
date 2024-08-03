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
	game->mlx = mlx_init();
	mlx_get_screen_size(game->mlx, &game->dda.screen_size_w_px, &game->dda.screen_size_h_px);
	game->mlx_win = mlx_new_window(game->mlx, game->dda.screen_size_w_px, game->dda.screen_size_h_px, "UrMom");

	game->img = mlx_new_image(game->mlx, game->dda.screen_size_w_px, game->dda.screen_size_h_px);
	game->buffer = mlx_get_data_addr(game->img, &game->bpp, &game->line_bytes, &game->endian);
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
	mlx_hook(game.mlx_win, KeyPress, KeyPressMask, &key_press, &game);
    mlx_hook(game.mlx_win, KeyRelease, KeyReleaseMask, &key_release, &game);
	mlx_hook(game.mlx_win, 17, 0, mlx_loop_end, game.mlx);
	//mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop(game.mlx);
}