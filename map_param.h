#ifndef MAP_H
# define MAP_H

#include "stdlib.h"

typedef struct	map_param
{
	int		width;
	int		height;
	int		max_sq_size;
	char	empt_symb;
	char	obst_symb;
	char	fill_symb;
}				mp;

#endif
