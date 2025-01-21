/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:00:26 by tales             #+#    #+#             */
/*   Updated: 2025/01/20 12:37:43 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Inicializa o jogo
#include "cub3d.h"
#include "player.h"  // Para a função init_player
#include "map.h"     // Para a função load_map


void init_game(t_game *game)
{
    // Inicializar o MiniLibX
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        fprintf(stderr, "Error: Failed to initialize MiniLibX.\n");
        exit(1);
    }

    // Inicializar o jogador
    init_player(&game->player);

    // Carregar o mapa e as texturas
    load_map("asserts/maps/level1.cub", game);
    load_images(game->mlx, &game->textures);

    // Depurar texturas (opcional)
    debug_textures(&game->textures);

    // Criar a janela
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
    if (!game->win)
    {
        fprintf(stderr, "Error: Failed to create a window.\n");
        exit(1);
    }

    // Criar a imagem
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->img)
    {
        fprintf(stderr, "Error: Failed to create an image.\n");
        exit(1);
    }

    // Obter o endereço da imagem
    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    if (!game->data)
    {
        fprintf(stderr, "Error: Failed to get image data address.\n");
        exit(1);
    }
}
