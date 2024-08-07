#include <cub3D.h>

void load_sprites(t_var *game);

void	config_event_handling(t_var *game)
{
	mlx_hook(game->mlx_win, KeyPress, KeyPressMask, &key_press, game);
	mlx_hook(game->mlx_win, KeyRelease, KeyReleaseMask, &key_release, game);
	mlx_hook(game->mlx_win, 17, 0, mlx_loop_end, game->mlx);
	mlx_loop_hook(game->mlx, &game_loop, game);
}

void mlx_configuration(t_var *game)
{
	mlx_get_screen_size(game->mlx, &game->config._w, &game->config._h);
	game->mlx_win = mlx_new_window(game->mlx, game->config._w, game->config._h, WINDOW_NAME);
	game->img = mlx_new_image(game->mlx, game->config._w, game->config._h);
	game->buffer = mlx_get_data_addr(game->img, &game->bpp, &game->line_bytes, &game->endian);

    //load_sprites();
	rendering(game);
	config_event_handling(game);
}