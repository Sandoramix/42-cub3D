/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:39:48 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/04 14:43:09 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_parse.h>

bool	parse_is_filepath_valid(char *line, int line_n, char *path)
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

int	parse_validate_map_filepath(t_var *game, int ac, char **av)
{
	char	*file;
	int		fd;

	if (ac != 2)
		return (pf_errcode(E_INVALID_ARGC), cleanup(game, true, 1), -1);
	file = av[1];
	if (!str_endswith(file, ".cub"))
		return (ft_perror("Error: invalid suffix (.cub) of file %s\n", file),
			cleanup(game, true, 1), -1);
	if (file_isdir(file))
		return (ft_perror("Error: %s is a directory\n", file),
			cleanup(game, true, 1), -1);
	if (!file_exists(file))
		return (ft_perror("Error: file %s does not exist\n", file),
			cleanup(game, true, 1), -1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_perror("Error: file %s doesn't have +r permissions\n", file),
			cleanup(game, true, 1), -1);
	return (fd);
}
