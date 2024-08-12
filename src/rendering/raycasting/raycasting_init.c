#include <libft.h>
#include "cub3D.h"

void	calc_direction(t_var *game)
{
	const double	x_axispos = (game->player.x_px / (double)TILE_SIZE
			- game->engine.map_coords.x) * game->engine.delta_dist.x;
	const double	x_axisneg =	(-game->player.x_px / (double)TILE_SIZE
			+ game->engine.map_coords.x + 1.0) * game->engine.delta_dist.x;
	double			y_axispos;
	double			y_axisneg;
	t_dpoint		direction;

	if (game->engine.dir.x < 0)
		game->engine.step_x = -1;
	else
		game->engine.step_x = 1;
	direction.x = (double [2]){x_axispos, x_axisneg}[game->engine.dir.x > 0];
	y_axispos = ((game->player.y_px / (double)TILE_SIZE) - game->engine.map_coords.y)
		* game->engine.delta_dist.y;
	y_axisneg = ((-game->player.y_px / (double)TILE_SIZE) + game->engine.map_coords.y + 1.0) * game->engine.delta_dist.y;
	if (game->engine.dir.y < 0)
		game->engine.step_y = -1;
	else
		game->engine.step_y = 1;
	direction.y = (double [2])
	{y_axispos, y_axisneg}[game->engine.dir.y > 0];
	copy_dpos(&game->engine.ray, direction);
}


void	init_vars(t_var *game, int x)
{
	const t_point	pl_vector = (t_point){(int)game->player.x_px / (double)TILE_SIZE, game->player.y_px / (double)TILE_SIZE};
	const double	raydirx = game->player.dir_x + game->engine.plane.x
		* game->engine.camera_x;
	const double	raydiry = game->player.dir_y + game->engine.plane.y
		* game->engine.camera_x;
	const t_dpoint	ray_dir_vect = (t_dpoint){raydirx, raydiry};
	const t_dpoint	delta_dist_vect = (t_dpoint){fabs(1.0 / game->engine.dir.x),
		fabs(1.0 / game->engine.dir.y)};

	copy_pos(&game->engine.map_coords, pl_vector);
	game->engine.camera_x = (double)(2.0 * x)
		/ (double)game->config.win_width - 1;
	copy_dpos(&game->engine.dir, ray_dir_vect);
	copy_dpos(&game->engine.delta_dist, delta_dist_vect);
}
