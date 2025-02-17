/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanweber <sanweber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:04:37 by tlima-de          #+#    #+#             */
/*   Updated: 2025/02/14 15:18:52 by sanweber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include "utils.h"

float distance(float x, float y)
{
    return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float angle_diff = atan2(delta_y, delta_x) - game->player.angle;

    while (angle_diff < -PI)
        angle_diff += 2 * PI;
    while (angle_diff > PI)
        angle_diff -= 2 * PI;

    return sqrt(delta_x * delta_x + delta_y * delta_y) * cos(angle_diff);
}


int touch(float px, float py, t_game *game)
{
    if (!game || !game->map) // Ver se o game e o mapa são válidos ULTIMA COISA
    {
        printf("error game - touch \n"); // tirar, botei pra teste todo if
        return 0;
    }
        
    int x = (int)(px / BLOCK);
    int y = (int)(py / BLOCK);

    if (y < 0 || y >= game->MAP_HEIGHT || x < 0 || x >= game->MAP_WIDTH)
    {
        printf("error map - touch ok \n");  // tirar, botei pra teste todo if
        return 0;
    }

    if (game->map[y][x] == '1')
    {
        float offset_x = px - x * BLOCK;
        float offset_y = py - y * BLOCK;

        if (offset_x < 1.0) // Perto da borda esquerda (WEST)
            return WEST;
        else if (offset_x > BLOCK - 1.0) // Perto da borda direita (EAST)
            return EAST;
        else if (offset_y < 1.0) // Perto da borda superior (NORTH)
            return NORTH;
        else if (offset_y > BLOCK - 1.0) // Perto da borda inferior (SOUTH)
            return SOUTH;
    }
    return 0; // Sem colisão
}

void debug_textures(t_textures *textures)
{
    if (textures->north)
        printf("North texture loaded\n");
    if (textures->south)
        printf("South texture loaded\n");
    if (textures->east)
        printf("East texture loaded\n");
    if (textures->west)
        printf("West texture loaded\n");
}


void free_split(char **split)
{
    int i = 0;

    if (!split)
        return;

    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}
