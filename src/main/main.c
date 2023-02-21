#include "../include/cub3d.h"

void	init_variables(t_game *game)
{
	game->fd = 0;
	game->total_length = 0;
	game->map_index = 0;
	game->map_width = 0;
	game->map_height = 0;
	game->nb_player = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->game_copy = NULL;
	game->map_copy = NULL;
	game->elements_copy = NULL;
	game->mlx = NULL;
	game->window = NULL;
}

void	close_fds(t_game *game)
{
	close(game->fd);
}

/*static int	clean_exit (t_game *game)
{
	//check game->mlx, game->window
	free_table(game->map_copy);
	return (0);
}*/

int	main(int argc, char **argv)
{
	t_game	game;

	init_variables(&game);
	game_validation(&game, argc, argv[1]);
	game_sections_copy(&game, argv[1]);
	game_parsing(&game);
	//printf("[ MAP BEFORE FLOODFILL ]\n");
	//print_game(game.map_copy);
	//flood_fill(game.player_x, game.player_y, &game); // ints = starting player coordinates
	//printf("\n[ MAP AFTER FLOODFILL ]\n");
	//print_game(game.map_copy);
	free_game(&game);
	close_fds(&game);
//	return (clean_exit(&game));
	return (0);
}
