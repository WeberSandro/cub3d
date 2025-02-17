/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanweber <sanweber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:02:16 by tlima-de          #+#    #+#             */
/*   Updated: 2025/02/14 12:07:17 by sanweber         ###   ########.fr       */
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

//void load_map(const char *file_path, t_game *game)
void load_map(char map[MAX_MAP_LINES][MAX_LINE], t_game *game)
{
    //int fd = open(file_path, O_RDONLY);
    //if (fd < 0)
    //{
    //    perror("Error opening map file");
    //    exit(EXIT_FAILURE);
    //}

    int     i;  
    //char    *line = NULL;
    char    line[256];
    int     row = 0;
    bool    map_started = false;

    // Alocar memória para o mapa
    game->map = malloc(sizeof(char *) * (game->MAP_HEIGHT + 1)); // +1 para NULL
    if (!game->map)
    {
        perror("Error allocating memory for map");
        exit(EXIT_FAILURE);
    }
    i = 0;
    //while ((line = get_next_line(fd)) != NULL)
    while (i < game->MAP_HEIGHT)
    {
        ft_strlcpy(line, map[i], ft_strlen(map[i]));
        if (!map_started)
        {
            // Processar linhas de configuração
            if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "WE", 2) == 0 ||
                ft_strncmp(line, "SO", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
            {
                load_textures(line, &game->textures);
            }
            else if (ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
            {
                parse_colors(line, game); // Adicione uma função para processar cores do teto e do chão
            }
            else if (ft_isdigit(line[0]))
            {
                // Início do mapa detectado
                printf("achei o mapa\n");
                map_started = true;
            }
        }

        if (map_started)
        {
            if (row >= game->MAP_HEIGHT)
            {
                fprintf(stderr, "Error: Map exceeds defined height\n");
                //free(line);
                free_map(game->map);
                //close(fd);
                exit(EXIT_FAILURE);
            }
            game->map[row++] = line;
        }
        else
        {
            //free(line);
        }
        i++;
    }

    game->map[row] = NULL; // Finaliza o array do mapa
    //close(fd);
}

