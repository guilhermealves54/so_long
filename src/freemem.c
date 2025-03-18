/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freemem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:19:33 by gribeiro          #+#    #+#             */
/*   Updated: 2025/03/18 16:23:52 by gribeiro         ###   ########.fr       */
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

int	freemlx(t_gm *gm, int out)
{
	t_map	*map;

	map = gm->map;
	if (gm->exit)
		mlx_destroy_image(gm->mlx, gm->exit);
	if (gm->plr)
		mlx_destroy_image(gm->mlx, gm->plr);
	if (gm->pll)
		mlx_destroy_image(gm->mlx, gm->pll);
	if (gm->colec)
		mlx_destroy_image(gm->mlx, gm->colec);
	if (gm->lake)
		mlx_destroy_image(gm->mlx, gm->lake);
	if (gm->wall)
		mlx_destroy_image(gm->mlx, gm->wall);
	if (gm->wall1)
		mlx_destroy_image(gm->mlx, gm->wall1);
	if (gm->wn)
		mlx_destroy_window(gm->mlx, gm->wn);
	mlx_destroy_display(gm->mlx);
	free(gm->mlx);
	freemem (map, 3);
	if (out)
		exit(0);
	return (0);
}
