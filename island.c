#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stddef.h>
#include<time.h>

#define LAND (1)
#define WATER (0)
#define CHECKED (1)
#define UN_CHECKED (0)
#define HIGH (4)
#define LENGTH (5)

typedef struct dot
{
	int land_or_water;
	int checked;
} t_dot;

t_dot map[HIGH][LENGTH];


void printf_map(t_dot (*map)[LENGTH], int high, int length)
{
	int i = 0, j = 0;
	for(i = 0 ; i < high ; i++ )
	{
		for(j = 0 ; j < length ; j++ )
		{
			printf("%d ", (*(map+i)+j)->land_or_water );
			//printf("%d ", map[i][j].land_or_water );
		}
		printf("\n");
	}
}

void init_map(t_dot map[][LENGTH], int high, int length)
{
#define BY_RANDOM
	int i = 0, j = 0;
	int random = 0;
	for(i = 0 ; i < high ; i++ )
	{
		for(j = 0 ; j < length ; j++ )
		{
			map[i][j].land_or_water = LAND;
			map[i][j].checked = UN_CHECKED;
		}
	}
#ifdef BY_RANDOM
	srand((unsigned)time(NULL));//选取种子文件
	for(i = 0 ; i < high ; i++ )
	{
		for(j = 0 ; j < length ; j++ )
		{
			random = (rand() % 2);
			if(random == 1) 
				map[i][j].land_or_water = LAND;
			else if(random == 0) 
				map[i][j].land_or_water = WATER;
		}
	}
#endif
	
}

int check_single_dot(t_dot (*map)[LENGTH], int line, int column)
{
	int result = UN_CHECKED;
	
	if( map[line][column].checked == CHECKED ) result = CHECKED;
	else result = UN_CHECKED;

	return result;
}

void check_dots(t_dot (*map)[LENGTH], int line, int column, int layer, int *island)
{
	if( line < 0 || line > HIGH - 1 || column < 0 || column > LENGTH - 1 || map[line][column].checked == CHECKED)
	{
		return ;
	}
	if( map[line][column].checked == CHECKED )
	{
		printf("map[%d][%d] is %d \n;", line, column, map[line][column].checked );
		return ;
	}
	
	map[line][column].checked = CHECKED;

	if( map[line][column].land_or_water == LAND )
	{
		if( layer == 0 )
		{
			(*island) ++;
		}
		
		check_dots( map, line, column - 1, layer + 1, island);
		check_dots( map, line + 1, column, layer + 1, island);
		check_dots( map, line, column + 1, layer + 1, island);
		check_dots( map, line - 1, column, layer + 1, island);
	}
	
	
}

void check_island(t_dot (*map)[LENGTH], int high, int length)
{
	int i = 0, j = 0;
	int island = 0;
	int *p_island = &island;
	for(i = 0 ; i < high ; i++ )
	{
		for(j = 0 ; j < length ; j++ )
		{
			//if(check_single_dot( map, i, j) == UN_CHECKED)
				check_dots(map, i, j, 0, p_island);
		}
	}
	printf("island is %d \n", island );
}

int main()
{
	init_map(map, HIGH, LENGTH);
	printf_map(map, HIGH, LENGTH);
	check_island( map, HIGH, LENGTH);
		
	return 0;
}