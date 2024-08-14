/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 02:31:03 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/14 02:31:10 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_rgba	get_texture_color(t_var *game, int tex_x, int tex_y)
{
	t_img	*texture;
	t_uint	color_value;
	char *pixel;

	texture = game->engine.texture.hit_texture;
	pixel = texture->data + (tex_y * texture->size_line) + (tex_x * 4);
	color_value = *(t_uint *)(pixel);
	return (hex_to_rgba(color_value));
}

void	calc_scaled_textpos(t_var *game, t_raycast *engine, t_player *player)
{
	const double z_offset = player->offset+ ((player->pos_z
						+ player->head_pos_z) / engine->wall_dist);
	const double half_win_height = game->config.win_height / 2;
	const double half_wall_height = engine->wall_height / 2;

	engine->texture.scale = 1.0 * (double)TILE_SIZE
		/ (double)engine->wall_height;
	engine->texture.scaled_textpos = (engine->wall_ceil
			- (half_win_height + z_offset)
			+ half_wall_height) * engine->texture.scale;
}

int	calc_text_y(t_var *game)
{
	int	text_y;

	text_y = (int)game->engine.texture.scaled_textpos
		& (game->engine.texture.hit_texture->height - 1);
	return (text_y);
}

int	calc_text_x(t_var *game)
{
	const t_raycast	*engine = &game->engine;
	int				tex_x;
	double			text_perc_px_hit;

	if (isinf(engine->dir.x) || isinf(engine->dir.y))
		return (KO); // i dont like it cause its zero, but i dont like -1 as well

	text_perc_px_hit = normalize_to_one(calc_wall_px_hit(game));
	tex_x = (int)(text_perc_px_hit * (double)TILE_SIZE);

	return (tex_x);
}

