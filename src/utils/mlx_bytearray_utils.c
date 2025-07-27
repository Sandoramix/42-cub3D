/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bytearray_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 05:37:16 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/27 05:43:07 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_argb	bytearray_get_color(t_img *img, t_ivec2 pos)
{
	char	*px;

	px = img->data + (pos.y * img->size_line + pos.x * (img->bpp / 8));
	return (hex_to_argb(*(t_uint *)px));
}

int	bytearray_coord_idx(t_img *img, t_ivec2 pos)
{
	return (pos.y * img->size_line + pos.x * (img->bpp / 8));
}
