
#include "includes/cub3D.h"

#define TEXTURE_SIZE 32
#define TEXTURE_HALF_SIZE 32

#define N 78
#define W 87
#define E 69
#define S 83

#define FLOOR 0
#define WALL 1


int **fromCharMtxtoIntMtx(char **mtx, int col, int row)
{
	int **intMtx;
	int counterRow;
	int counterCol;

	intMtx = ft_calloc(row, sizeof(int *));
	if (!intMtx)
		return NULL;
	counterRow = 0;
	counterCol = 0;
	while(counterRow < row)
	{
		intMtx[counterRow] = ft_calloc(col, sizeof(int));
		counterCol = 0;
		while(counterCol < col)
		{
			/*https://www.youtube.com/watch?v=wLg04uu2j2o*/
			if (mtx[counterRow][counterCol] == '\n' || mtx[counterRow][counterCol] == '\0')
			{
				counterCol++;	
				continue;
			}
			intMtx[counterRow][counterCol] = (float)mtx[counterRow][counterCol] - '0';
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
	while(counterRow < row)
	{
		counterCol = 0;
		while(counterCol < col)
		{
			if (mtx[counterRow][counterCol] != FLOOR && mtx[counterRow][counterCol] != WALL)
			{
				pos->x = (counterCol * TEXTURE_SIZE) + TEXTURE_HALF_SIZE;
				pos->y = (counterRow * TEXTURE_SIZE) + TEXTURE_HALF_SIZE;
				return pos;
			}
			counterCol++;
		}
		counterRow++;
	}
	return NULL;
}


int	main()
{
	char **mtx;
	int	**intMtx; 
	int intMtxRows;
	int intMtxCols;
	int fd;
	struct s_var infos;

	infos = (struct s_var){0};
	fd = open("maps/mappa.txt", O_RDONLY);
	mtx = ft_readfile(fd, true);


	intMtxRows = str_mtxlen(mtx);
	intMtxCols = str_ilen(mtx[0]);
	
	intMtx = fromCharMtxtoIntMtx(mtx, intMtxCols, intMtxRows);
	infos.playerPos = getPlayerPos(intMtx, intMtxCols, intMtxRows);
	
	if (!infos.playerPos)
		ft_perror("No player found in the map provided!");
	dbg_printf("Player Position[x]: %f\nPlayer Position[y]: %f\n", infos.playerPos->x, infos.playerPos->y);

	



















}