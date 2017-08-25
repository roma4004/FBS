#include "sq_coord.h"
#include "map_param.h"

void	sq_set(sq *square, int y, int x, int size)
{
	printf("\nsq_set in: y = %d, x = %d, size: %d", y, x, size);
	if (y != -1)
		square->y = y;
	if (x != -1)
		square->x = x;
	if (size != -1)
		square->size = size;
	printf("\nsq_set sq: y = %d, x = %d, size: %d", square->y, square->x, square->size);

}

int		is_sq_empty(char **argv, sq *used_sq, mp *map)
{
	int y;
	int x;

	y = used_sq->y;
	x = used_sq->x;
	while (y < used_sq->size)
	{
		while (x < used_sq->size)
		{
			if (argv[y][x] != map->empt_symb)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int		len_of(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		fill_sq(char **argv, sq *save_sq, char fill_symb) //if (sq_size == 0) //err_handler(1); //show alert min placed sq not found
{
	int y;
	int x;

	y = save_sq->y;
	x = save_sq->x;
	while (y < save_sq->size)
	{
		while (x < save_sq->size)
		{                                  						printf("\ncoord: y = %d, x = %d, %c = %c, used-size: %d", y, x, argv[y][x], fill_symb, save_sq->size);
			argv[y][x] = fill_symb;
			x++;
		}
		y++;
	}
	return (1);
}

void	check_sq(char **argv, sq *used_sq, sq *save_sq, mp *map)
{
	if (is_sq_empty(argv, used_sq, map)
			&& save_sq->size < used_sq->size)
	{
		sq_set(save_sq, used_sq->y, used_sq->x, used_sq->size);
		printf(" save to placed x %d, y %d, size %d", save_sq->x, save_sq->y, save_sq->size);
	//	used_sq->x = 0;
		sq_set(used_sq, -1, -1, used_sq->size + 1);
	}
	else
		sq_set(used_sq, -1, used_sq->x + 1, -1);
}

void	check_sq_on_x(char **argv, sq *used_sq, sq *save_sq, mp *map)
{
	while (used_sq->x + used_sq->size < map->width
		   	&& used_sq->size < map->max_sq_size)	
		check_sq(argv, used_sq, save_sq, map);
	printf("\ncheck_sq_on_x: y =  %d, x = %d, actual->size = %d", used_sq->y, used_sq->x, used_sq->size);
}

void	check_sq_on_y(char **argv, sq *used_sq, sq *save_sq, mp *map)
{
	while (used_sq->y + used_sq->size < map->height
			&& used_sq->size < map->max_sq_size)
	{
		check_sq_on_x(argv, used_sq, save_sq, map);				printf("\ncheck_sq_on_y: y =  %d, actual->size = %d", used_sq->y, used_sq->size);
		if (used_sq->x + used_sq->size == map->width)
			sq_set(used_sq, used_sq->y + 1, 0, -1);
	}
}

int		get_min_of(int width, int height)
{
	if (width < height)
		return (width);
	return (height);
}

int		check_row(char **argv, int y, int sq_size)
{
	int i;

	i = 0; 
	while (argv[y][i] && i < sq_size)
	{
		if (argv[y][i] != '.')
			return (0);
		i++;
	}
	return (1);
}

int		check_col(char **argv, int x, int sq_size, char empt_symb)
{
	int i;

	i = 1;
	while (argv[i] && i < sq_size)
	{
		if (argv[i][x] != empt_symb)
			return (0);
		i++;
	}
	return (1);
}

void	show_map(char **argv)
{
	int y;

	y = 1;
	while (argv[y])
	{
		write(1, argv[y], len_of(argv[y]));
		write(1, "\n", 1);
		y++;
	}
}

void	str_cpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
}

int		main(int argc, char **argv_def)
{
	int x;
	int y;

	sq used_sq;
	sq save_sq;
	mp map;

	map.height = 10;
	map.width = 27;
	map.fill_symb = 'X';
	map.empt_symb = '.';
	map.obst_symb = 'o';

	char **argv;
	argv    = (char **)malloc(sizeof(char*) * 10 + 1);
	argv[0] = (char * )malloc(sizeof(char ) *  4 + 1);
	argv[1] = (char * )malloc(sizeof(char ) * 27 + 1);
	argv[2] = (char * )malloc(sizeof(char ) * 27 + 1);
	argv[3] = (char * )malloc(sizeof(char ) * 27 + 1);
	argv[4] = (char * )malloc(sizeof(char ) * 27 + 1);
	argv[5] = (char * )malloc(sizeof(char ) * 27 + 1);
	argv[6] = (char * )malloc(sizeof(char ) * 27 + 1);
	argv[7] = (char * )malloc(sizeof(char ) * 27 + 1);
	argv[8] = (char * )malloc(sizeof(char ) * 27 + 1);
	argv[9] = (char * )malloc(sizeof(char ) * 27 + 1);

	str_cpy(argv[0], "9.ox");
	str_cpy(argv[1], "...........................");
	str_cpy(argv[2], "....o......................");
	str_cpy(argv[3], "............o..............");
	str_cpy(argv[4], "...........................");
	str_cpy(argv[5], "....o......................");
	str_cpy(argv[6], "...............o...........");
	str_cpy(argv[7], "...........................");
	str_cpy(argv[8], "......o..............o.....");
	str_cpy(argv[9], "..o.......o................");
	show_map(argv);
	sq_set(&save_sq, -1, -1, 0);
	sq_set(&used_sq, 1, 0, 1);
	
//	sq_set(&used_sq, 5, 5, 5);

	map.max_sq_size = get_min_of(map.width, map.height);					 //printf("\nmap.max_sq_size: %d", map.max_sq_size);
														//	printf("used_sq.size : %d\n", used_sq.size);
	check_sq_on_y(argv, &used_sq, &save_sq, &map);
																	//max_save_sq_size finded or not if (save_sq_size == 0).
	fill_sq(argv, &save_sq, map.fill_symb);								//	sq_set(&used_sq, 2, 5, -1);

	printf("\nused_sq y   : %d", used_sq.y );
	printf("\nused_sq x   : %d", used_sq.x );
	printf("\nused_sq size: %d", used_sq.size );
	printf("\nsave_sq y   : %d", save_sq.y );
	printf("\nsave_sq x   : %d", save_sq.x );
	printf("\nsave_sq size: %d\n\n", save_sq.size );

	show_map(argv);
	write(1, "\n", 1);
	return (0);
}
