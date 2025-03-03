/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanweber <sanweber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:04:37 by tlima-de          #+#    #+#             */
/*   Updated: 2025/02/27 16:46:30 by sanweber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle_diff;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle_diff = atan2(delta_y, delta_x) - game->player.angle;
	while (angle_diff < -PI)
		angle_diff += 2 * PI;
	while (angle_diff > PI)
		angle_diff -= 2 * PI;
	return (sqrt(delta_x * delta_x + delta_y * delta_y) * cos(angle_diff));
}

int	touch(float px, float py, t_game *game)
{
	int		x;
	int		y;
	float	offset_x;
	float	offset_y;

	if (!game || !game->map)
		return (0);
	x = (int)(px / BLOCK);
	y = (int)(py / BLOCK);
	if (y < 0 || y >= game->map_height || x < 0 || x >= game->map_width)
		return (0);
	if (game->map[y][x] == '1')
	{
		offset_x = px - x * BLOCK;
		offset_y = py - y * BLOCK;
		if (offset_x < 1.0)
			return (WEST);
		else if (offset_x > BLOCK - 1.0)
			return (EAST);
		else if (offset_y < 1.0)
			return (NORTH);
		else if (offset_y > BLOCK - 1.0)
			return (SOUTH);
	}
	return (0);
}

void	debug_textures(t_textures *textures)
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

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
