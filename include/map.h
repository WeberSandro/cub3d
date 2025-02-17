/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanweber <sanweber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:59:00 by tlima-de          #+#    #+#             */
/*   Updated: 2025/02/13 15:49:32 by sanweber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Funções e estruturas relacionadas ao mapa
#if !defined(MAP_H)
#define MAP_H

#include "render.h" // Para usar draw_square
#include "libft.h" // Certifique-se de incluir isso
#include <fcntl.h>    // Para open()
#include <unistd.h>   // Para read() e close()
#include <stdlib.h>   // Para malloc()
#include <stdio.h>    // Para perror()
#include "textures.h"

#define MAX_LINE 256
#define MAX_MAP_LINES 100  

//#define MAP_HEIGHT 15
//#define MAP_WIDTH  30 // Ajuste conforme a largura do seu mapa
#define WIDTH 1280
#define HEIGHT 720


//funções
void draw_map(t_game *game);
//void load_map(const char *file_path, t_game *game);
void load_map(char map[MAX_MAP_LINES][MAX_LINE], t_game *game);
void free_map(char **map);
int exit_program(t_game *game);
int mapvalid(int fd, char map[MAX_MAP_LINES][MAX_LINE], int *map_lines);
void init_game(t_game *game, char map[MAX_MAP_LINES][MAX_LINE]);

#endif
