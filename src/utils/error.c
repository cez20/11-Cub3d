#include "../include/cub3d.h"

void	errmsg(char *msg, int tofree, t_game *game)
{
	if (tofree == 1)
		free_game(game);
	write(2, msg, ft_strlen(msg));
	close(game->fd);
	exit(EXIT_FAILURE);
}
