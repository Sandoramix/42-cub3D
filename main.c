/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:43:47 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/04 14:50:50 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>


// TODO REMOVE ME
static int **cmtxtoimtx(t_var *game, char **mtx, int col, int row)
{
	int **intMtx;
	int counterRow;
	int counterCol;
	(void)mtx;
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
			intMtx[counterRow][counterCol] = parse_map_chr_at(game, counterRow, counterCol) - '0';
			counterCol++;
		}
		counterRow++;
	}
	return intMtx;
}

//TODO purge me hahahahah lol
void init_hardcoded_value(t_var *game)
{
	if (ft_isdebug())
	{
		dbg_printf("LOADED MAP:\n");
		ft_putstrmtx(game->mapinfo.map);
	}
	ft_putstrmtx(game->mapinfo.map);

	game->mapinfo.mtxint = cmtxtoimtx(game, game->mapinfo.map,
			game->mapinfo.cols_mtx, game->mapinfo.rows_mtx);



	printf("Player Position x: %.5f\nPlayer Position y: %.5f\n", game->player.x_px, game->player.y_px);
	printf("Player Map Position x: %.5f\nPlayer Position y: %.5f\n", game->player.x_px /  64, game->player.y_px /  64);
	/*gestire direzione il player is facing in base al parsing*/
	game->player.dir_y = cos(game->player.angle);
	game->player.dir_x = sin(game->player.angle);

	const double plane_limit = .7;

	game->engine.plane.y = plane_limit * cos(game->player.angle);
	game->engine.plane.x = plane_limit * sin(game->player.angle);

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
