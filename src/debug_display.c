#include <cub3D.h>

static char *dbg_get_fps(t_var *game)
{
    char *text;
    char *num;

    num = ft_itoa(1 / game->deltatime);
    text = str_join("FPS: ", num);
    free(num);
    return (text);
}

static char *dbg_get_position(t_var *game)
{
    char *y_txt;
    char *x_txt;
    char *pos_x;
    char *pos_y;
    char *final;
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

static char *dbg_get_player_angle(t_var *game)
{
    char *text;
    char *num;

    num = ft_itoa((int)(atan2(game->player.dir_y, game->player.dir_x) * 180 / M_PI));
    text = str_join("Angle: ", num);
    free(num);
    return (text);
}

char *ftoa(char *buffer, double d, int precision) {

	long wholePart = (long) d;

	// Deposit the whole part of the number.

	buffer = ft_itoa(wholePart);

	// Now work on the faction if we need one.

	if (precision > 0) {

		// We do, so locate the end of the string and insert
		// a decimal point.

		char *endOfString = buffer;
		while (*endOfString != '\0') endOfString++;
		*endOfString++ = '.';

		// Now work on the fraction, be sure to turn any negative
		// values positive.

		if (d < 0) {
			d *= -1;
			wholePart *= -1;
		}
		
		double fraction = d - wholePart;
		while (precision > 0) {

			// Multipleby ten and pull out the digit.

			fraction *= 10;
			wholePart = (long) fraction;
			*endOfString++ = '0' + wholePart;

			// Update the fraction and move on to the
			// next digit.

			fraction -= wholePart;
			precision--;
		}

		// Terminate the string.

		*endOfString = '\0';
	}

    return buffer;
}

static char *dbg_player_distance_from_wall(t_var *game)
{
    const int x = game->config.win_width / 10;
    printf("x: %d\n", x);
    char *final;
    char *walldist;
    final = NULL;
    (void)walldist;
    //TODO understand why i m getting always the length of the last column on the right
    init_vars(game, x);
    calc_direction(game);
    loop_until_hit_wall(game);
    get_wall_coords(game);
    final = ftoa(final, game->engine.wall_dist, 5);
    return (final);
}

void debug_info(t_var *game)
{
    //TODO solve the memory leak
    mlx_string_put(game->mlx, game->mlx_win, 16,
                   game->config.win_height - 150, 0xFFFFFF, "DEBUG MODE");
    mlx_string_put(game->mlx, game->mlx_win, 16,
                   game->config.win_height - 80, 0xFFFFFF, dbg_get_fps(game));
    mlx_string_put(game->mlx, game->mlx_win, 16,
                   game->config.win_height - 100, 0xFFFFFF, dbg_get_position(game));
    mlx_string_put(game->mlx, game->mlx_win, 16,
                   game->config.win_height - 120, 0xFFFFFF, dbg_get_player_angle(game));
    mlx_string_put(game->mlx, game->mlx_win, 16,
                   game->config.win_height - 60, 0xFFFFFF, dbg_player_distance_from_wall(game));
}