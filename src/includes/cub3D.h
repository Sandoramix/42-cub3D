/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:59:50 by odudniak          #+#    #+#             */
/*   Updated: 2024/07/31 17:20:56 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <mlx.h>
# include <mlx_int.h>

# include <cub3D_settings.h>
# include <cub3D_structs.h>

// PARSING----------------------------------------------------------------------
void	parse(t_var *game, int ac, char **av);
//------------------------------------------------------------------------------

// RAYCASTING-------------------------------------------------------------------
void	calculate_DDA(t_var *game);
void	calc_initial_step_intial_raylen(t_var *game);
void	increase_raylen(t_var *game);
void	calc_distance_from_wall(t_var *game);
void	calc_perspective(t_var *game);
//------------------------------------------------------------------------------

double	delta_time(t_var *game);

#endif