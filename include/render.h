/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:34 by tlima-de          #+#    #+#             */
/*   Updated: 2025/01/21 11:13:14 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//funções e estruturas relacionadas à renderização

#if !defined(RENDER_H)
#define RENDER_H

#include "cub3d.h"



//funções de renderização
void put_pixel(int x, int y, int color, t_game *game);
void clear_image(t_game *game);
void draw_square(int x, int y, int size, int color, t_game *game);
void draw_line(t_player *player, t_game *game, float start_x, int i);
int draw_loop(t_game *game);
int get_texture_color(void *img, int x, int y);


#endif // RENDER_H