#include "render.h" // Cabeçalho para funções de renderização
#include "utils.h"  // Para funções como touch e fixed_dist
#include "player.h" // Para funções como move_player
#include "map.h"    // Para a função draw_map

void put_pixel(int x, int y, int color, t_game *game)
{
    // Verifica se as coordenadas (x, y) estão dentro dos limites da janela
    if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;

    // Calcula o índice no buffer de imagem
    int index = y * game->size_line + x * game->bpp / 8;

    // Define os valores de cor (B, G, R) no buffer
    game->data[index] = color & 0xFF;             // Azul
    game->data[index + 1] = (color >> 8) & 0xFF;  // Verde
    game->data[index + 2] = (color >> 16) & 0xFF; // Vermelho
}

void clear_image(t_game *game)
{
    // Itera sobre todas as linhas da janela
    for (int y = 0; y < HEIGHT; y++)
        // Itera sobre todas as colunas da janela
        for (int x = 0; x < WIDTH; x++)
            // Define cada pixel como preto
            put_pixel(x, y, 0, game);
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
    // Desenha a borda superior
    for (int i = 0; i < size; i++)
        put_pixel(x + i, y, color, game);

    // Desenha a borda esquerda
    for (int i = 0; i < size; i++)
        put_pixel(x, y + i, color, game);

    // Desenha a borda inferior
    for (int i = 0; i < size; i++)
        put_pixel(x + size, y + i, color, game);

    // Desenha a borda direita
    for (int i = 0; i < size; i++)
        put_pixel(x + i, y + size, color, game);
}

void draw_line(t_player *player, t_game *game, float start_x, int i)
{
    float cos_angle = cos(start_x);
    float sin_angle = sin(start_x);
    float ray_x = player->x;
    float ray_y = player->y;

    while (!touch(ray_x, ray_y, game))
    {
        ray_x += cos_angle;
        ray_y += sin_angle;
    }

    int direction = touch(ray_x, ray_y, game);
    void *texture = NULL;

    // Selecionar textura com base na direção
    if (direction == NORTH)
        texture = game->textures.north;
    else if (direction == SOUTH)
        texture = game->textures.south;
    else if (direction == WEST)
        texture = game->textures.west;
    else if (direction == EAST)
        texture = game->textures.east;

    if (!texture)
        return;

    float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
    float height = (BLOCK / dist) * (WIDTH / 2);
    int wall_start = (int)((HEIGHT - height) / 2);
    int wall_end = (int)(wall_start + height);

    if (wall_start < 0) wall_start = 0; // Corrige valores negativos
    if (wall_end >= HEIGHT) wall_end = HEIGHT; // Corrige valores maiores que a altura

    int texture_width = 40, texture_height = 40;
    int texture_x;
    if (direction == NORTH || direction == SOUTH)
        texture_x = (int)((ray_x - floor(ray_x / BLOCK) * BLOCK) * texture_width / BLOCK);
    else
        texture_x = (int)((ray_y - floor(ray_y / BLOCK) * BLOCK) * texture_width / BLOCK);

    if (texture_x < 0 || texture_x >= texture_width)
        texture_x = texture_width - 1;

    for (int y = wall_start; y < wall_end; y++)
    {
        int texture_y = (y - wall_start) * texture_height / (wall_end - wall_start);

        if (texture_y < 0 || texture_y >= texture_height)
            texture_y = texture_height - 1;

        int color = get_texture_color(texture, texture_x, texture_y);
        put_pixel(i, y, color, game);
    }

    // Pintar teto
    if (wall_start > 0)
    {
        for (int y = 0; y < wall_start; y++)
            put_pixel(i, y, game->ceiling_color, game);
    }

    // Pintar solo
    if (wall_end < HEIGHT)
    {
        for (int y = wall_end; y < HEIGHT; y++)
            put_pixel(i, y, game->floor_color, game);
    }
}

int draw_loop(t_game *game)
{
    t_player *player = &game->player;

    if (player->key_esc)
        exit_program(game);
       
    // Atualiza a posição do jogador
    move_player(player, game);

    // Limpa a tela
    clear_image(game);

    // Renderiza elementos no modo DEBUG
    if (DEBUG)
    {
        draw_square(player->x, player->y, 10, 0x00FF00, game); // Posição do jogador
        draw_map(game);                                        // Desenha o mapa
    }

    // Raycasting: calcula e desenha os raios
    float fraction = PI / 3 / WIDTH;
    float start_x = player->angle - PI / 6;
    int i = 0;
    while (i < WIDTH)
    {
        draw_line(player, game, start_x, i);
        start_x += fraction;
        i++;
    }

    // Atualiza a imagem na janela
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

    return 0;
}


int get_texture_color(void *img, int x, int y)
{
    int bpp, size_line, endian;
    char *data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
    if (!data)
    {
        fprintf(stderr, "Error: Invalid texture data\n");
        exit(EXIT_FAILURE);
    }

    int index = (y * size_line) + (x * (bpp / 8));
    return *(int *)(data + index);
}

/*
 *
 * Resumo
Função	Objetivo
put_pixel	Desenha um pixel em (x, y) no buffer de imagem.
clear_image	Preenche a tela com preto (limpa a imagem).
draw_square	Desenha um quadrado de tamanho size na posição (x, y).
draw_line	Desenha um raio (linha) e calcula paredes no raycasting.
draw_loop	Loop principal de renderização que desenha todos os elementos.
*/