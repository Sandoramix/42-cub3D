/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:11:29 by odudniak          #+#    #+#             */
/*   Updated: 2024/07/31 17:13:37 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	cleanup(t_var *game, bool should_exit, int statuscode)
{
	(void)game;
	if (should_exit)
		exit(statuscode);
	return (statuscode);
}