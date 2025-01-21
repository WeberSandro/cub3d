/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:02:16 by tlima-de          #+#    #+#             */
/*   Updated: 2025/01/14 13:45:09 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"



void draw_map(t_game *game)
{
    char **map = game->map;
    int color = 0x0000FF;
    for (int y = 0; map[y]; y++)
        for (int x = 0; map[y][x]; x++)
            if (map[y][x] == '1')
                draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
}

void free_map(char **map)
{
    if (!map)
        return;

    for (int i = 0; map[i]; i++)
    {
        free(map[i]);
        map[i] = NULL;
    }

    free(map);
    map = NULL;
}

void load_map(const char *file_path, t_game *game)
{
    int fd = open(file_path, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening map file");
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    int row = 0;
    bool map_started = false;

    // Alocar memória para o mapa
    game->map = malloc(sizeof(char *) * (MAP_HEIGHT + 1)); // +1 para NULL
    if (!game->map)
    {
        perror("Error allocating memory for map");
        exit(EXIT_FAILURE);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        if (!map_started)
        {
            // Processar linhas de configuração
            if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0 ||
                ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
            {
                load_textures(line, &game->textures);
            }
            else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
            {
                parse_colors(line, game); // Adicione uma função para processar cores do teto e do chão
            }
            else if (ft_isdigit(line[0]))
            {
                // Início do mapa detectado
                map_started = true;
            }
        }

        if (map_started)
        {
            if (row >= MAP_HEIGHT)
            {
                fprintf(stderr, "Error: Map exceeds defined height\n");
                free(line);
                free_map(game->map);
                close(fd);
                exit(EXIT_FAILURE);
            }
            game->map[row++] = line;
        }
        else
        {
            free(line);
        }
    }

    game->map[row] = NULL; // Finaliza o array do mapa
    close(fd);
}

