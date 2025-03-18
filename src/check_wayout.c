/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wayout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:19:27 by gribeiro          #+#    #+#             */
/*   Updated: 2025/03/18 15:43:20 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void		findplayer(t_map *map, int *x, int *y);
static char	**fillvisitd(t_map *map, char **visitd);
static int	explore(t_map *map, int x, int y, char **visitd);

static int	allc_visitd(t_map *map, char **visitd)
{
	int		n;

	n = 0;
	while (map->map[n])
	{
		visitd[n] = calloc ((ft_strlen (map->map[n])) + 1, sizeof (char));
		if (!visitd[n])
			return (freevisitd (visitd), 0);
		visitd[n][ft_strlen (map->map[n])] = '\0';
		n++;
	}
	return (1);
}

int	check_wayout(t_map *map)
{
	int		x;
	int		y;
	char	**visitd;
	int		n;

	findplayer(map, &x, &y);
	n = 0;
	while (map->map[n])
		n++;
	visitd = calloc ((n + 1), sizeof (char *));
	if (!visitd)
		return (0);
	visitd[n] = NULL;
	if (!allc_visitd (map, visitd))
		return (0);
	visitd = fillvisitd (map, visitd);
	if (!explore (map, x, y, visitd))
		return (freevisitd (visitd), 0);
	return (freevisitd (visitd), 1);
}

void	findplayer(t_map *map, int *x, int *y)
{
	int		n;
	int		i;

	n = 0;
	while (map->map[n])
	{
		i = 0;
		while (map->map[n][i] != '\0')
		{
			if (map->map[n][i] == 'P')
			{
				*x = n;
				*y = i;
			}
			i++;
		}
		n++;
	}
}

static char	**fillvisitd(t_map *map, char **visitd)
{
	int		n;
	int		i;

	n = 0;
	while (map->map[n])
	{
		i = 0;
		while (map->map[n][i])
		{
			if (map->map[n][i] == '1')
				visitd[n][i] = '1';
			else
				visitd[n][i] = '0';
			i++;
		}
		n++;
	}
	return (visitd);
}

static int	explore(t_map *map, int x, int y, char **visitd)
{
	if (map->map[x][y] == 'C')
		map->check_c += 1;
	if (map->map[x][y] == 'E')
		map->check_e = 1;
	if (map->check_e == 1 && map->check_c == map->c_nbr)
		return (1);
	visitd[x][y] = '1';
	if (visitd[x + 1][y] != '1' && explore (map, x + 1, y, visitd))
		return (1);
	if (visitd[x][y + 1] != '1' && explore (map, x, y + 1, visitd))
		return (1);
	if (visitd[x - 1][y] != '1' && explore (map, x - 1, y, visitd))
		return (1);
	if (visitd[x][y - 1] != '1' && explore (map, x, y - 1, visitd))
		return (1);
	return (0);
}
