/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freemem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:19:33 by gribeiro          #+#    #+#             */
/*   Updated: 2025/02/11 16:59:47 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	freemem(t_map *map, int n)
{
	int		i;

	if (!map)
		return (0);
	if (n >= 3 && map->map)
	{
		i = 0;
		while (map->map[i])
		{
			free(map->map[i]);
			i++;
		}
	}
	if (n >= 2 && map->map)
		free(map->map);
	free(map);
	return (0);
}

void	freevisitd(char **visitd)
{
	int		n;

	n = 0;
	while (visitd[n])
	{
		free (visitd[n]);
		n++;
	}
	free (visitd);
}
