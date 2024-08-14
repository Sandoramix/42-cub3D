#include <cub3D.h>

void	player_sprites_event_pressed(int keycode, t_var *game)
{
	if (keycode == XK_Control_R) // ctrl vicino alla freccia sinistra
		game->move.block = true;
}

void	player_sprites_event_released(int keycode, t_var *game)
{
	if (keycode == XK_Control_R) // ctrl vicino alla freccia sinistra
		game->move.block = false;
}



void	handle_player_sprites(t_var *game)
{
    if (game->move.block)
    {
        game->config.hands_sprites.slctd = game->config.hands_sprites.block;
        game->config.hands_sprites.slctd_screen_x = game->config.win_width / 2 + game->config.hands_sprites.block->width / 2 - 100;
    }
    if (!game->move.block)
    {
        game->config.hands_sprites.slctd = game->config.hands_sprites.rest;
        game->config.hands_sprites.slctd_screen_x = game->config.win_width - game->config.hands_sprites.rest->width;
    }
}