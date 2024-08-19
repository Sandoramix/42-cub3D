/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:42:10 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/19 15:16:42 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSE_H
# define CUB3D_PARSE_H

# include <cub3D.h>

int			parse_validate_map_filepath(t_var *game, int ac, char **av);

t_state		parse_configs(t_var *game);
t_state		parse_map(t_var *game);
//------------------------------------------------------------------------------
// UTILS

char		get_map_at(t_var *game, int row_idx, int col_idx);

char		**parse_get_config_pointed_str(t_var *game, t_cnf type);
/**
 * @brief Get a pointer of given type's configuration, it can be either
 * `t_img *` or `t_rgba *`
 */
void		*parse_get_config_pointed_data(t_var *game, t_cnf type);

t_cnf		parse_identify_cnf(char *line);
bool		parse_config_val_is_path(t_cnf type);
bool		parse_is_filepath_valid(char *line, int line_n, char *path);

#endif