/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_conditionals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:52:51 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/04 11:00:17 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

bool	parse_config_val_is_path(t_cnf type)
{
	return (type != CNF_CEILING && type != CNF_FLOOR);
}

bool	is_filepath_valid(char *line, int line_n, char *path)
{
	int	fd;

	if (file_isdir(path))
		return (ft_perror("Error on line %d: '%s':\n\t%s is a directory\n",
				line_n, line, path), false);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_perror("Error on line %d: '%s':\n\t%s : "
				"unknown file or not enough permissions\n",
				line_n, line, path), false);
	close(fd);
	return (true);
}

bool	chr_is_player(char c)
{
	return (c == MAP_PLAYER_NORD || c == MAP_PLAYER_EAST
		|| c == MAP_PLAYER_WEST || c == MAP_PLAYER_WEST);
}