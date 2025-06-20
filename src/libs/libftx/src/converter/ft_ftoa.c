/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_crosshair.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 02:11:13 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 15:24:59 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	invert_negative(float *d, long *whole_part)
{
	if (*d >= 0.0)
		return ;
	*d = *d * -1;
	*whole_part = *whole_part * -1;
}

char	*ft_ftoa(float d, int precision)
{
	char	*buffer;
	float	fraction;
	long	whole_part;

	whole_part = (long) d;
	buffer = ft_itoa(d);
	if (precision > 0)
	{
		buffer = str_pushchar(buffer, '.');
		invert_negative(&d, &whole_part);
		fraction = d - whole_part;
		while (precision > 0)
		{
			fraction *= 10;
			whole_part = (long) fraction;
			buffer = str_pushchar(buffer, '0' + whole_part);
			fraction -= whole_part;
			precision--;
		}
	}
	return (buffer);
}
