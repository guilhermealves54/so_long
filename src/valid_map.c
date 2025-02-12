/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:19:49 by gribeiro          #+#    #+#             */
/*   Updated: 2025/02/12 23:15:25 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	cnt_colec(t_map *map);
static int	check_clsdret(t_map *map);
static int	check_symbols(t_map *map, int *pec);

int	valid_map(t_map *map)
{
	int		pec[3];

	pec[0] = 0;
	pec[1] = 0;
	pec[2] = 0;
	map->check_c = 0;
	map->check_e = 0;
	map->c_nbr = cnt_colec (map);
	if (!check_clsdret (map))
		return (0);
	if (!check_symbols (map, pec))
		return (0);
	if (!check_wayout (map))
		return (0);
	return (1);
}

static int	cnt_colec(t_map *map)
{
	int	n;
	int	i;
	int	res;

	res = 0;
	n = 0;
	while (map->map[n])
	{
		i = 0;
		while (map->map[n][i])
		{
			if (map->map[n][i] == 'C')
				res++;
			i++;
		}
		n++;
	}
	return (res);
}

static int	check_clsdret(t_map *map)
{
	size_t	i;
	int		n;

	n = 0;
	while (map->map[n])
	{
		i = 0;
		while (map->map[n][i] != '\0')
			i++;
		if (i != ft_strlen (map->map[0]))
			return (0);
		n++;
	}
	n--;
	i = 0;
	while (map->map[n][i] && map->map[n][i] == '1' && map->map[0][i] == '1')
		i++;
	if (i != ft_strlen (map->map[0]))
		return (0);
	while (n >= 0 && map->map[n][0] == '1' && map->map[n][i - 1] == '1')
		n--;
	if (n + 1 != 0)
		return (0);
	return (1);
}

static int	check_symbols(t_map *map, int *pec)
{
	int		i;
	int		n;

	n = 0;
	while (map->map[n])
	{
		i = 0;
		while (map->map[n][i] != '\0')
		{
			if (map->map[n][i] == 'P')
				pec[0]++;
			else if (map->map[n][i] == 'E')
				pec[1]++;
			else if (map->map[n][i] == 'C')
				pec[2]++;
			else if (map->map[n][i] != '1' && map->map[n][i] != '0')
				return (0);
			i++;
		}
		n++;
	}
	if (pec[0] != 1 || pec[1] != 1 || pec[2] < 1)
		return (0);
	return (1);
}
