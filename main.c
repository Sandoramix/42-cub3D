/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:43:47 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/09 14:16:34 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// TODO purge me hahahahah lol
void init_hardcoded_value(t_var *game)
{
	if (ft_isdebug())
	{
		dbg_printf("LOADED MAP:\n");
		ft_putstrmtx(game->mapinfo.map);
	}
	ft_putstrmtx(game->mapinfo.map);

	//printf("Player Position x: %.5f\nPlayer Position y: %.5f\n", game->player.x_px, game->player.y_px);
	//printf("Player Map Position x: %.5f\nPlayer Position y: %.5f\n", game->player.x_px / 64, game->player.y_px / 64);
	/*gestire direzione il player is facing in base al parsing*/



}

int main(int ac, char **av)
{
	t_var game;

	ft_bzero(&game, sizeof(t_var));
	game.mlx = mlx_init();
	if (!game.mlx)
		return (pf_errcode(E_MLX), cleanup(&game, true, 1), 1);
	parse(&game, ac, av);
	init_hardcoded_value(&game);
	mlx_setup(&game);
	render(&game);
	mlx_loop(game.mlx);
	return (cleanup(&game, true, 0), 0);
}
