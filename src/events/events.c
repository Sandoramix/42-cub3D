#include <cub3D.h>

int game_loop(t_var *game)
{
	(void)game;
	return 1;
}

int key_press(int keycode, t_var *game)
{
    if (keycode == ESC_KEY) { 
        cleanup(game, true, 1);
        return (OK);
    }
	handle_player_movement(game, keycode);
    handle_player_rotation(game, keycode);
    
	rendering(game);
    game->move.rot_left = 0;
    game->move.rot_right = 0;
    return 0;
}

int key_release(int keycode, t_var *game)
{
    if (keycode == KEY_W)
        game->move.up = 0;
    if (keycode == KEY_S)
        game->move.down = 0;
    if (keycode == KEY_A)
        game->move.left = 0;
    if (keycode == KEY_D)
        game->move.right = 0;
    return 0;
}



