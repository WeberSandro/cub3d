/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanweber <sanweber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:03:17 by tlima-de          #+#    #+#             */
/*   Updated: 2025/02/25 13:31:52 by sanweber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include <stdio.h>

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
	player->key_esc = false;
}

int	key_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	if (keycode == ESC)
		player->key_esc = true;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	if (keycode == ESC)
		player->key_esc = false;
	return (0);
}

void	rotate_player(t_player *player)
{
	float	angle_speed;

	angle_speed = 0.02;
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
}

void	move_player(t_player *player, t_game *game)
{
	int		speed;
	float	cos_angle;
	float	sin_angle;
	float	new_x;
	float	new_y;

	speed = 3;
	rotate_player(player);
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	new_x = player->x + cos_angle * speed * (player->key_up - player->key_down)
		+ sin_angle * speed * (player->key_left - player->key_right);
	new_y = player->y + sin_angle * speed * (player->key_up - player->key_down)
		- cos_angle * speed * (player->key_left - player->key_right);
	if (game->map[(int)(player->y / BLOCK)][(int)(new_x / BLOCK)] != '1')
		player->x = new_x;
	if (game->map[(int)(new_y / BLOCK)][(int)(player->x / BLOCK)] != '1')
		player->y = new_y;
}

/*
void move_player(t_player *player, t_game *game)
{
    int speed = 3;
    float angle_speed = 0.02;

    // Calcula o cosseno e seno do ângulo atual do jogador
    float cos_angle = cos(player->angle);
    float sin_angle = sin(player->angle);
    // Nova posição do jogador
    float new_x = player->x;
    float new_y = player->y;
    // Rotação do jogador
    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;
    if (player->angle > 2 * PI)
        player->angle -= 2 * PI;
    if (player->angle < 0)
        player->angle += 2 * PI;
    // Movimento para frente e para trás
    if (player->key_up)
    {
        new_x += cos_angle * speed;
        new_y += sin_angle * speed;
    }
    if (player->key_down)
    {
        new_x -= cos_angle * speed;
        new_y -= sin_angle * speed;
    }
    // Movimento lateral (strafe)
    if (player->key_left)
    {
        new_x += sin_angle * speed;
        new_y -= cos_angle * speed;
    }
    if (player->key_right)
    {
        new_x -= sin_angle * speed;
        new_y += cos_angle * speed;
    }
    // Verifica se a nova posição colide com uma parede
    int map_x = (int)(new_x / BLOCK);
    int map_y = (int)(new_y / BLOCK);
    if (game->map[map_y][(int)(player->x / BLOCK)] != '1') // Checa o eixo Y
        player->y = new_y;
    if (game->map[(int)(player->y / BLOCK)][map_x] != '1') // Checa o eixo X
        player->x = new_x;
}*/

/*
Resumo do Uso de PI
2 * PI: Representa uma rotação completa (360 graus).
cos e sin: Usam o ângulo em radianos para determinar o deslocamento no plano.
Normalização do ângulo: Garante que o ângulo não ultrapasse os limites de uma
 rotação completa, evitando cálculos redundantes.
*/