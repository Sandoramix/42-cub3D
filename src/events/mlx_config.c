#include <cub3D.h>


void load_sprites(t_var *game);

void config_event_handling(t_var *game)
{
    mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &key_press, &game);
    mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, &key_release, &game);
	mlx_hook(game->win_ptr, 17, 0, mlx_loop_end, game->mlx_ptr);
	mlx_loop_hook(game->mlx_ptr, &game_loop, &game);
}


void mlx_configuration(t_var *game)
{
    game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, 1600, 1080, "UrMom");

    //load_sprites();
    
    config_event_handling(game);
}