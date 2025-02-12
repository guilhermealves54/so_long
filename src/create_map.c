/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:19:31 by gribeiro          #+#    #+#             */
/*   Updated: 2025/02/12 22:49:28 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int		line_size(char *tmp_map);
static t_map	*fill_map(t_map *map, char *tmp_map);

t_map	*create_map(t_map	*map, char *tmp_map)
{
	int		i;
	int		l;

	i = 0;
	l = 0;
	map = calloc (1, sizeof(t_map));
	if (!map)
		return (freemem(map, 1), NULL);
	while (tmp_map[i] != '\0')
	{
		if (tmp_map[i] == '\n')
			l++;
		i++;
	}
	if (i > 0 && tmp_map[i] == '\0' && tmp_map[i - 1] != '\n')
		l++;
	map->map = calloc ((l + 1), sizeof(char *));
	if (!map->map)
		return (freemem(map, 2), NULL);
	while (l >= 0)
		map->map[l--] = NULL;
	i = 0;
	fill_map (map, tmp_map);
	return (map);
}

static int	line_size(char *tmp_map)
{
	int		i;

	i = 0;
	while (tmp_map[i] != '\0' && tmp_map[i] != '\n')
		i++;
	return (i);
}

static t_map	*fill_map(t_map *map, char *tmp_map)
{
	int		i;
	int		n;
	int		l;

	i = 0;
	n = 0;
	while (tmp_map[i] != '\0')
	{
		map->map[n] = calloc (line_size (&tmp_map[i]) + 1, sizeof(char));
		if (!map->map[n])
			return (freemem(map, 3), NULL);
		l = 0;
		while (tmp_map[i] != '\0' && tmp_map[i] != '\n')
		{
			map->map[n][l] = tmp_map[i];
			i++;
			l++;
		}
		map->map[n][l] = '\0';
		n++;
		if (tmp_map[i] != '\0')
			i++;
	}
	return (map);
}
