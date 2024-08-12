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

int main(int ac, char **av)
{
	t_var game;

	ft_bzero(&game, sizeof(t_var));
	game.mlx = mlx_init();
	if (!game.mlx)
		return (pf_errcode(E_MLX), cleanup(&game, true, 1), 1);
	parse(&game, ac, av);
	game.config.plane_limit = 0.7;
	(void)/*va fatta la funzione dove ci si prende i valori delle MACRO*/
	mlx_setup(&game);
	(void)/*first frame*/
/* 	render_background(&game); */
	render_walls(&game);
	if (!mlx_put_image_to_window(game.mlx, game.mlx_win, game.img, 0, 0))
		return (pf_errcode(E_MLXIMG), cleanup(&game, true, 1), 1);
	mlx_loop(game.mlx);
	return (cleanup(&game, true, 0), 0);
}
