#ifndef CUB3D_H
# define CUB3D_H

#include <libft.h>
#include <mlx.h>
#include <mlx_int.h>


//Player position structure

typedef struct s_playerPos{
    float x;
    float y;
} t_playerPos;


// "GLOBAL" program's structure.
struct s_var
{
   struct s_playerPos *playerPos;
} t_varr;





#endif
