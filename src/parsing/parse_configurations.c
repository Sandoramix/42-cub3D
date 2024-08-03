/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configurations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:21:15 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/03 14:06:56 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

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

	existing_val = get_config_pointed_str(game, type);
	if (*existing_val)
		return (ft_perror("Error on line %d: '%s': duplicate config\n",
				line_n, line), cleanup(game, true, 1), NULL);
	splitted = str_split_first(line, ' ');
	if (!splitted)
		return (pf_errcode(E_MALLOC), cleanup(game, true, 1), NULL);
	if (parse_config_val_is_path(type)
		&& !is_filepath_valid(line, line_n, splitted[1]))
		return (str_freemtx(splitted), cleanup(game, true, 1), NULL);
	*existing_val = splitted[1];
	splitted[1] = NULL;
	return (str_freemtx(splitted), *existing_val);
}

int	validate_color_val(t_var *game, char **split, char *val, int line_num)
{
	int	*atoi;
	int	parsed_num;

	atoi = strict_atoi(val);
	if (!atoi)
		return (ft_perror("Error: line %d: cannot parse '%s' as a number\n",
				line_num, val),
			str_freemtx(split), cleanup(game, true, 1), INT_MIN);
	parsed_num = *atoi;
	free(atoi);
	if (parsed_num < 0 || parsed_num > 255)
		return (ft_perror("Error: line %d: color must be in range [0;255]. \
		Number passed instead: %d\n", line_num, val, parsed_num),
			str_freemtx(split), cleanup(game, true, 1), INT_MIN);
	return (parsed_num);
}

t_state	load_color(t_var *game, t_rgb *rgb, char *value, int line_num)
{
	char	**split;

	split = str_split(value, ',');
	if (!split)
		return (pf_errcode(E_MALLOC), cleanup(game, true, 1), KO);
	if (str_mtxlen(split) != 3)
		return (ft_perror("Error: line %d: invalid color value (%s)\n",
				line_num, value), str_freemtx(split),
			cleanup(game, true, 1), KO);
	rgb->color.red = validate_color_val(game, split, split[0], line_num);
	rgb->color.green = validate_color_val(game, split, split[1], line_num);
	rgb->color.blue = validate_color_val(game, split, split[2], line_num);
	return (OK);
}

static t_state	parse_config_line(t_var *game, char *line, int line_num)
{
	const t_cnf	type = parse_identify_cnf(line);
	char		*value;
	void		*parsed_data;

	value = validate_config_line(game, line, line_num);
	parsed_data = get_config_pointed_data(game, type);
	if (parse_config_val_is_path(type))
		load_xpm_image(game, parsed_data, value);
	else
		load_color(game, parsed_data, value, line_num);
	return (OK);
}

t_state	parse_configs(t_var *game)
{
	char	**filedata;
	int		i;

	i = -1;
	filedata = game->mapinfo.file_content;
	while (filedata[++i])
	{
		if (str_isblank(filedata[i]))
			continue ;
		if (!is_config_missing(game))
		{
			if (i > 0 && str_ilen(filedata[i - 1]) == 0)
				return (OK);
		}
		else if (parse_identify_cnf(filedata[i]) == CNF_UNKNOWN)
			return (ft_perror("Error on line %d: '%s':\n\t? configuration\n",
					i + 1, filedata[i]), cleanup(game, true, 1), KO);
		parse_config_line(game, filedata[i], i + 1);
	}
	return (OK);
}
