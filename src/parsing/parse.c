/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:46:08 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/04 14:43:28 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_parse.h>

static t_state	load_map(t_var *game)
{
	char	**file_content;
	int		i;

	file_content = game->mapinfo.file_content;
	i = str_mtxlen(file_content) - 1;
	if (i <= 0)
		return (pf_errcode(E_DEFAULT), cleanup(game, true, 1), KO);
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

static void	calc_map_size(t_var *game)
{
	int		i;

	game->mapinfo.rows_mtx = str_mtxlen(game->mapinfo.map);
	if (game->mapinfo.rows_mtx == 0)
		return ;
	game->mapinfo.cols_mtx = str_ilen(game->mapinfo.map[0]);
	i = -1;
	while (game->mapinfo.map[++i])
	{
		if (game->mapinfo.cols_mtx < str_ilen(game->mapinfo.map[i]))
			game->mapinfo.cols_mtx = str_ilen(game->mapinfo.map[i]);
	}
}

t_state	parse(t_var *game, int ac, char **av)
{
	int		file_fd;

	file_fd = parse_validate_map_filepath(game, ac, av);
	game->mapinfo.file_content = ft_readfile(file_fd, false);
	close(file_fd);
	if (!game->mapinfo.file_content)
	{
		ft_perror("Error: file is empty\n", av[1]),
		cleanup(game, true, 1);
		return (KO);
	}
	parse_configs(game);
	if (is_config_missing(game))
		return (print_missing_config(game), cleanup(game, true, 1), KO);
	load_map(game);
	calc_map_size(game);
	parse_map(game);
	return (OK);
}
