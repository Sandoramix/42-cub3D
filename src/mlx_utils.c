/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:35:13 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/09 14:21:44 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_state	load_xpm_image(t_var *game, t_img **img, char *path)
{
	void	*res;

	res = mlx_xpm_file_to_image(game->mlx, path,
			&game->config._w, &game->config._h);
	if (!res)
		return (ft_perror("Error: cannot load sprite from '%s'. \
		Check if it is a valid xpm image\n", path),
			cleanup(game, true, 1), KO);
	*img = res;
	return (OK);
}
