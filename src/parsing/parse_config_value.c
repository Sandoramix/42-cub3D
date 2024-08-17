/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:37:39 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 15:24:59 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	validate_color_val(t_var *game, char **split,
		char *val, int line_num)
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
		Number passed instead: %d\n", line_num, parsed_num),
			str_freemtx(split), cleanup(game, true, 1), INT_MIN);
	return (parsed_num);
}

t_state	load_color(t_var *game, t_rgba *rgba, char *value, int line_num)
{
	char	**split;

	split = str_split(value, ',');
	if (!split)
		return (pf_errcode(E_MALLOC), cleanup(game, true, 1), KO);
	if (str_mtxlen(split) != 3)
		return (ft_perror("Error: line %d: invalid color value (%s)\n",
				line_num, value), str_freemtx(split),
			cleanup(game, true, 1), KO);
	rgba->red = validate_color_val(game, split, split[0], line_num);
	rgba->green = validate_color_val(game, split, split[1], line_num);
	rgba->blue = validate_color_val(game, split, split[2], line_num);
	rgba->alpha = 0xFF;
	rgba->hex = rgba_to_hex(*rgba);
	str_freemtx(split);
	return (OK);
}

t_state	load_xpm_image(t_var *game, t_img **img, char *path)
{
	void	*res;

	res = mlx_xpm_file_to_image(game->mlx, path,
			&game->cnf._w, &game->cnf._h);
	if (!res)
		return (ft_perror("Error: cannot load sprite from '%s'. \
		Check if it is a valid xpm image\n", path),
			cleanup(game, true, 1), KO);
	*img = res;
	return (OK);
}
