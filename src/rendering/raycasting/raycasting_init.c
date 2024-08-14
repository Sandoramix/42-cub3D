#include <libft.h>
#include "cub3D.h"

void	calc_direction(t_var *game)
{
	const double	x_axispos = (game->player.x
			- game->engine.map_coords.x) * game->engine.delta_dist.x;
	const double	x_axisneg =	(-game->player.x
			+ game->engine.map_coords.x + 1.0) * game->engine.delta_dist.x;
	double			y_axispos;
	double			y_axisneg;
	t_dpoint		direction;

	if (game->engine.dir.x < 0)
		game->engine.step_x = -1;
	else
		game->engine.step_x = 1;
	if (game->engine.dir.y < 0)
		game->engine.step_y = -1;
	else
		game->engine.step_y = 1;
	y_axispos = ((game->player.y) - game->engine.map_coords.y)
		* game->engine.delta_dist.y;
	y_axisneg = ((-game->player.y) + game->engine.map_coords.y + 1.0) * game->engine.delta_dist.y;
	direction.x = (double [2]){x_axispos, x_axisneg}[game->engine.dir.x > 0];
	direction.y = (double [2]){y_axispos, y_axisneg}[game->engine.dir.y > 0];
	copy_dpos(&game->engine.ray, direction);
}


void	init_vars(t_var *game, int x)
{
	const t_point	pl_vector = (t_point){(int)game->player.x, game->player.y};
	const double camera_x = (double)(2.0 * x) / (double)game->config.win_width - 1;
	const double	raydirx = game->player.dir_x + game->engine.plane.x
		* camera_x;
	const double	raydiry = game->player.dir_y + game->engine.plane.y
		* camera_x;
	const t_dpoint	ray_dir_vect = (t_dpoint){raydirx, raydiry};

	t_dpoint	delta_dist_vect;
	if (game->engine.dir.x == 0)
		delta_dist_vect.x = 1e30;
	else
		delta_dist_vect.x = fabs(1.0 / game->engine.dir.x);
	if (game->engine.dir.y == 0)
		delta_dist_vect.y = 1e30;
	else
		delta_dist_vect.y = fabs(1.0 / game->engine.dir.y);
	copy_pos(&game->engine.map_coords, pl_vector);
	copy_dpos(&game->engine.dir, ray_dir_vect);
	copy_dpos(&game->engine.delta_dist, delta_dist_vect);
}
