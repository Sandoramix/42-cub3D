/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:46:08 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 00:36:39 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_parse.h>

static t_state	load_map(t_var *game)
{
	char	**filedata;
	int		i;

	filedata = game->map.filedata;
	i = str_mtxlen(filedata) - 1;
	if (i <= 0)
		return (pf_errcode(E_DEFAULT), cleanup(game, true, 1), KO);
	while (i >= 0)
	{
		if (parse_identify_cnf(filedata[i]) != CNF_UNKNOWN
			|| !str_ilen(filedata[i]))
		{
			i++;
			break ;
		}
		i--;
	}
	while (filedata[i] && str_ilen(filedata[i]) == 0)
		i++;
	game->map.map = str_mtxdup(&filedata[i]);
	if (!game->map.map)
		return (pf_errcode(E_MALLOC), cleanup(game, true, 1), KO);
	return (OK);
}

static void	calc_map_size(t_var *game)
{
	int		i;

	game->map.rows_mtx = str_mtxlen(game->map.map);
	if (game->map.rows_mtx == 0)
		return ;
	game->map.cols_mtx = str_ilen(game->map.map[0]);
	i = -1;
	while (game->map.map[++i])
	{
		if (game->map.cols_mtx < str_ilen(game->map.map[i]))
			game->map.cols_mtx = str_ilen(game->map.map[i]);
	}
}

t_state	parse(t_var *game, int ac, char **av)
{
	int		file_fd;

	file_fd = parse_validate_map_filepath(game, ac, av);
	game->map.filedata = ft_readfile(file_fd, false);
	game->map.filedata_size = str_mtxlen(game->map.filedata);
	close(file_fd);
	if (!game->map.filedata)
	{
		ft_perror("Error: file is empty\n", av[1]),
		cleanup(game, true, 1);
		return (KO);
	}
	load_map(game);
	parse_configs(game);
	if (is_config_missing(game))
		return (print_missing_config(game), cleanup(game, true, 1), KO);
	calc_map_size(game);
	parse_map(game);
	return (OK);
}
