/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanweber <sanweber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:19:07 by tlima-de          #+#    #+#             */
/*   Updated: 2025/02/17 13:55:48 by sanweber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"
#include <stdio.h>

void load_textures(const char *line, t_textures *textures)
{
    if (ft_strncmp(line, "NO", 2) == 0)
        textures->north = ft_strdup(line + 2); // Copia o caminho após "NO "
    else if (ft_strncmp(line, "WE", 2) == 0)
        textures->west = ft_strdup(line + 2); // Copia o caminho após "WE "
    else if (ft_strncmp(line, "SO", 2) == 0)
        textures->south = ft_strdup(line + 2); // Copia o caminho após "SO "
    else if (ft_strncmp(line, "EA", 2) == 0)
        textures->east = ft_strdup(line + 2); // Copia o caminho após "EA "
    else
    {
        fprintf(stderr, "Error: Invalid texture line\n");
        exit(EXIT_FAILURE);
    }
    printf("passei aqui\n");
}

void parse_colors(const char *line, t_game *game)
{    
    char **split = ft_split(line + 1, ','); // Divide valores após "F " ou "C "
    if (!split || !split[0] || !split[1] || !split[2])
    {
        fprintf(stderr, "Error: Invalid color format\n");
        exit(EXIT_FAILURE);
    }

    int r = ft_atoi(split[0]);
    int g = ft_atoi(split[1]);
    int b = ft_atoi(split[2]);

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        fprintf(stderr, "Error: Color values must be between 0 and 255\n");
        exit(EXIT_FAILURE);
    }

    int color = (r << 16) | (g << 8) | b; // Converte para valor hexadecimal

    if (line[0] == 'F')
        game->floor_color = color;
    else if (line[0] == 'C')
        game->ceiling_color = color; // Corrige para usar o valor hexadecimal calculado

    // Libera a memória
    for (int i = 0; split[i]; i++)
        free(split[i]);
    free(split);
    printf("passei aqui nas cores\n");
}

void load_images(void *mlx, t_textures *textures)
{
    int width, height;

    textures->north = mlx_xpm_file_to_image(mlx, "asserts/textures/1.xpm", &width, &height);
    
    textures->south = mlx_xpm_file_to_image(mlx, "asserts/textures/2.xpm", &width, &height);

    textures->east = mlx_xpm_file_to_image(mlx, "asserts/textures/3.xpm", &width, &height);

    textures->west = mlx_xpm_file_to_image(mlx, "asserts/textures/4.xpm", &width, &height);

if (!textures->north || !textures->south || !textures->east || !textures->west)
{
    fprintf(stderr, "Error: Failed to load one or more textures.\n");
    exit(EXIT_FAILURE);
}

    debug_textures(textures);
}
