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

void handle_player_movement(t_var *game)
{
	double new_x;
	double new_y;


    //TODO non sto gestendo bene la posizione del player, le sue x e y devono essere
    //scalate x 64 all se si parla della sua posizione(pixel)
	if (game->move.up) 
    {
        new_y = game->player.y - VELOCITY;
        if (!handle_wll_collision(game, game->player.x, new_y - SAFETY_WALL_DIST)) 
            game->player.y = new_y;
    }
    if (game->move.down)
    {
        new_y = game->player.y + VELOCITY;
        if (!handle_wll_collision(game, game->player.x, new_y + SAFETY_WALL_DIST)) 
            game->player.y = new_y;
    }
    if (game->move.left)
    {
        new_x = game->player.x - VELOCITY;
        if (!handle_wll_collision(game, new_x - SAFETY_WALL_DIST, game->player.y )) 
            game->player.x = new_x;
    }
    if (game->move.right) 
    {
        new_x = game->player.x + VELOCITY;
        if (!handle_wll_collision(game, new_x + SAFETY_WALL_DIST, game->player.y))
            game->player.x = new_x;
    }
}

#define CAMERA_HIGH_LIMIT 100
#define CAMERA_LOW_LIMIT -100
#define JUMP_LIMIT 400
#define CROUCH_HEIGHT 200

void handle_player_rotation(t_var *game)
{
    float value;

	if (game->move.rot_left)
         handle_camera_rotation(game , ROTAT_DIR_LEFT);
    if (game->move.rot_right)
        handle_camera_rotation(game , ROTAT_DIR_RIGHT);
    
    
    if (game->move.rot_up)
    {
        game->player.offset += 15 * VELOCITY;
        if(game->player.offset > CAMERA_HIGH_LIMIT)
            game->player.offset = CAMERA_HIGH_LIMIT;
    }
    if (game->move.rot_down)
    {
        game->player.offset -= 15 * VELOCITY;
        if( game->player.offset < CAMERA_LOW_LIMIT) 
            game->player.offset = CAMERA_LOW_LIMIT;
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
    //pos z per il momento e' sempre zero 
    // serve a gestire la posizione del player sull asse z
    //devo solo implementare il keyhook a questo punto
    if(game->move.jump && game->move.jump_mult == 1)
    {
        game->player.pos_z += Z_ACCELLERATION * game->deltatime;
        if(game->player.pos_z >= JUMP_LIMIT)
        {
            game->player.pos_z = JUMP_LIMIT;
            game->move.jump_mult = -1;
        }
        
    }

    if(game->move.jump && game->move.jump_mult == -1)
    {
        game->player.pos_z -= Z_ACCELLERATION * game->deltatime;
        if(game->player.pos_z <= 0)
        {
            game->player.pos_z = 0;
            game->move.jump_mult = 0;
            game->move.jump = false;
        } 
    }
    if(game->move.crouch && !game->move.has_crouched)
    {
        game->player.pos_z -=  CROUCH_HEIGHT;
        game->move.has_crouched = true;
    }
    if (!game->move.crouch && game->move.has_crouched)
    {
        game->player.pos_z +=  CROUCH_HEIGHT;
        game->move.has_crouched = false;
    }
}
