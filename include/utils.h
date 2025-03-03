/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:49 by tlima-de          #+#    #+#             */
/*   Updated: 2025/02/18 11:39:05 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Funções utilitárias

#if !defined(UTILS_H)
#define UTILS_H

#include "cub3d.h"
#include <stdbool.h>
#include "libft.h"


#define NORTH 1
#define SOUTH 2
#define WEST 3
#define EAST 4


//funções de distância
float distance(float x, float y);
float fixed_dist(float x1, float y1, float x2, float y2, t_game *game);
int touch(float px, float py, t_game *game);
void debug_textures(t_textures *textures);
void free_split(char **split);





#endif// UTILS_H