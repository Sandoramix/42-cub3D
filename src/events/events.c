#include <cub3D.h>

int	key_press(int keycode, t_var *game)
{
	if (keycode == ESC_KEY)
		return (cleanup(game, true, 0), OK);

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

	if (keycode == XK_space && !game->move.jump)
	{
		game->move.jump = true;
		game->move.jump_mult = 1;
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

	// TODO MOVEMENT OSCILLATION
	//if (!game->move.up && !game->move.down &&
	//	!game->move.left && !game->move.right)
	//	game->player.travel_count = 0;
	return (0);
}
