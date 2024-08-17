/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:46:42 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 01:31:25 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

double	pi(void)
{
	return (acos(-1.0));
}

double	angle_to_radiant(double angle)
{
	return (angle * (pi() / 180));
}

double	normalize_to_one(double num)
{
	return (num - floor(num));
}

double	direction_to_angle(double x, double y)
{
	const double	angle_rad = atan2(y, x);
	double			angle_deg;

	angle_deg = angle_rad * (180.0 / pi());
	if (angle_deg < 0)
		angle_deg += 360.0;
	return (angle_deg);
}
