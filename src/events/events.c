#include <cub3D.h>

int	game_loop(t_var *game)
{
	delta_time(game);
	//printf("planex : %f, planey %f\n", game->plane.x, game->plane.y);
	handle_player_movement(game);
	handle_player_rotation(game);

	rendering(game);
	return (1);
}

int	key_press(int keycode, t_var *game)
{
	if (keycode == ESC_KEY)
	{
		cleanup(game, true, 1);
		return (OK);
	}

	if (keycode == XK_w)
		game->move.up = true;
	if (keycode == XK_s)
		game->move.down = true;
	if (keycode == XK_d)
		game->move.right = true;
	if (keycode == XK_a)
		game->move.left = true;

	if (keycode == XK_Left)
		game->move.rot_left = true;
	if (keycode == XK_Right)
		game->move.rot_right = true;
	if (keycode == XK_Up)
		game->move.rot_up = true;
	if (keycode == XK_Down)
		game->move.rot_down = true;

	if (keycode == XK_space)
	{
		if(!game->move.jump)
		{
			game->move.jump = true;
			game->move.jump_mult = 1;
		}
	}
	if (keycode == XK_Shift_L)
		game->move.crouch = true;
	
	return (0);
}

int	key_release(int keycode, t_var *game)
{
	if (keycode == KEY_W)
		game->move.up = false;
	if (keycode == KEY_S)
		game->move.down = false;
	if (keycode == KEY_A)
		game->move.left = false;
	if (keycode == KEY_D)
		game->move.right = false;

	if (keycode == XK_Left)
		game->move.rot_left = false;
	if (keycode == XK_Right)
		game->move.rot_right = false;
	if (keycode == XK_Up)
		game->move.rot_up = false;
	if (keycode == XK_Down)
		game->move.rot_down = false;

	if (keycode == XK_Shift_L)
		game->move.crouch = false;

		
	return (0);
}
