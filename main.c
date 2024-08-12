/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:43:47 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/12 18:08:57 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	fill_configs(t_config *config)
{
	config->plane_limit = 0.7;
	config->minimap_scale = 8;
	config->minimap_player_scale = 4;
}

int main(int ac, char **av)
{
	t_var game;

	ft_bzero(&game, sizeof(t_var));
	game.mlx = mlx_init();
	if (!game.mlx)
		return (pf_errcode(E_MLX), cleanup(&game, true, 1), 1);
	parse(&game, ac, av);
	(void)/*va fatta la funzione dove ci si prende i valori delle MACRO*/
	fill_configs(&game.config);
	mlx_setup(&game);
	(void)/*first frame*/
	render_background(&game);
	render_walls(&game);
	if (!mlx_put_image_to_window(game.mlx, game.mlx_win, game.img, 0, 0))
		return (pf_errcode(E_MLXIMG), cleanup(&game, true, 1), 1);
	mlx_loop(game.mlx);
	return (cleanup(&game, true, 0), 0);
}
