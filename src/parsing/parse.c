/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:46:08 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/03 14:17:35 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	validate_map_filepath(t_var *game, int ac, char **av)
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

t_state	parse_map(t_var *game)
{
	char	**file_content;
	int		i;

	file_content = game->mapinfo.file_content;
	i = str_mtxlen(file_content) - 1;
	if (i <= 0)
		return (pf_errcode(E_DEFAULT), cleanup(game, true, 1), KO); // SHOULDN'T HAPPEN
	while (i >= 0)
	{
		if (parse_identify_cnf(file_content[i]) != CNF_UNKNOWN)
		{
			i++;
			break ;
		}
		i--;
	}
	while (file_content[i] && str_ilen(file_content[i]) == 0)
		i++;
	game->mapinfo.map = str_mtxdup(&file_content[i]);
	if (!game->mapinfo.map)
		return (pf_errcode(E_MALLOC), cleanup(game, true, 1), KO);
	return (OK);
}

static t_state	parse_content(t_var *game)
{
	parse_configs(game);
	if (is_config_missing(game))
		return (print_missing_config(game), cleanup(game, true, 1), KO);
	// TODO: map parsing
	parse_map(game);
	return (OK);
}

t_state	parse(t_var *game, int ac, char **av)
{
	int		file_fd;

	file_fd = validate_map_filepath(game, ac, av);
	game->mapinfo.file_content = ft_readfile(file_fd, false);
	close(file_fd);
	if (!game->mapinfo.file_content)
	{
		ft_perror("Error: file is empty\n", av[1]),
		cleanup(game, true, 1);
		return (KO);
	}
	parse_content(game);
	return (OK);
}
