/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_rendering.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:03:11 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/18 15:17:11 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_RENDERING_H
# define CUB3D_RENDERING_H

# include <cub3D.h>

// RENDERING--------------------------------------------------------------------
void		render_base(t_var *g);
void		render_sprites(t_var *g, t_playersprites *sprites);
void		render_minimap(t_var *g);
/**
 * @brief Tunnable crosshair, just need to change `cross_thickness`
 * and `cross_length` inside the function xD
 * @note #### TODO add the cursor's parameters inside global configuration.
 * @param game game obj
 */
void		render_crosshair(t_var *game);

// RAYCASTING--------------------------
void		init_raycast_vars(t_var *game, t_raycast *eng, t_player *pl, int x);
void		get_wall_coords(t_var *g, t_raycast *eng, t_wall *wall);
void		loop_until_hit_wall(t_var *g);
//------------------------------------------------------------------------------
// TEXTURE---------------------------------------------------------------------
int			calc_text_x(t_var *g);
int			calc_text_y(t_var *game);
void		calc_scaled_textpos(t_var *game,
				t_raycast *engine, t_player *player);
t_rgba		get_texture_color(t_var *g, int tex_x, int tex_y);

//------------------------------------------------------------------------------
void		calc_direction(t_raycast *eng, t_player *pl);
//------------------------------------------------------------------------------

#endif
