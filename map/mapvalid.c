/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvalid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanweber <sanweber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:39:22 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/17 13:50:01 by sanweber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "map.h"

void	remove_spaces(char *str)
{
    int i;
	int	j;
    
	i = 0;
	j = 0;
    while (str[i])
	{
        if (str[i] != ' ')
		{
            str[j] = str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
}

int	test_view(char *view, int *flags)
{
	if ((view[0] == 'N' && view[1] == 'O')
		|| (view[0] == 'S' && view[1] == 'O')
		|| (view[0] == 'W' && view[1] == 'E')
		|| (view[0] == 'E' && view[1] == 'A')
		|| (view[0] == 'F')
		|| (view[0] == 'C'))
	{
		if (view[0] == 'N')
			*flags += 1;
		else if (view[0] == 'S')
			*flags += 10;
		else if (view[0] == 'W')
			*flags += 100;
		else if (view[0] == 'E')
			*flags += 1000;
		else if (view[0] == 'F')
			*flags += 10000;
		else
			*flags += 100000;
		return (1);
	}
	return (0);
}

int	parse_map(int fd, char map[MAX_MAP_LINES][MAX_LINE], int *map_lines)
{
	char	*line;
	int		flags;
	
    flags = 0;
	line = get_next_line(fd);
	while ((line) && (*map_lines < 6))
	{
		remove_spaces(line);
		if (test_view(line, &flags))
		{
			ft_strlcpy(map[*map_lines], line, ft_strlen(line));
			printf("achei essa view no mapa %s>\n", map[*map_lines]);
			(*map_lines)++;
		}
		else if (line[0] != '\0' && line[0] != '\n')
			{
				(*map_lines)++;
				printf("achei dados errados>\n"); //precisa tirar comentarios
			}
			else
				printf("achei linha em branco>\n");
		free(line);
		if (*map_lines < 6)
			line = get_next_line(fd);
	}
	if (flags == 111111) /*se os 6 argumentos sao diferentes ok*/ 
	    return (1);
    return (0);
}

int	is_valid_char(char c)
{
	return (c == ' ' || c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

int	is_valid_map_line(const char *line)
{
	int	i;
	int	inside_block;

	i = 0;
	inside_block = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '1')
			inside_block = 1;
		else if (line[i] == ' ')
		{
			if (inside_block)
			{
				while (line[i] == ' ')
					i++;
				if (line[i] != '1' && line[i] != '\0')
					return (0);
				i--;
			}
		}
		else if (!is_valid_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_map_closed(char map[MAX_MAP_LINES][MAX_LINE], int map_lines)
{
	int	i;
	int	j;

	i = 0;
	while (map[6][i] != '\0')
	{
		if (map[6][i] != '1' && map[6][i] != ' ')
			return (0);
		i++;
	}
	i = 0;
	while (map[map_lines - 1][i] != '\0')
	{
		if (map[map_lines - 1][i] != '1' && map[map_lines - 1][i] != ' ')
			return (0);
		i++;
	}
	i = 6;
	while (i < map_lines - 1)
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] != '1')
			return (0);
		j = strlen(map[i]) - 1;
		while (j >= 0 && map[i][j] == ' ')
			j--;
		if (j >= 0 && map[i][j] != '1')
			return (0);
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '0')
			{
				if ((i > 0 && j >= (int)strlen(map[i - 1])) ||
					(i < map_lines - 1 && j >= (int)strlen(map[i + 1])))
					return (0);
				if ((i > 0 && (map[i - 1][j] == ' ' || map[i - 1][j] == '\0')) ||
					(i < map_lines - 1 && (map[i + 1][j] == ' ' || map[i + 1][j] == '\0')) ||
					(j > 0 && map[i][j - 1] == ' ') ||
					(map[i][j + 1] != '\0' && map[i][j + 1] == ' '))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	charge_map(int fd, char map[MAX_MAP_LINES][MAX_LINE], int *map_lines)
{
	char	*line;

	line = get_next_line(fd);
	while ((line) && (line[0] == '\n'))
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		ft_strlcpy(map[*map_lines], line, ft_strlen(line));
		(*map_lines)++;
		free(line);
		line = get_next_line(fd);
	}
}

int mapvalid(int fd, char map[MAX_MAP_LINES][MAX_LINE], int *map_lines)
{
	int	i;
	
	*map_lines = 0;
	if (!parse_map(fd, map, map_lines))
	{
		fprintf(stderr, "Error: Invalid Textures or Colors\n");
		return (0);
	}
	charge_map(fd, map, map_lines);
	i = 6;
	while (i < *map_lines)
	{
		if (!is_valid_map_line(map[i]))
		{
			printf("Error: Map Line %d Invalid\n", ((i - 6) + 1));
			return (0);
		}
		i++;
	}
	if (!is_map_closed(map, *map_lines))
	{
		printf("Error: Map is not Closed\n");
		return (0);
	}
	printf("Mapa válido e fechado!\n");   // tirar depois de testado
	return (1);
}	