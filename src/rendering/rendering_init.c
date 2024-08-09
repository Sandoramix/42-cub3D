#include <libft.h>
#include "cub3D.h"

static void calc_initial_step_and_intial_raylen(t_var *game)
{
	const t_dpoint init_ray = (t_dpoint){(game->player.x_px / 64.0 - game->engine.map_coords.x) * game->engine.delta_dist.x, 0};
	const t_dpoint init_ray1 = (t_dpoint){(- game->player.x_px / 64.0 + game->engine.map_coords.x + 1.0 ) * game->engine.delta_dist.x, 0};
	t_dpoint init_ray2;
	t_dpoint init_ray3;

	if (game->engine.dir.x < 0)
		game->engine.step_x = -1;
	else
		game->engine.step_x = 1;
	copy_dpos(&game->engine.ray, (t_dpoint[2]){init_ray, init_ray1}[game->engine.dir.x > 0]);
	init_ray2 = (t_dpoint){game->engine.ray.x, ((game->player.y_px / 64.0) - game->engine.map_coords.y) * game->engine.delta_dist.y};
	init_ray3 = (t_dpoint){game->engine.ray.x, ((-game->player.y_px / 64.0) + game->engine.map_coords.y + 1.0) * game->engine.delta_dist.y};
	if (game->engine.dir.y < 0)
		game->engine.step_y = -1;
	else
		game->engine.step_y = 1;
	copy_dpos(&game->engine.ray, (t_dpoint[2]){init_ray2, init_ray3}[game->engine.dir.y > 0]);
}


void init_rendering(t_var *game, int pixel_pos_x)
{
	const t_point player_pos_vect = (t_point){(int)floor(game->player.x_px / 64.0), (int)floor(game->player.y_px / 64.0)};
	const double dirx = game->player.dir_y + game->engine.plane.x * game->engine.camera_x;
	const double diry = game->player.dir_x + game->engine.plane.y * game->engine.camera_x;
	const t_dpoint ray_dir_vect = (t_dpoint){dirx, diry};
	const t_dpoint delta_dist_vect = (t_dpoint){fabs(1.0 / game->engine.dir.x), fabs(1.0 / game->engine.dir.y)};
	copy_pos(&game->engine.map_coords, player_pos_vect);
	game->engine.camera_x = (double)(2.0 * pixel_pos_x) / (double)game->config.win_width - 1;
	copy_dpos(&game->engine.dir, ray_dir_vect);
	copy_dpos(&game->engine.delta_dist, delta_dist_vect);
	calc_initial_step_and_intial_raylen(game);
}
