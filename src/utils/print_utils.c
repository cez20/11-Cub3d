#include "../include/cub3d.h"

void	print_variables(t_game *game)
{
	printf("The value of game->fd is %d\n", game->fd);
	printf("The value of game->number_of_lines is %d\n", game->total_length);
	printf("The value of game->number_of_lines is %d\n", game->map_index);
	printf("The value of game->game_copy is %p\n", game->game_copy);
	printf("The value of game->game_copy is %p\n", game->map_copy);
	printf("The value of game->game_copy is %p\n", game->elements_copy);
	printf("The value of game->mlx is %p\n", game->mlx);
	printf("The value of game->window is %p\n", game->window);
}

void	print_game(char **str)
{
	int	i;

	i = 0;
	printf("--------DIVISION HERE----------\n");
	while (str[i])
		printf("%s\n", str[i++]);
}
