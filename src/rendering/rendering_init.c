#include <libft.h>
#include "cub3D.h"

void copy_dpos(t_dpoint *p1, t_dpoint p2)
{
	p1->x = p2.x;
	p1->y = p2.y;
}

void copy_pos(t_point *p1, t_point p2)
{
	p1->x = p2.x;
	p1->y = p2.y;
}

void add_dpoint(t_dpoint *p1, t_dpoint p2)
{
	p1->x += p2.x;
	p1->y += p2.y;
}

static void calc_initial_step_and_intial_raylen(t_var *game)
{
	const t_dpoint ray = (t_dpoint){(game->player.x_px / 64 - game->dda.map_coords.x) * game->dda.delta_dist.x, 0};
	const t_dpoint ray1 = (t_dpoint){(game->dda.map_coords.x + 1.0 - game->player.x_px / 64) * game->dda.delta_dist.x, 0};
	t_dpoint ray2;
	t_dpoint ray3;

	if (game->dda.dir.x < 0)
	{
		game->dda.step_x = -1;
		copy_dpos(&game->dda.ray, ray);
	}
	else
	{
		game->dda.step_x = 1;
		copy_dpos(&game->dda.ray, ray1);
	}
	ray2 = (t_dpoint){game->dda.ray.x,(game->player.y_px / 64 - game->dda.map_coords.y) * game->dda.delta_dist.y};
	ray3 = (t_dpoint){game->dda.ray.x, (game->dda.map_coords.y + 1.0 - game->player.y_px / 64) * game->dda.delta_dist.y};
	if (game->dda.dir.y < 0)
	{
		game->dda.step_y = -1;
		copy_dpos(&game->dda.ray, ray2);
	}
	else
	{
		game->dda.step_y = 1;
		copy_dpos(&game->dda.ray, ray3);
	}
}


void init_rendering(t_var *game, int pixel_pos_x)
{
	const t_point playerPos = (t_point){(int)game->player.x_px / 64, (int)game->player.y_px / 64};
	const double dirx = game->player.dir_y + game->plane.x * game->dda.camera_x;
	const double diry = game->player.dir_x + game->plane.y * game->dda.camera_x;
	const t_dpoint dirVect = (t_dpoint){ dirx, diry };
	const t_dpoint dDistVect = (t_dpoint){fabs(1 / game->dda.dir.x), fabs(1 / game->dda.dir.y)};
	
	
	copy_pos(&game->dda.map_coords, playerPos);
	game->dda.camera_x = (double)(2 * pixel_pos_x) / (double)game->dda.screen_size_w_px - 1;
	copy_dpos(&game->dda.dir, dirVect);
	copy_dpos(&game->dda.delta_dist, dDistVect);
	
	calc_initial_step_and_intial_raylen(game);
}