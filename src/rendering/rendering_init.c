#include <libft.h>
#include "cub3D.h"

static void copy_dpos(t_dpoint *p1, t_dpoint p2)
{
	p1->x = p2.x;
	p1->y = p2.y;
}

static void copy_pos(t_point *p1, t_point p2)
{
	p1->x = p2.x;
	p1->y = p2.y;
}

/* static void add_dpoint(t_dpoint *p1, t_dpoint p2)
{
	p1->x += p2.x;
	p1->y += p2.y;
} */

static void calc_initial_step_and_intial_raylen(t_var *game)
{
	const t_dpoint init_ray = (t_dpoint){(game->player.x_px / 64 - game->raycasting.map_coords.x) * game->raycasting.delta_dist.x, 0};
	const t_dpoint init_ray1 = (t_dpoint){(- game->player.x_px / 64 + game->raycasting.map_coords.x + 1.0 ) * game->raycasting.delta_dist.x, 0};
	t_dpoint init_ray2;
	t_dpoint init_ray3;

	if (game->raycasting.dir.x < 0)
		game->raycasting.step_x = -1;
	else
		game->raycasting.step_x = 1;
	//muove 
	copy_dpos(&game->raycasting.ray, (t_dpoint[2]){init_ray, init_ray1}[game->raycasting.dir.x > 0]);
	init_ray2 = (t_dpoint){game->raycasting.ray.x,(game->player.y_px / 64 - game->raycasting.map_coords.y) * game->raycasting.delta_dist.y};
	init_ray3 = (t_dpoint){game->raycasting.ray.x, ( - game->player.y_px / 64 + game->raycasting.map_coords.y + 1.0) * game->raycasting.delta_dist.y};
	if (game->raycasting.dir.y < 0)
		game->raycasting.step_y = -1;
	else
		game->raycasting.step_y = 1;
	copy_dpos(&game->raycasting.ray, (t_dpoint[2]){init_ray2, init_ray3}[game->raycasting.dir.y > 0]);

}


void init_rendering(t_var *game, int pixel_pos_x)
{
	const t_point player_pos_vect = (t_point){(int)game->player.x_px / 64, (int)game->player.y_px / 64};
	const double dirx = game->player.dir_y + game->plane.x * game->raycasting.camera_x;
	const double diry = game->player.dir_x + game->plane.y * game->raycasting.camera_x;
	const t_dpoint ray_dir_vect = (t_dpoint){ dirx, diry };
	const t_dpoint delta_dist_vect = (t_dpoint){fabs(1 / game->raycasting.dir.x), fabs(1 / game->raycasting.dir.y)};
	
	copy_pos(&game->raycasting.map_coords, player_pos_vect);
	game->raycasting.camera_x = (double)(2 * pixel_pos_x) / (double)game->config._w - 1;
	copy_dpos(&game->raycasting.dir, ray_dir_vect);
	copy_dpos(&game->raycasting.delta_dist, delta_dist_vect);
	
	calc_initial_step_and_intial_raylen(game);
}