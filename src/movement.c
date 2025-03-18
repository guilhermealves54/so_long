/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:19:15 by gribeiro          #+#    #+#             */
/*   Updated: 2025/03/18 16:22:11 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	mov_up(t_map *map, t_gm *gm, int x, int y)
{
	if (map->map[x - 1][y] == '0')
	{
		map->map[x - 1][y] = 'P';
		map->map[x][y] = '0';
		mlx_put_image_to_window(gm->mlx, gm->wn, gm->plr, y * 75, (x - 1) * 75);
		mlx_put_image_to_window(gm->mlx, gm->wn, gm->lake, y * 75, x * 75);
		return (1);
	}
	else if (map->map[x - 1][y] == 'C')
	{
		map->map[x - 1][y] = 'P';
		map->map[x][y] = '0';
		mlx_put_image_to_window(gm->mlx, gm->wn, gm->plr, y * 75, (x - 1) * 75);
		mlx_put_image_to_window(gm->mlx, gm->wn, gm->lake, y * 75, x * 75);
		map->col += 1;
		if (map->col == map->c_nbr)
			map->v_exit = 1;
		return (1);
	}
	else if (map->map[x - 1][y] == 'E')
	{
		if (map->v_exit == 1)
			freemlx(gm, 1);
	}
	return (0);
}

int	mov_down(t_map *map, t_gm *gm, int x, int y)
{
	if (map->map[x + 1][y] == '0')
	{
		map->map[x + 1][y] = 'P';
		map->map[x][y] = '0';
		mlx_put_image_to_window(gm->mlx, gm->wn, gm->plr, y * 75, (x + 1) * 75);
		mlx_put_image_to_window(gm->mlx, gm->wn, gm->lake, y * 75, x * 75);
		return (1);
	}
	else if (map->map[x + 1][y] == 'C')
	{
		map->map[x + 1][y] = 'P';
		map->map[x][y] = '0';
		mlx_put_image_to_window(gm->mlx, gm->wn, gm->plr, y * 75, (x + 1) * 75);
		mlx_put_image_to_window(gm->mlx, gm->wn, gm->lake, y * 75, x * 75);
		map->col += 1;
		if (map->col == map->c_nbr)
			map->v_exit = 1;
		return (1);
	}
	else if (map->map[x + 1][y] == 'E')
	{
		if (map->v_exit == 1)
			freemlx(gm, 1);
	}
	return (0);
}

int	mov_right(t_map *map, t_gm *gm, int x, int y)
{
	if (map->map[x][y + 1] == '0')
	{
		map->map[x][y + 1] = 'P';
		map->map[x][y] = '0';
		mlx_put_image_to_window(gm->mlx, gm->wn, gm->plr, (y + 1) * 75, x * 75);
		mlx_put_image_to_window(gm->mlx, gm->wn, gm->lake, y * 75, x * 75);
		return (1);
	}
	else if (map->map[x][y + 1] == 'C')
	{
		map->map[x][y + 1] = 'P';
		map->map[x][y] = '0';
		mlx_put_image_to_window(gm->mlx, gm->wn, gm->plr, (y + 1) * 75, x * 75);
		mlx_put_image_to_window(gm->mlx, gm->wn, gm->lake, y * 75, x * 75);
		map->col += 1;
		if (map->col == map->c_nbr)
			map->v_exit = 1;
		return (1);
	}
	else if (map->map[x][y + 1] == 'E')
	{
		if (map->v_exit == 1)
			freemlx(gm, 1);
	}
	return (0);
}

int	mov_left(t_map *map, t_gm *gm, int x, int y)
{
	if (map->map[x][y - 1] == '0')
	{
		map->map[x][y - 1] = 'P';
		map->map[x][y] = '0';
		mlx_put_image_to_window(gm->mlx, gm->wn, gm->pll, (y - 1) * 75, x * 75);
		mlx_put_image_to_window(gm->mlx, gm->wn, gm->lake, y * 75, x * 75);
		return (1);
	}
	else if (map->map[x][y - 1] == 'C')
	{
		map->map[x][y - 1] = 'P';
		map->map[x][y] = '0';
		mlx_put_image_to_window(gm->mlx, gm->wn, gm->pll, (y - 1) * 75, x * 75);
		mlx_put_image_to_window(gm->mlx, gm->wn, gm->lake, y * 75, x * 75);
		map->col += 1;
		if (map->col == map->c_nbr)
			map->v_exit = 1;
		return (1);
	}
	else if (map->map[x][y - 1] == 'E')
	{
		if (map->v_exit == 1)
			freemlx(gm, 1);
	}
	return (0);
}
