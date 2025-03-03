/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanweber <sanweber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:00:26 by tales             #+#    #+#             */
/*   Updated: 2025/02/27 17:20:49 by sanweber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "map.h"
#include "player.h"

static void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		fprintf(stderr, "Error: Failed to initialize MiniLibX.\n");
		exit(1);
	}
}

static void	init_window_img_data(t_game *game)
{
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	if (!game->win)
	{
		fprintf(stderr, "Error: Failed to create a window.\n");
		exit(1);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		fprintf(stderr, "Error: Failed to create an image.\n");
		exit(1);
	}
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	if (!game->data)
	{
		fprintf(stderr, "Error: Failed to get image data address.\n");
		exit(1);
	}
}

static void	set_player_at(t_game *game, int x, int y, char c)
{
	game->player.x = x * BLOCK + BLOCK / 2;
	game->player.y = y * BLOCK + BLOCK / 2;
	if (c == 'N')
		game->player.angle = PI / 2;
	else if (c == 'S')
		game->player.angle = 3 * PI / 2;
	else if (c == 'E')
		game->player.angle = 0;
	else if (c == 'W')
		game->player.angle = PI;
	game->map[y][x] = '0';
}

void	set_player_position(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			c = game->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				set_player_at(game, x, y, c);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_game(t_game *game, char **map)
{
	init_mlx(game);
	init_player(&game->player);
	load_map(map, game);
	load_images(game->mlx, &game->textures);
	set_player_position(game);
	init_window_img_data(game);
}
