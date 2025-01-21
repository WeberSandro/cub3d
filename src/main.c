/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanweber <sanweber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:01:12 by tlima-de          #+#    #+#             */
/*   Updated: 2025/01/21 09:52:59 by sanweber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "player.h"   // Para key_press e key_release
#include "render.h"   // Para draw_loop
#include "map.h"      // Inclua este cabeçalho para acessar free_map

// Callback para o evento de fechamento da janela
int exit_program(t_game *game)
{
    free_map(game->map);
    exit(0); // Encerra o programa
    return 0;
}

int main(void)
{
    t_game game;

    // Inicializa o jogo
    init_game(&game);
    
    // Associa o evento de fechamento ao callback
    mlx_hook(game.win, 17, 0, exit_program, &game);

    // Configura eventos de teclado
    mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
    mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);

    // Loop principal
    mlx_loop_hook(game.mlx, draw_loop, &game);
    mlx_loop(game.mlx);

    // Libera recursos antes de sair * foi transferido para draw_loop (ESC)
    //free_map(game.map); // Certifique-se de liberar apenas uma vez

    return 0;
}