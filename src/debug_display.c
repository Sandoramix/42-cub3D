#include <cub3D.h>

static char	*dbg_get_fps(t_var *game)
{
	char	*text;
	char	*num;

	num = ft_itoa(1 / game->deltatime);
	text = str_join("FPS: ", num);
	free(num);
	return (text);
}

static char	*dbg_get_position(t_var *game)
{
	char	*y_txt;
	char	*x_txt;
	char	*pos_x;
	char	*pos_y;
	char	*final;

	pos_x = ft_itoa((int)game->player.x_px);
	pos_y = ft_itoa((int)game->player.y_px);
	x_txt = str_join("X: ", pos_x);
	y_txt = str_join(" Y: ", pos_y);
	final = str_join(x_txt, y_txt);

	free(x_txt);
	free(pos_x);
	free(pos_y);
	free(y_txt);
	return (final);
}

static char	*dbg_get_player_angle(t_var *game)
{
	char	*text;
	char	*num;

	num = ft_itoa((atan2(game->player.dir_y, game->player.dir_x) * 180 / pi()));
	text = str_join("Angle: ", num);
	free(num);
	return (text);
}

char	*ftoa(char *buffer, double d, int precision)
{
	double	fraction;
	long	whole_part;

	whole_part = (long) d;
	// Deposit the whole part of the number.
	buffer = ft_itoa(d);
	// Now work on the faction if we need one.
	if (precision > 0)
	{
		// We do, so locate the end of the string and insert a decimal point.
		buffer = str_pushchar(buffer, '.');
		// Now work on the fraction, be sure to turn any negative values positive.
		if (d < 0)
		{
			d *= -1;
			whole_part *= -1;
		}
		fraction = d - whole_part;
		while (precision > 0)
		{
			// Multiple by ten and pull out the digit.
			fraction *= 10;
			whole_part = (long) fraction;
			buffer = str_pushchar(buffer, '0' + whole_part);
			// Update the fraction and move on to the next digit.
			fraction -= whole_part;
			precision--;
		}
	}
	return (buffer);
}

static char	*dbg_get_mouse_position(t_var *game)
{
	char	*x_txt;
	char	*y_txt;
	char	*pos_x;
	char	*pos_y;
	char	*final;

	pos_x = ft_itoa(game->mouse.pos.x);
	pos_y = ft_itoa(game->mouse.pos.y);
	x_txt = str_join("Mouse X: ", pos_x);
	y_txt = str_join(" Y: ", pos_y);
	final = str_join(x_txt, y_txt);

	free(x_txt);
	free(pos_x);
	free(pos_y);
	free(y_txt);
	return (final);
}

/* static char	*dbg_player_distance_from_wall(t_var *game)
{
	const int		x = game->config.win_width / 10;
	char			*final;

	final = NULL;
	//TODO understand why i m getting always the length of the last column on the right
	init_vars(game, x);
	calc_direction(game);
	loop_until_hit_wall(game);
	get_wall_coords(game);
	final = ftoa(final, game->engine.wall.dist, 5);
	return (final);
} */

static char	**allocate_infos(t_var *game)
{
	char	**res;

	res = ft_calloc(6, sizeof(char *));
	if (!res)
		return (pf_errcode(E_MALLOC), cleanup(game, true, 1), NULL);
	res[0] = str_dup("DEBUG_MODE");
	res[1] = dbg_get_fps(game);
	res[2] = dbg_get_position(game);
	res[3] = dbg_get_player_angle(game);
	//res[4] = dbg_player_distance_from_wall(game);
	res[4] = dbg_get_mouse_position(game);
	return (res);
}


void	debug_info(t_var *game)
{
	char	**infos;

	infos = allocate_infos(game);
	mlx_string_put(game->mlx, game->mlx_win, 16,
		game->config.win_height - 150, 0xFFFFFF, infos[0]);
	mlx_string_put(game->mlx, game->mlx_win, 16,
		game->config.win_height - 80, 0xFFFFFF, infos[1]);
	mlx_string_put(game->mlx, game->mlx_win, 16,
		game->config.win_height - 100, 0xFFFFFF, infos[2]);
	mlx_string_put(game->mlx, game->mlx_win, 16,
		game->config.win_height - 120, 0xFFFFFF, infos[3]);
	mlx_string_put(game->mlx, game->mlx_win, 16,
		game->config.win_height - 60, 0xFFFFFF, infos[4]);
	str_freemtx(infos);
}
