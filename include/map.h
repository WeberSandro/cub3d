/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanweber <sanweber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:59:00 by tlima-de          #+#    #+#             */
/*   Updated: 2025/02/24 13:27:46 by sanweber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Funções e estruturas relacionadas ao mapa
#if !defined(MAP_H)
#define MAP_H

#include "render.h" 
#include "libft.h" 
#include <fcntl.h>    
#include <unistd.h>   
#include <stdlib.h>   
#include <stdio.h>    
#include "textures.h"

#define MAX_LINE 256
#define MAX_MAP_LINES 100  

#define WIDTH 1280
#define HEIGHT 720

void    draw_map(t_game *game);
void    load_map(char **map, t_game *game);
void    free_map(char **map);
int     exit_program(t_game *game);
int     mapvalid(int fd, char **map, int *map_lines, int *map_width);
void    init_game(t_game *game, char **map);
void	error_system(char *str);
void	charge_map(int fd, char **map, int *map_lines, int *map_width);
bool    is_texture_or_color(char *line);
void    process_line(char *line, bool *map_started, t_game *game);
void	remove_spaces(char *str);
int 	test_view(char *view, int *flags);
int 	parse_map(int fd, char **map, int *map_lines);
int     is_valid_char(char c);
int     is_valid_map_line(const char *line);
int     is_map_closed(char **map, int map_lines);

#endif
