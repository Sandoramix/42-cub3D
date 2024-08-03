#include <cub3D.h>

int game_loop(t_var *game)
{
	(void)game;
	return 1;
}


void rotate_camera(t_var *game, int rotation_dir)
{
	double old_dir_x;
	double old_plane_x;

	if (rotation_dir == ROTAT_DIR_RIGHT)
	{
		old_dir_x = game->player_pos.dir_x;
		game->player_pos.dir_x = game->player_pos.dir_x * game->player_pos.neg_cos_rot_speed_pos \
		- game->player_pos.dir_y * game->player_pos.neg_sin_rot_speed_pos; 
		game->player_pos.dir_y = old_dir_x * game->player_pos.neg_sin_rot_speed_pos + game->player_pos.dir_y * game->player_pos.neg_cos_rot_speed_pos;
		old_plane_x = game->plane.x;
		game->plane.x = game->plane.x  * game->player_pos.neg_cos_rot_speed_pos - game->plane.y *  game->player_pos.neg_sin_rot_speed_pos;
		game->plane.y = old_plane_x *  game->player_pos.neg_sin_rot_speed_pos + game->plane.y * game->player_pos.neg_cos_rot_speed_pos; 
	}
	else
	{
		old_dir_x = game->player_pos.dir_x;
		game->player_pos.dir_x = game->player_pos.dir_x * game->player_pos.positive_cos_rot_speed \
		- game->player_pos.dir_y * game->player_pos.positive_sin_rot_speed; 
		game->player_pos.dir_y = old_dir_x * game->player_pos.positive_sin_rot_speed + game->player_pos.dir_y * game->player_pos.positive_cos_rot_speed;
		old_plane_x = game->plane.x;
		game->plane.x = game->plane.x  * game->player_pos.positive_cos_rot_speed - game->plane.y *  game->player_pos.positive_sin_rot_speed;
		game->plane.y = old_plane_x *  game->player_pos.positive_sin_rot_speed + game->plane.y * game->player_pos.positive_cos_rot_speed; 
	}

}

int key_press(int keycode, t_var *game)
{
	if (keycode == KEY_W)
        game->move.up = 1;
	if (keycode == KEY_S)
        game->move.down = 1;
	if (keycode == KEY_A)
        game->move.left = 1;
	if (keycode == KEY_D)
        game->move.right = 1;
	/*check rotazione*/
	if (keycode == XK_Left)
        game->move.rot_left = 1;
	if (keycode == XK_Right)
        game->move.rot_right = 1;
	/*movimento */
	if (game->move.up)
	    game->player_pos.y -= VELOCITY /* * game->deltatime  */;
	if (game->move.down)
	    game->player_pos.y += VELOCITY /* * game->deltatime  */;
	if (game->move.left)
	    game->player_pos.x -= VELOCITY /* * game->deltatime  */;
	if (game->move.right)
        game->player_pos.x += VELOCITY /* * game->deltatime  */;
	/**direzione */
	if (game->move.rot_left)
		rotate_camera(game , ROTAT_DIR_LEFT);
	if (game->move.rot_right)
		rotate_camera(game , ROTAT_DIR_RIGHT);


	raycasting(game);
	
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



