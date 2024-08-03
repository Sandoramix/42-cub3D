#include <cub3D.h>


void load_sprites(t_var *game);



void config_event_handling(t_var *game)
{
    mlx_hook(game->mlx_win, KeyPress, KeyPressMask, &key_press, game);
    mlx_hook(game->mlx_win, KeyRelease, KeyReleaseMask, &key_release, game);
	mlx_hook(game->mlx_win, 17, 0, mlx_loop_end, game->mlx);
	mlx_loop_hook(game->mlx, &game_loop, game);
}


void mlx_configuration(t_var *game)
{
    game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
    game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->buffer = mlx_get_data_addr(game->img, &game->bpp, &game->line_bytes, &game->endian);
    
    //load_sprites();
    rendering(game);
    config_event_handling(game);
}