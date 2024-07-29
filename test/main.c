#include <libft.h>
#include "cub3D.h"

#define TEXTURE_SIZE 32
#define TEXTURE_HALF_SIZE 16

#define N 78
#define W 87
#define E 69
#define S 83

#define FLOOR 0
#define WALL 1

typedef struct s_playerPos
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
} t_playerPos;

typedef struct s_DDA
{
	double cameraX;
	double rayDirX;
	double rayDirY;
	double screenSize;

	double sideDistX;
	double sideDistY;
	double pixelPosX;
	double deltaDistX;
	double deltaDistY;

	int stepX;
	int stepY;
	int mapX;
	int mapY;

} t_DDA;

// "GLOBAL" program's structure.
typedef struct s_var
{
	struct s_playerPos *playerPos;
	struct s_DDA dda_helper;
	int **mtxint;
	int intMtxRows;
	int intMtxCols;
	double planeX;
	double planeY;
	void *mlx_ptr;
	void *win_ptr;
} t_var;

int **cmtxtoimtx(char **mtx, int col, int row)
{
	int **intMtx;
	int counterRow;
	int counterCol;

	intMtx = ft_calloc(row, sizeof(int *));
	if (!intMtx)
		return NULL;
	counterRow = 0;
	counterCol = 0;
	while (counterRow < row)
	{
		intMtx[counterRow] = ft_calloc(col, sizeof(int));
		counterCol = 0;
		while (counterCol < col)
		{
			intMtx[counterRow][counterCol] = mtx[counterRow][counterCol] - '0';
			dbg_printf("intMtx[counterRow][counterCol] == %d\n", intMtx[counterRow][counterCol]);
			counterCol++;
		}
		counterRow++;
	}
	return intMtx;
}

t_playerPos *getPlayerPos(int **mtx, int col, int row)
{
	int counterRow;
	int counterCol;
	t_playerPos *pos;

	counterRow = 0;
	counterCol = 0;
	pos = ft_calloc(1, sizeof(t_playerPos));
	if (!pos)
	{
		/*https://www.youtube.com/watch?v=wLg04uu2j2o*/
		return NULL;
	}
	while (counterRow < row)
	{
		counterCol = 0;
		while (counterCol < col)
		{
			if (mtx[counterRow][counterCol] != FLOOR && mtx[counterRow][counterCol] != WALL)
			{
				/*
				bisogna controllare quale sia il carattere presente
				e settare la player direction accordingly
				pos->dir_x
				pos->dir_y
				*/
				pos->pos_x = (counterCol * TEXTURE_SIZE) + TEXTURE_HALF_SIZE;
				pos->pos_y = (counterRow * TEXTURE_SIZE) + TEXTURE_HALF_SIZE;
				return pos;
			}
			counterCol++;
		}
		counterRow++;
	}
	return NULL;
}

void draw_square(t_var *infos, int y, int x, int color)
{
	int origX = x;
	int counterRows;
	int counterCols;

	counterRows = 0;

	while (counterRows < 32)
	{
		counterCols = 0;
		x = origX;
		while (counterCols < 32)
		{
			mlx_pixel_put(infos->mlx_ptr, infos->win_ptr, x, y, color);
			x++;
			counterCols++;
		}
		y++;
		counterRows++;
	}
}

void draw_map(t_var *infos)
{
	int row;
	int cols;
	int color;

	row = 0;
	cols = 0;
	while (row < infos->intMtxRows)
	{
		cols = 0;
		while (cols < infos->intMtxCols)
		{
			color = (int[2]){0xFFFFFF, 0x000000}[infos->mtxint[row][cols] != 1];
			draw_square(infos, row * TEXTURE_SIZE, cols * TEXTURE_SIZE, color);
			cols++;
		}
		row++;
	}
}

void calc_initial_step_intial_raylen(t_var *infos)
{
	if (infos->dda_helper.rayDirX < 0)
	{
		infos->dda_helper.stepX = -1;
		infos->dda_helper.sideDistX = (infos->planeX - infos->dda_helper.mapX) * infos->dda_helper.deltaDistX;
	}
	else
	{
		infos->dda_helper.stepX = 1;
		infos->dda_helper.sideDistX = (infos->dda_helper.mapX + 1.0 - infos->planeX) * infos->dda_helper.deltaDistX;
	}
	if (infos->dda_helper.rayDirY < 0)
	{
		infos->dda_helper.stepY = -1;
		infos->dda_helper.sideDistY = (infos->planeY - infos->dda_helper.mapY) * infos->dda_helper.deltaDistY;
	}
	else
	{
		infos->dda_helper.stepY = 1;
		infos->dda_helper.sideDistY = (infos->dda_helper.mapY + 1.0 - infos->planeY) * infos->dda_helper.deltaDistY;
	}
}

void calculate_DDA(t_var *infos)
{
	infos->dda_helper = (t_DDA){0};
	infos->dda_helper.screenSize = infos->intMtxCols * 32;
	infos->dda_helper.mapX = (int)infos->playerPos->pos_x;	   // quadrato della mappa in cui ci troviamo
	infos->dda_helper.mapY = (int)infos->playerPos->pos_y; // quadrato della mappa in cui ci troviamo
	int pixelPosX = 0;
	while (pixelPosX < infos->dda_helper.screenSize)
	{
		// cameraX is the x-coordinate on the camera plane that the current x-coordinate of the screen represents, done this way so that
		// the right side of the screen will get coordinate 1, the center of the screen gets coordinate 0, and the left side of the screen gets coordinate -1.
		infos->dda_helper.cameraX = 2 * pixelPosX / infos->dda_helper.screenSize - 1;
		// direction of the ray
		infos->dda_helper.rayDirX = infos->planeX + infos->planeX * infos->dda_helper.cameraX;
		infos->dda_helper.rayDirY = infos->planeY + infos->planeY * infos->dda_helper.cameraX;

		// lunghezza da percorrere lungo il per spostarsi di 1 sull asse x e y, poi verranno confrontati per decidere dove
		// fare il prossimo passo ("StepX/StepY")
		infos->dda_helper.deltaDistX = (float[2]){1e30, fabs(1 / infos->dda_helper.rayDirX)}[infos->dda_helper.rayDirX == 1];
		infos->dda_helper.deltaDistY = (float[2]){1e30, fabs(1 / infos->dda_helper.rayDirY)}[infos->dda_helper.rayDirY == 1];

		calc_initial_step_intial_raylen(infos);

		// fino a questo punto ho ottenuto solo la prima length del raggio di mio interesse
		// adesso deve partire un loop che andra ad aggiungere una certa len al nostro ray.
		// il loop si ferma quando colpiamo un blocco

		pixelPosX++;
	}
}

int main()
{
	struct s_var infos;
	char **mtx;
	int fd;

	infos = (struct s_var){0};
	// apro il file
	fd = open("../maps/mappa.txt", O_RDONLY);
	if (fd < 0)
		perror("Path to map file is incorrect!\n");
	mtx = ft_readfile(fd, false);

	// prendo n cols & n rows
	infos.intMtxRows = str_mtxlen(mtx);
	infos.intMtxCols = str_ilen(mtx[0]);
	infos.mtxint = cmtxtoimtx(mtx, infos.intMtxCols, infos.intMtxRows);

	// prendo player pos e assegno direz hardcoded
	infos.playerPos = getPlayerPos(infos.mtxint, infos.intMtxCols, infos.intMtxRows);
	if (!infos.playerPos)
		ft_perror("No player found in the map provided!");
	dbg_printf("Player Position[x]: %f\nPlayer Position[y]: %f\n", infos.playerPos->pos_x, infos.playerPos->pos_y);

	infos.playerPos->dir_x = 0;
	infos.playerPos->dir_y = 1;

	//					the length of the direction
	// FOV = ratio of  --------------------------------
	// 					    the camera plane

	infos.planeX = 0.0;	 // sul piano x non c' e alcun offset
	infos.planeY = 0.66; // offset di 0.66unita sull asse delle Y

	infos.mlx_ptr = mlx_init();
	infos.win_ptr = mlx_new_window(infos.mlx_ptr, infos.intMtxCols * 32, infos.intMtxRows * 32, "UrMom");
	// game loop

	//"minimappa"
	draw_map(&infos);

	calculate_DDA(&infos);
	// player position
	mlx_pixel_put(infos.mlx_ptr, infos.win_ptr, infos.playerPos->pos_x, infos.playerPos->pos_y, 0xFF0000);
	mlx_hook(infos.win_ptr, 17, 0, mlx_loop_end, infos.mlx_ptr);
	mlx_loop(infos.mlx_ptr);
}