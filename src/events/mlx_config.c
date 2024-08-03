#include <cub3D.h>


void load_sprites(t_var *game);

void config_event_handling(t_var *game)
{
    mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &key_press, &game);
    mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, &key_release, &game);
	mlx_hook(game->win_ptr, 17, 0, mlx_loop_end, game->mlx);
	mlx_loop_hook(game->mlx, &game_loop, &game);
}


void mlx_configuration(t_var *game)
{
    game->mlx = mlx_init();
    mlx_get_screen_size(game->mlx, &game->dda.screen_size_w_px, &game->dda.screen_size_h_px);
    dbg_printf("screen size, x y: %d %d\n",game->dda.screen_size_w_px, game->dda.screen_size_h_px );
	game->win_ptr = mlx_new_window(game->mlx, game->dda.screen_size_w_px, game->dda.screen_size_h_px, "UrMom");

    //load_sprites();
    raycasting(game);
    config_event_handling(game);
}