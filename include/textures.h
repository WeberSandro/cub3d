/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:18:19 by tlima-de          #+#    #+#             */
/*   Updated: 2025/01/14 11:51:58 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
#define TEXTURES_H

#include "cub3d.h" // Para a estrutura t_game
#include "mlx.h"
#include "libft.h"


void load_textures(const char *line, t_textures *textures);
void parse_colors(const char *line, t_game *game);
void load_images(void *mlx, t_textures *textures);

#endif // TEXTURES_H
