/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanweber <sanweber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:02:16 by tlima-de          #+#    #+#             */
/*   Updated: 2025/02/27 16:34:27 by sanweber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		x;
	int		y;

	map = game->map;
	color = 0x0000FF;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
			x++;
		}
		y++;
	}
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

bool	is_texture_or_color(char *line)
{
	if (!line)
		return (false);
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "WE", 2)
		|| !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "EA", 2))
		return (true);
	if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
		return (true);
	return (false);
}

void	process_line(char *line, bool *map_started, t_game *game)
{
	if (is_texture_or_color(line))
	{
		if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
			parse_colors(line, game);
		else
			load_textures(line, &game->textures);
	}
	else
		*map_started = true;
}

void	load_map(char **map, t_game *game)
{
	int		i;
	int		row;
	bool	map_started;
	char	*line;

	game->map = malloc(sizeof(char *) * (game->map_height + 1 - 6));
	if (!game->map)
		error_system("Error allocating memory for map");
	i = 0;
	row = 0;
	map_started = false;
	while (i < game->map_height)
	{
		line = ft_strdup(map[i]);
		if (!line)
			error_system("Error duplicating map line");
		process_line(line, &map_started, game);
		if (map_started)
			game->map[row++] = line;
		else
			free(line);
		i++;
	}
	game->map[row] = NULL;
	game->map_height = row;
}
