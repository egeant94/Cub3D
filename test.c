#include <stdio.h>
#include <stdlib.h>

int		main(void)
{
	int		**map;
	int		i;
	map =  {
			{1, 1, 1, 1, 1, 1},
			{1, 0, 0, 0, 0, 1},
			{1, 0, 1, 0, 0, 1},
			{1, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 1},
			{1, 1, 1, 1, 1, 1}};
	printf("%d\n", map[2][2]);
}