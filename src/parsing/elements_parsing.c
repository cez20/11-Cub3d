#include "../include/cub3d.h"

void	check_colors(t_game *game, char *element)
{
	int		i;
	int		n;
	char	**rgb;
	char	*tmp;

	i = -1;
	n = 0;
	rgb = ft_split(&element[2], ',');
	while (rgb[++i])
	{
		if (i >= 3)
			errmsg(ERR_RGB, 1, game);
		n = ft_atoi(rgb[i]);
		tmp = rgb[i];
		skip_whitespaces(&tmp);
		if ((n < 0 || n > 255) || !ft_strcmp(tmp, "-0"))
			errmsg(ERR_RGB, 1, game);
		else
		{
			if (element[0] == 'F')
				game->tex->floor[i] = n;
			if (element[0] == 'C')
				game->tex->ceiling[i] = n;
		}
	}
	free_table(rgb);
}

//This function validates that the textures has a valid path 
//and skip any unecessary elements that can be found before (whitespaces). 
char	*create_texture_path(t_game *game, char *path)
{
	char	*texture_path;
	char	*tmp;
	int		i;
	int		fd;

	i = 0;
	while (ft_is_whitespace(path[i]))
		i++;
	tmp = ft_strdup(&path[i]);
	fd = open(tmp, O_RDONLY);
	if (fd == -1)
		errmsg(ERR_TEXTURE_PATH, 1, game);
	texture_path = tmp;
	tmp = NULL;
	close (fd);
	return (texture_path);
}

void	check_direction(t_game *game, char *str, char **texture_path)
{
	char	**tab;

	if (!(*texture_path))
	{
		tab = ft_split(str, ' ');
		if (nb_of_strings(tab) != 2)
			errmsg(ERR_TOOMUCH_TEXT, 1, game);
		*texture_path = create_texture_path(game, tab[1]);
		free_double_pointer(tab);
	}
	else
		errmsg(ERR_EXTRA_ELEMENT, 1, game);
}

void	verify_elements(t_game *game)
{
	int	i;

	i = 0;
	while (game->elements_copy[i])
	{
		if (ft_strncmp(game->elements_copy[i], "NO", 2) == 0)
			check_direction(game, game->elements_copy[i], &game->tex->north);
		else if (ft_strncmp(game->elements_copy[i], "SO", 2) == 0)
			check_direction(game, game->elements_copy[i], &game->tex->south);
		else if (ft_strncmp(game->elements_copy[i], "WE", 2) == 0)
			check_direction(game, game->elements_copy[i], &game->tex->west);
		else if (ft_strncmp(game->elements_copy[i], "EA", 2) == 0)
			check_direction(game, game->elements_copy[i], &game->tex->east);
		else if (ft_strncmp(game->elements_copy[i], "F ", 2) == 0 \
			|| ft_strncmp(game->elements_copy[i], "C ", 2) == 0)
			check_colors(game, game->elements_copy[i]);
		else
			errmsg(ERR_WRONG_ELEMENT, 1, game);
		i++;
	}
	if (!game->tex->north || !game->tex->south || !game->tex->east \
	|| !game->tex->west || game->tex->floor[0] == -1 \
	|| game->tex->ceiling[0] == -1)
		errmsg(ERR_MISSING_ELEMENT, 1, game);
}
