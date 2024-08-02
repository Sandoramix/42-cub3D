/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configurations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:21:15 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/02 20:50:59 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static bool	is_filepath_valid(char *line, int line_n, char *path)
{
	int	fd;

	if (file_isdir(path))
		return (ft_perror("Error on line %d: '%s':\n\t%s is a directory\n",
				line_n, line, path), false);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_perror("Error on line %d: '%s':\n\t%s : permission denied\n",
				line_n, line, path), false);
	close(fd);
	return (true);
}

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

static t_state	parse_config_line(t_var *game, char *line, int line_num)
{
	const t_cnf	type = parse_identify_cnf(line);
	char		*value;

	value = validate_config_line(game, line, line_num);
	if (parse_config_val_is_path(type))
	{
		// TODO create image from path (value)
	}
	else
	{
		// TODO parse color from value
	}
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
