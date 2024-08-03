#include <cub3D.h>



void handle_camera_rotation(t_var *game, int rotation_dir)
{
	double old_dir_x;
	double old_plane_x;
    double rotSpeed = 0.035;

	if (rotation_dir == ROTAT_DIR_RIGHT)
	{
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-rotSpeed) - game->player.dir_y * sin(-rotSpeed); 
		game->player.dir_y = old_dir_x *sin(-rotSpeed) + game->player.dir_y * cos(-rotSpeed);
		old_plane_x = game->plane.x;
		game->plane.x = game->plane.x  * cos(-rotSpeed) - game->plane.y * sin(-rotSpeed);
		game->plane.y = old_plane_x * sin(-rotSpeed) + game->plane.y * cos(-rotSpeed); 
	}
	else
	{
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(rotSpeed) - game->player.dir_y * sin(rotSpeed); 
		game->player.dir_y = old_dir_x * sin(rotSpeed) + game->player.dir_y * cos(rotSpeed);
		old_plane_x = game->plane.x;
		game->plane.x = game->plane.x  * cos(rotSpeed) - game->plane.y *  sin(rotSpeed);
		game->plane.y = old_plane_x *  sin(rotSpeed) + game->plane.y * cos(rotSpeed); 
	}

}

int handle_wll_collision(t_var *game, double x, double y)
{
    if (x < 0 || x >= game->mapinfo.cols_mtx || y < 0
		|| y >= game->mapinfo.rows_mtx || game->mapinfo.mtxint[(int)x][(int)y] == 1)
        return (OK);
    printf("Can t move, the player position will be :%f %f\n", x, y);
    return (KO);
}

void handle_player_movement(t_var *game, int keycode)
{
	double new_x;
	double new_y;


    //TODO non sto gestendo bene la posizione del player, le sue x e y devono essere
    //scalate x 64 all se si parla della sua posizione(pixel)
	if (keycode == KEY_W) 
    {
        new_y = game->player.y - VELOCITY;
        if (!handle_wll_collision(game, game->player.x, new_y - SAFETY_WALL_DIST)) 
            game->player.y = new_y;
    }
    if (keycode == KEY_S)
    {
        new_y = game->player.y + VELOCITY;
        if (!handle_wll_collision(game, game->player.x, new_y + SAFETY_WALL_DIST)) 
            game->player.y = new_y;
    }
    if (keycode == KEY_A) 
    {
        new_x = game->player.x - VELOCITY;
        if (!handle_wll_collision(game, new_x - SAFETY_WALL_DIST, game->player.y )) 
            game->player.x = new_x;
    }
    if (keycode == KEY_D) 
    {
        new_x = game->player.x + VELOCITY;
        if (!handle_wll_collision(game, new_x + SAFETY_WALL_DIST, game->player.y))
            game->player.x = new_x;
    }
}

void handle_player_rotation(t_var *game, int keycode)
{
    float value;

	if (keycode == XK_Left)
         handle_camera_rotation(game , ROTAT_DIR_LEFT);
    if (keycode == XK_Right)
        handle_camera_rotation(game , ROTAT_DIR_RIGHT);
    
    
    
    
    if (keycode == XK_Up)
    {
        game->player.offset += 15 * VELOCITY;
        if(game->player.offset > 100)
            game->player.offset = 100;
    }
    if (keycode == XK_Down)
    {
        game->player.offset -= 15 * VELOCITY;
        if( game->player.offset < -100) 
            game->player.offset = -100;
    }
    if(game->player.offset  > 0)
    {
        value = game->player.offset * 0.9f;
        game->player.offset  = (float[2]){0, value}[0.1f < value];
    } 
    if(game->player.offset  < 0)
    {
        value = game->player.offset  * 0.9f;
        game->player.offset  = (float[2]){0, value}[-0.1f > value];
    } 
    if(game->player.pos_z  > 0)
    {
        value = game->player.pos_z  - 50 * VELOCITY;
        game->player.pos_z  = (float[2]){0, value}[0.1f < value];
    } 
    if(game->player.pos_z  < 0)
    {
        value = game->player.pos_z  + 50 * VELOCITY;
        game->player.pos_z  = (float[2]){0, value}[-0.1f > value];
    } 
}
