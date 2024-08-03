#include <cub3D.h>

int handle_wll_collision(t_var *game, int x, int y) {
    if (x < 0 || x >= game->mapinfo.cols_mtx || y < 0
		|| y >= game->mapinfo.rows_mtx || game->mapinfo.mtxint[x][y] == 1)
        return (OK);
    return (KO);
}

void handle_camera_rotation(t_var *game, int rotation_dir)
{
	double old_dir_x;
	double old_plane_x;

	if (rotation_dir == ROTAT_DIR_RIGHT)
	{
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * game->player.neg_cos_rot_speed_pos \
		- game->player.dir_y * game->player.neg_sin_rot_speed_pos; 
		game->player.dir_y = old_dir_x * game->player.neg_sin_rot_speed_pos + game->player.dir_y * game->player.neg_cos_rot_speed_pos;
		old_plane_x = game->plane.x;
		game->plane.x = game->plane.x  * game->player.neg_cos_rot_speed_pos - game->plane.y *  game->player.neg_sin_rot_speed_pos;
		game->plane.y = old_plane_x *  game->player.neg_sin_rot_speed_pos + game->plane.y * game->player.neg_cos_rot_speed_pos; 
	}
	else
	{
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * game->player.positive_cos_rot_speed \
		- game->player.dir_y * game->player.positive_sin_rot_speed; 
		game->player.dir_y = old_dir_x * game->player.positive_sin_rot_speed + game->player.dir_y * game->player.positive_cos_rot_speed;
		old_plane_x = game->plane.x;
		game->plane.x = game->plane.x  * game->player.positive_cos_rot_speed - game->plane.y *  game->player.positive_sin_rot_speed;
		game->plane.y = old_plane_x *  game->player.positive_sin_rot_speed + game->plane.y * game->player.positive_cos_rot_speed; 
	}

}

void handle_player_movement(t_var *game, int keycode)
{
	double new_x;
	double new_y;

	if (keycode == KEY_W) {
        new_y = game->player.y - VELOCITY;
        if (!handle_wll_collision(game, (int)game->player.x, (int)new_y)) {
            game->player.y = new_y;
        }
    }
    if (keycode == KEY_S) {
        new_y = game->player.y + VELOCITY;
        if (!handle_wll_collision(game, (int)game->player.x, (int)new_y)) {
            game->player.y = new_y;
        }
    }
    if (keycode == KEY_A) {
        new_x = game->player.x - VELOCITY;
        if (!handle_wll_collision(game, (int)new_x, (int)game->player.y)) {
            game->player.x = new_x;
        }
    }
    if (keycode == KEY_D) {
        new_x = game->player.x + VELOCITY;
        if (!handle_wll_collision(game, (int)new_x, (int)game->player.y)) {
            game->player.x = new_x;
        }
    }
}

void handle_player_rotation(t_var *game, int keycode)
{
	if (keycode == XK_Left)
        game->move.rot_left = 1;
    if (keycode == XK_Right)
        game->move.rot_right = 1;
    if (game->move.rot_left)
        handle_camera_rotation(game , ROTAT_DIR_LEFT);
    if (game->move.rot_right)
        handle_camera_rotation(game , ROTAT_DIR_RIGHT);
}
