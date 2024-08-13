/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:43:00 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/14 00:26:42 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_parse.h>

static t_state	doubles_check(t_var *game, char **map, int row_idx, int col_idx)
{
	static int	player_count = 0;
	char		char_at_pos;

	char_at_pos = map[row_idx][col_idx];
	if (chr_is_player(char_at_pos))
		player_count++;
	if (player_count > 1)
		return (ft_perror("Error: Invalid map: multiple players found"\
		" at row=%d;col=%d (%c)\n", row_idx + 1, col_idx + 1,
				char_at_pos), cleanup(game, true, 1), KO);
	return (OK);
}

static bool	is_correctly_surrounded(t_var *game, int row_idx, int col_idx)
{
	const char	char_at_pos = get_map_at(game, row_idx, col_idx);
	const int	directions[][4] = {{row_idx - 1, col_idx},
	{row_idx + 1, col_idx}, {row_idx, col_idx - 1}, {row_idx, col_idx + 1}};
	char		chr;
	int			i;

	if (!chr_is_player(char_at_pos) && char_at_pos != MAP_FLOOR)
		return (true);
	i = -1;
	while (++i < 4)
	{
		chr = get_map_at(game, directions[i][0], directions[i][1]);
		if (!chr_is_player(chr) && chr != MAP_FLOOR && chr != MAP_WALL)
			return (false);
	}
	return (true);
}

static t_state	surrounding_check(t_var *game, int row_idx, int col_idx)
{
	const char	chr_curr = get_map_at(game, row_idx, col_idx);

	if (chr_curr == MAP_WALL)
		return (OK);
	if (!is_correctly_surrounded(game, row_idx, col_idx))
		return (ft_perror("Error: Invalid map: '%c' is not permitted "\
		"on row=%d;col=%d", chr_curr, row_idx + 1, col_idx + 1),
			cleanup(game, true, 1), KO);
	return (OK);
}

t_state	parse_map(t_var *game)
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
				init_player(game, j, i, chr_player_to_direction(map[i][j]));
			doubles_check(game, map, i, j);
			surrounding_check(game, i, j);
		}
	}
	return (OK);
}
