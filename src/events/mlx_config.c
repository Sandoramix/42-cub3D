#include <cub3D.h>


void load_sprites(t_var *game);

void config_event_handling(t_var *game)
{
    mlx_hook(game->mlx_win, KeyPress, KeyPressMask, &key_press, &game);
    mlx_hook(game->mlx_win, KeyRelease, KeyReleaseMask, &key_release, &game);
	mlx_hook(game->mlx_win, 17, 0, mlx_loop_end, game->mlx);
	mlx_loop_hook(game->mlx, &game_loop, &game);
}


void mlx_configuration(t_var *game)
{
    game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, 1600, 1080, "UrMom");

    //load_sprites();
    
    config_event_handling(game);
}