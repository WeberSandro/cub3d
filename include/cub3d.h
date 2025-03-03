/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanweber <sanweber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:58:38 by tlima-de          #+#    #+#             */
/*   Updated: 2025/02/27 17:22:28 by sanweber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Header principal


#if !defined(CUB3D_H)
#define CUB3D_H

#define WIDTH 1280
#define HEIGHT 720
#define BLOCK 64
#define DEBUG 0

#define W 119
#define A 97
#define S 115
#define D 100
#define LEFT 65361
#define RIGHT 65363
#define ESC 65307

#define PI 3.14159265359

#include "../lib/minilibx-linux/mlx.h"  
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct s_player
{
    float x;
    float y;
    float angle;

    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;

    bool left_rotate;
    bool right_rotate;
    bool key_esc;
} t_player;

typedef struct s_textures
{
    void *no;
    void *so;
    void *ea;
    void *we;
    void *north;
    void *south;
    void *east;
    void *west;
} t_textures;

typedef struct s_game
{
    int map_height;
    int map_width; 
    
    void *mlx;
    void *win;
    void *img;

    char *data;
    int bpp;
    int size_line;
    int endian;

    t_player player;
    char **map;
    t_textures textures; 
    int floor_color;
    int ceiling_color;
} t_game;

void debug_textures(t_textures *textures);

#endif 
