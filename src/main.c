/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanweber <sanweber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:01:12 by tlima-de          #+#    #+#             */
/*   Updated: 2025/02/27 17:10:36 by sanweber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "map.h"
#include "player.h" /* Para key_press e key_release */
#include "render.h" /* Para draw_loop */

/* Callback fechamento da janela e termino do programa so por aqui */
int	exit_program(t_game *game)
{
	if (game->textures.north)
		mlx_destroy_image(game->mlx, game->textures.north);
	if (game->textures.south)
		mlx_destroy_image(game->mlx, game->textures.south);
	if (game->textures.east)
		mlx_destroy_image(game->mlx, game->textures.east);
	if (game->textures.west)
		mlx_destroy_image(game->mlx, game->textures.west);
	free(game->textures.no);
	free(game->textures.so);
	free(game->textures.ea);
	free(game->textures.we);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	free_map(game->map);
	exit(0);
	return (0);
}

void	free_map_file(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

char	**initialize_map(int *fd, int argc, char *file)
{
	int		i;
	char	**map;

	if (argc != 2)
		error_system("Map File Required to");
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
		error_system("Error opening file");
	map = malloc(sizeof(char *) * MAX_MAP_LINES);
	if (!map)
		error_system("Error allocating memory to the map");
	i = 0;
	while (i < MAX_MAP_LINES)
	{
		map[i] = NULL;
		i++;
	}
	return (map);
}

int	main(int argc, char *argv[])
{
	t_game	game;
	char	**map;
	int		fd;
	int		map_lines;
	int		map_width;

	ft_memset(&game, 0, sizeof(t_game));
	map = initialize_map(&fd, argc, argv[1]);
	if (!mapvalid(fd, map, &map_lines, &map_width))
	{
		free_map_file(map);
		close(fd);
		return (0);
	}
	close(fd);
	game.map_height = map_lines;
	game.map_width = map_width;
	init_game(&game, map);
	free_map_file(map);
	mlx_hook(game.win, 17, 0, exit_program, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
