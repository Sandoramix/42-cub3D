/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 02:31:03 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/19 16:11:23 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_rgba	get_texture_color(t_var *game, int tex_x, int tex_y)
{
	t_img	*texture;
	t_uint	color_value;
	char	*pixel;

	texture = game->engine.texture.hit_texture;
	pixel = texture->data + (tex_y * texture->size_line)
		+ (tex_x * texture->bpp / 8);
	color_value = *(t_uint *)(pixel);
	return (hex_to_rgba(color_value));
}

void	calc_scaled_textpos(t_var *game, t_raycast *engine, t_player *player)
{
	const double	z_offset = player->offset + ((player->pos_z
				+ player->head_pos_z) / engine->wall.dist);
	const double	half_win_height = game->cnf.window_height / 2;
	const double	half_wall_height = engine->wall.height / 2;

	engine->texture.scale = 1.0 / engine->wall.height;
	engine->texture.scaled_textpos = (engine->wall.ceil
			- (half_win_height + z_offset)
			+ half_wall_height) * engine->texture.scale;
}

int	calc_text_y(t_var *game)
{
	const t_img	*texture = game->engine.texture.hit_texture;
	int			text_y;

	if (!texture)
		return (0);
	text_y = game->engine.texture.scaled_textpos * texture->height;
	if (texture && texture->height > 0 && text_y >= texture->height)
		text_y = texture->height - 1;
	text_y = int_imax(0, text_y);
	return (text_y);
}

int	calc_text_x(t_var *game)
{
	const t_raycast	*engine = &game->engine;
	const t_img		*texture = game->engine.texture.hit_texture;
	int				tex_x;
	double			text_perc_px_hit;

	if (!texture)
		return (0);
	if (isinf(engine->dir.x) || isinf(engine->dir.y))
		return (KO);
	text_perc_px_hit = normalize_to_one(calc_wall_px_hit(game));
	tex_x = (int)(text_perc_px_hit * texture->width);
	if (texture && texture->width > 0 && tex_x >= texture->width)
		tex_x = texture->width - 1;
	tex_x = int_imax(0, tex_x);
	return (tex_x);
}
