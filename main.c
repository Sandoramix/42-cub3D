/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:43:47 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/03 14:43:52 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>


// TODO REMOVE ME
static int **cmtxtoimtx(char **mtx, int col, int row)
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

//TODO purge me
void init_hardcoded_value(t_var *game)
{

	if (ft_isdebug())
	{
		dbg_printf("LOADED MAP:\n");
		ft_putstrmtx(game->mapinfo.map);
	}

	game->mapinfo.rows_mtx = str_mtxlen(game->mapinfo.map);
	game->mapinfo.cols_mtx = str_ilen(game->mapinfo.map[0]);
	for (int i = 0; game->mapinfo.map[i]; i++){
		if (game->mapinfo.cols_mtx < str_ilen(game->mapinfo.map[i]))
			game->mapinfo.cols_mtx = str_ilen(game->mapinfo.map[i]);
	}

	printf("Map sizes:\trows[%f]\tcols[%f]\n", game->mapinfo.rows_mtx,
		game->mapinfo.cols_mtx);


	game->mapinfo.mtxint = cmtxtoimtx(game->mapinfo.map,
			game->mapinfo.cols_mtx, game->mapinfo.rows_mtx);

	game->player.x = 7;
	game->player.y = 7;


	printf("Player Position x: %.5f\nPlayer Position y: %.5f\n", game->player.x, game->player.y);
	/*gestire direzione il player is facing in base al parsing*/
	game->player.dir_x = cos(PLAYER_ANGLE);
	game->player.dir_y = sin(PLAYER_ANGLE);

	/* printf("player dir %f, %f\n", game->player.dir_x, game->player.dir_y); */

	game->plane.x = 0.0;	 // sul piano x non c' e alcun offset
	game->plane.y = 0.66; 	// offset di 0.66unita sull asse delle Y

	game->sprite.tile_sprite_w = TILE_SIZE;
	game->sprite.tile_sprite_h = TILE_SIZE;
	game->sprite.mini_player_w = MINIMAP_TILE_SIZE;
	game->sprite.mini_player_h = MINIMAP_TILE_SIZE;

    // double rotSpeed = delta_time(game) + 0.05; 
	// /* printf("rotation speed %f\n", rotSpeed); */
	// game->player.positive_cos_rot_speed = cos(rotSpeed);
	// game->player.positive_sin_rot_speed = sin(rotSpeed);
	// game->player.neg_cos_rot_speed_pos = cos(-rotSpeed);
	// game->player.neg_sin_rot_speed_pos = sin(-rotSpeed);

	// TODO dynamic
	game->dda.screen_size_w_px = WINDOW_WIDTH;
	game->dda.screen_size_h_px = WINDOW_HEIGHT;

}

int	main(int ac, char **av)
{
	t_var	game;

	ft_bzero(&game, sizeof(t_var));
	game.mlx = mlx_init();
	if (!game.mlx)
		return (pf_errcode(E_MLX), cleanup(&game, true, 1), 1);
	parse(&game, ac, av);
	init_hardcoded_value(&game); // TODO: WE CAN DO BETTER THAN THIS
	mlx_configuration(&game);
	//draw first frame
	rendering(&game);
	mlx_loop(game.mlx);
	return (0);
}
