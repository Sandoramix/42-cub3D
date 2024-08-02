/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:43:47 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/02 18:30:20 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	main(int ac, char **av)
{
	t_var	game;

	game = (t_var){0};
	parse(&game, ac, av, true);
	mlx_configuration(&game);


	/**
	 * mlx inizializzazione (finestra, sprite, hook)
	 * 
	 * init_game(first world renderization(DDA))
	 * game_starts()
	 */
	//game_start(&game);
	return (0);
}
