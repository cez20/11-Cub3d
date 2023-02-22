#include "../include/cub3d.h"

//This function indicates player position: North, East, West, South (NEWS)
int	is_news(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

int	is_wall(char c)
{
	if (c == '1' || c == '0')
		return (1);
	return (0);
}

void	player_position(t_game *game, int x, int y)
{
	if (game->nb_player == 0)
	{
		game->player_x = x;
		game->player_y = y;
		game->nb_player++;
	}
	else
		game->nb_player++;
}

void	skip_whitespaces(char **str)
{
	if (!*str || !**str)
		return ;
	while (**str && ft_isset(**str, WHITESPACE))
		*str += 1;
	return ;
}

static void	check_colors(t_game *game, char *element)
{
	int		i;
	int		n;
	char	**rgb;
	char	mode;

	i = -1;
	n = 0;
	rgb = ft_split(&element[i + 3], ',');
	mode = element[0];
	while (rgb[++i])
	{
		if (i >= 3)
			errmsg(ERR_RGB, 1, game);
		n = ft_atoi(rgb[i]);
		skip_whitespaces(&rgb[i]);
		if ((n < 0 || n > 255) || !ft_strcmp(rgb[i], "-0"))
			errmsg(ERR_RGB, 1, game);
		else
		{
			if (mode == 'F')
				game->tex->floor[i] = n;
			if (mode == 'C')
				game->tex->ceiling[i] = n;
		}
	}
	free_double_pointer(rgb);
}

void	verify_elements(t_game *game)
{
	int	i;

	i = 0;
	print_game(game->elements_copy);
	while (game->elements_copy[i])
	{
		// if (is_cardinal_direction(game->elements_copy[i]))
		// 	check_direction(game, game->elements_copy[i]);
		if (ft_strncmp(game->elements_copy[i], "NO", 2) == 0)
			check_direction(game, game->elements_copy[i], &game->tex->north);
		else if (ft_strncmp(game->elements_copy[i], "SO", 2) == 0)
			check_direction(game, game->elements_copy[i], &game->tex->south);
		else if (ft_strncmp(game->elements_copy[i], "WE", 2) == 0)
			check_direction(game, game->elements_copy[i], &game->tex->west);
		else if (ft_strncmp(game->elements_copy[i], "EA", 2) == 0)
			check_direction(game, game->elements_copy[i], &game->tex->east);
		else if (!ft_strncmp(game->elements_copy[i], "F ", 2) \
			|| !ft_strncmp(game->elements_copy[i], "C ", 2))
			check_colors(game, game->elements_copy[i]);
		else
			errmsg(ERR_ELEMENTS, 1, game);
		i++;
	}
	if (!game->tex->north || !game->tex->south || game->tex->west \
	|| game->tex->west || game->tex->floor[0] == -1 \
	|| game->tex->ceiling[0] == -1)
		errmsg(ERR_ELEMENTS, 1, game); //Not all elements are present. 
}

void	verify_map_characters(t_game *g)
{
	int		i;
	int		j;

	i = 0;
	while (g->map_copy[i])
	{
		j = 0;
		while (g->map_copy[i][j])
		{
			if (is_wall(g->map_copy[i][j]) || is_news(g->map_copy[i][j]) ||
			ft_isset(g->map_copy[i][j], "-"))
			{
				if (is_news(g->map_copy[i][j]))
					player_position(g, i, j);
			}
			else
				errmsg(ERR_CONTENT, 1, g);
			j++;
		}
		i++;
	}
	if (g->nb_player < 1 || g->nb_player > 1)
		errmsg(ERR_CONTENT, 1, g);
	printf("player(%f, %f)\n", g->player_x, g->player_y);
}



void	game_parsing(t_game *game)
{
	verify_elements(game);
	verify_map_characters(game);
	verify_map_walls(game);
	replace_map_spaces(game);
}
