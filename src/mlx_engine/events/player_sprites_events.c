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
        game->config.sprites.slctd = game->config.sprites.block;
        game->config.sprites.slctd_buff = game->config.sprites.block_buff;
        game->config.sprites.slctd_screen_x = game->config.win_width / 2 + game->config.sprites.block->width / 2 - 100;
    }
    if (!game->move.block)
    {
        game->config.sprites.slctd = game->config.sprites.rest;
        game->config.sprites.slctd_buff = game->config.sprites.rest_buff;
        game->config.sprites.slctd_screen_x = game->config.win_width - game->config.sprites.rest->width;
    }
}