/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanweber <sanweber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:59:12 by tlima-de          #+#    #+#             */
/*   Updated: 2025/02/20 14:16:57 by sanweber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Funções e estruturas do jogador

#if !defined(PLAYER_H)
#define PLAYER_H

#include "cub3d.h"
#include <stdbool.h>


void init_player(t_player *player);
void set_player_position(t_game *game);
int key_release(int keycode, t_player *player);
int key_press(int keycode, t_player *player);
void move_player(t_player *player, t_game *game);
void parse_colors(const char *line, t_game *game);

#endif

