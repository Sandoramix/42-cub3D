#include <cub3D.h>

void handle_camera_rotation(t_var *game, int dir)
{
	const double	cos_res =  cos(dir * game->config.defaults.rot_speed);
	const double	sin_res =  sin(dir * game->config.defaults.rot_speed);
	double			old_dir_y;
	double			old_plane_x;

	old_dir_y = game->player.dir_y;
	game->player.dir_y = old_dir_y * cos_res - game->player.dir_x * sin_res;
	game->player.dir_x = old_dir_y * sin_res + game->player.dir_x * cos_res;
	old_plane_x = game->engine.plane.x;
	game->engine.plane.x = game->engine.plane.x * cos_res
		- game->engine.plane.y * sin_res;
	game->engine.plane.y = old_plane_x * sin_res
		+ game->engine.plane.y * cos_res;
}

static t_state	handle_wll_collision(t_var *game, double x, double y)
{

	if (x < TILE_SIZE
		|| x >= game->mapinfo.cols_mtx * TILE_SIZE - TILE_SIZE
		|| y < TILE_SIZE
		|| y >= game->mapinfo.rows_mtx * TILE_SIZE - TILE_SIZE
		|| get_map_at(game, (y / TILE_SIZE), (x / TILE_SIZE)) == MAP_WALL)
	{
		if (ft_isdebug())
			printf("Can't move,"
				"the player position will be [%.2f][%.2f]\n", x, y);
		return (KO);
	}
	return (OK);
}

void handle_player_movement(t_var *game)
{
	const int	dir_y = (int[2]){1, -1}[game->move.up];
	const int	dir_x = (int[2]){-1, 1}[game->move.right];
	double		new_x;
	double		new_y;


	game->engine.plane.x = -game->player.dir_y * game->config.plane_limit;  // Perpendicular to dir_x
	game->engine.plane.y = game->player.dir_x * game->config.plane_limit; 	// Perpendicular to dir_y

	new_x = game->player.x_px;
	new_y = game->player.y_px;
	if (game->move.up || game->move.down)
	{
		new_x -= (dir_y * (game->player.dir_x * VELOCITY * game->deltatime));
		new_y -= (dir_y * (game->player.dir_y * VELOCITY * game->deltatime));
	}
	if (game->move.left || game->move.right)
	{
		new_x -= (dir_x * (game->player.dir_y * VELOCITY * game->deltatime));
		new_y += (dir_x * (game->player.dir_x * VELOCITY * game->deltatime));
	}
	if (handle_wll_collision(game, new_x, new_y) == OK)
		set_player_dpos(game, (t_dpoint){new_x, new_y});
	//! TODO MOVEMENT OSCILLATION
	// Do we like it? Yes. Is it a priority? No
	//if (game->move.up || game->move.down || game->move.left || game->move.right)
	//{
	//	game->player.travel_count += .35;
	//	if (game->player.travel_count < 0.0)
	//		game->player.travel_count = 0.0;
	//	game->player.head_pos_z = ((sin(game->player.travel_count) + 1.0) / 2) * 169;
	//}

}

void handle_player_rotation(t_var *game)
{
	float value;
	if (game->move.rot_left)
	handle_camera_rotation(game, 1.);
	if (game->move.rot_right)
	handle_camera_rotation(game, -1.);
	
	if (game->move.rot_up)
	{
		game->player.offset += VELOCITY * game->deltatime;
		if (game->player.offset > CAMERA_HIGH_LIMIT)
			game->player.offset = CAMERA_HIGH_LIMIT;
	}
	if (game->move.rot_down)
	{
		game->player.offset -= VELOCITY * game->deltatime;
		if (game->player.offset < CAMERA_LOW_LIMIT)
			game->player.offset = CAMERA_LOW_LIMIT;
	}
	if (game->player.offset > 0)
	{
		value = game->player.offset * 0.9f;
		game->player.offset = (float[2]){0, value}[0.1f < value];
	}
	if (game->player.offset < 0)
	{
		value = game->player.offset * 0.9f;
		game->player.offset = (float[2]){0, value}[-0.1f > value];
	}
	// pos z per il momento e' sempre zero
	//  serve a gestire la posizione del player sull asse z
	// devo solo implementare il keyhook a questo punto
	if (game->move.jump && game->move.jump_mult == 1)
	{
		game->player.pos_z += Z_ACCELLERATION * game->deltatime;
		if (game->player.pos_z >= JUMP_LIMIT)
		{
			game->player.pos_z = JUMP_LIMIT;
			game->move.jump_mult = -1;
		}
	}

	if (game->move.jump && game->move.jump_mult == -1)
	{
		game->player.pos_z -= Z_ACCELLERATION * game->deltatime;
		if (game->player.pos_z <= 0)
		{
			game->player.pos_z = 0;
			game->move.jump_mult = 0;
			game->move.jump = false;
		}
	}
	if (game->move.crouch && !game->move.has_crouched)
	{
		game->player.head_pos_z = -CROUCH_HEIGHT;
		game->move.has_crouched = true;
	}
	if (!game->move.crouch && game->move.has_crouched)
	{
		game->player.head_pos_z = 0;
		game->move.has_crouched = false;
	}
}
