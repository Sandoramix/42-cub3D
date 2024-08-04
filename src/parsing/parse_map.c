/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:43:00 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/04 12:04:39 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static double	get_player_angle(char player_c)
{
	if (player_c == MAP_PLAYER_NORD)
		return (360.0 - 90.0);
	if (player_c == MAP_PLAYER_EAST)
		return (0.0);
	if (player_c == MAP_PLAYER_WEST)
		return (180.0);
	if (player_c == MAP_PLAYER_SOUTH)
		return (90.0);
	return (0.0);
}

static t_state	doubles_check(t_var *game, char **map, int i, int j)
{
	static int	player_count = 0;
	char		char_at_pos;

	char_at_pos = map[i][j];
	if (chr_is_player(char_at_pos))
		player_count++;
	if (player_count > 1)
		return (ft_perror("Error: Invalid map:" \
		" multiple players found at row=%d;col=%d (%c)\n", i + 1, j + 1,
				char_at_pos), cleanup(game, true, 1), KO);
	return (OK);
}

static void	surrounding_check(t_var *game, char **map, int i, int j)
{
	(void)game;
	(void)map;
	(void)i;
	(void)j;
	// TODO
}

static t_state	validate_map(t_var *game)
{
	int		i;
	int		j;
	char	**map;

	map = game->mapinfo.map;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (chr_is_player(map[i][j]))
				update_player(game, j, i, get_player_angle(map[i][j]));
			doubles_check(game, map, i, j);
			surrounding_check(game, map, i, j);
		}
	}
	return (OK);
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
	validate_map(game);
	return (OK);
}
