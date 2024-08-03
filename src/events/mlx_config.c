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
    mlx_get_screen_size(game->mlx, &game->dda.screen_size_w_px, &game->dda.screen_size_h_px);
    dbg_printf("screen size, x y: %d %d\n",game->dda.screen_size_w_px, game->dda.screen_size_h_px );
	game->mlx_win = mlx_new_window(game->mlx, game->dda.screen_size_w_px, game->dda.screen_size_h_px, "UrMom");
    
    game->img = mlx_new_image(game->mlx, game->dda.screen_size_w_px, game->dda.screen_size_h_px);
	game->buffer = mlx_get_data_addr(game->img, &game->bpp, &game->line_bytes, &game->endian);
    
    //load_sprites();
    raycasting(game);
    config_event_handling(game);
}