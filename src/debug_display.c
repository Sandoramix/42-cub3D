#include <cub3D.h>

static char *dbg_get_fps(t_var *game)
{
	char	*text;
	char	*num;

	num = ft_itoa(1 / game->deltatime);
	text = str_join("FPS: ", num);
	free(num);
	return (text);
}

static char *dbg_get_position(t_var *game)
{
    char	*y_txt;
    char	*x_txt;
    char   *pos_x; 
    char   *pos_y;
    char   *final;
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
    char	*text;
    char	*num;

    num = ft_itoa((int)(atan2(game->player.dir_y, game->player.dir_x) * 180 / M_PI));
    text = str_join("Angle: ", num);
    free(num);
    return (text);
}


void debug_info(t_var *game)
{
        mlx_string_put(game->mlx, game->mlx_win, 16,
            game->config.win_height - 150, 0xFFFFFF, "DEBUG MODE");
        mlx_string_put(game->mlx, game->mlx_win, 16,
        game->config.win_height - 80, 0xFFFFFF, dbg_get_fps(game));
        mlx_string_put(game->mlx, game->mlx_win, 16,
        game->config.win_height - 100, 0xFFFFFF, dbg_get_position(game));
        mlx_string_put(game->mlx, game->mlx_win, 16,
        game->config.win_height - 120, 0xFFFFFF, dbg_get_player_angle(game));
}