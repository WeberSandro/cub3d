/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanweber <sanweber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:19:07 by tlima-de          #+#    #+#             */
/*   Updated: 2025/02/20 14:43:43 by sanweber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"
#include <stdio.h>

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	get_color_value(char **split)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		fprintf(stderr, "Error: Color values must be between 0 and 255\n");
		exit(EXIT_FAILURE);
	}
	return ((r << 16) | (g << 8) | b);
}

void	load_textures(const char *line, t_textures *textures)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		textures->no = ft_strdup(line + 2);
	else if (ft_strncmp(line, "WE", 2) == 0)
		textures->we = ft_strdup(line + 2);
	else if (ft_strncmp(line, "SO", 2) == 0)
		textures->so = ft_strdup(line + 2);
	else if (ft_strncmp(line, "EA", 2) == 0)
		textures->ea = ft_strdup(line + 2);
	else
	{
		fprintf(stderr, "Error: Invalid texture line\n");
		exit(EXIT_FAILURE);
	}
}

void	parse_colors(const char *line, t_game *game)
{
	char	**split;
	int		color;

	split = ft_split(line + 1, ',');
	if (!split || !split[0] || !split[1] || !split[2])
	{
		fprintf(stderr, "Error: Invalid color format\n");
		exit(EXIT_FAILURE);
	}
	color = get_color_value(split);
	if (line[0] == 'F')
		game->floor_color = color;
	else if (line[0] == 'C')
		game->ceiling_color = color;
	free_split(split);
}

void	load_images(void *mlx, t_textures *textures)
{
	int	width;
	int	height;

	textures->north = mlx_xpm_file_to_image(mlx, textures->no,
			&width, &height);
	textures->south = mlx_xpm_file_to_image(mlx, textures->so,
			&width, &height);
	textures->east = mlx_xpm_file_to_image(mlx, textures->ea,
			&width, &height);
	textures->west = mlx_xpm_file_to_image(mlx, textures->we,
			&width, &height);
	if (!textures->north || !textures->south || !textures->east || \
		!textures->west)
	{
		fprintf(stderr, "Error: Failed to load one or more textures.\n");
		exit(EXIT_FAILURE);
	}
	debug_textures(textures);
}
