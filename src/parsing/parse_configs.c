/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:21:15 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 00:36:39 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_parse.h>

// *PRIVATE* functions used only by parsing
t_state	load_color(t_var *game, t_rgba *rgb, char *value, int line_num);
t_state	load_xpm_image(t_var *game, t_img **img, char *path);

/**
 * @brief Validate the configuration by checking if there's already set up the
 * same one and if the given path (if it should be one) is valid.
 * @param game game
 * @param line line to parse (`<CNF>` `<value>`)
 * @param line_n number of line (used for error printing)
 * @return `<value>`
 */
static char	*validate_config_line(t_var *game, char *line, int line_n)
{
	const t_cnf	type = parse_identify_cnf(line);
	char		**splitted;
	char		**existing_val;

	existing_val = parse_get_config_pointed_str(game, type);
	if (existing_val && *existing_val)
		return (ft_perror("Error on line %d: '%s': duplicate config\n",
				line_n, line), cleanup(game, true, 1), NULL);
	splitted = str_split_first(line, ' ');
	if (!splitted)
		return (pf_errcode(E_MALLOC), cleanup(game, true, 1), NULL);
	*existing_val = str_trim(splitted[1], " \t\r\v\n\f");
	if (!*existing_val)
		return (pf_errcode(E_MALLOC), cleanup(game, true, 1), NULL);
	if (parse_config_val_is_path(type)
		&& !parse_is_filepath_valid(line, line_n, *existing_val))
		return (str_freemtx(splitted), cleanup(game, true, 1), NULL);
	return (str_freemtx(splitted), *existing_val);
}

static t_state	parse_config_line(t_var *game, char *line, int line_num)
{
	const t_cnf	type = parse_identify_cnf(line);
	char		*value;
	void		*parsed_data;

	value = validate_config_line(game, line, line_num);
	parsed_data = parse_get_config_pointed_data(game, type);
	if (parse_config_val_is_path(type))
		load_xpm_image(game, parsed_data, value);
	else
		load_color(game, parsed_data, value, line_num);
	return (OK);
}

t_state	parse_configs(t_var *game)
{
	int		i;

	i = -1;
	while (game->map.filedata[++i])
	{
		if (str_ilen(game->map.filedata[i]) == 0)
			continue ;
		if (parse_identify_cnf(game->map.filedata[i]) != CNF_UNKNOWN)
			parse_config_line(game, game->map.filedata[i], i + 1);
		else if (!is_config_missing(game))
		{
			if (i > 0 && str_ilen(game->map.filedata[i - 1]) == 0)
				return (OK);
		}
		if (parse_identify_cnf(game->map.filedata[i]) == CNF_UNKNOWN)
		{
			if (game->map.map
				&& str_equals(game->map.filedata[i], game->map.map[0]))
				return (OK);
			return (ft_perror("Error on line %d: '%s':\n\t? configuration\n",
					i + 1, game->map.filedata[i]), cleanup(game, true, 1), KO);
		}
	}
	return (OK);
}
