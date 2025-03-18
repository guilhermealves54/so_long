/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:19:05 by gribeiro          #+#    #+#             */
/*   Updated: 2025/03/18 16:30:31 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	put_pec(t_map *map, t_gm *gm)
{
	int		x;
	int		y;
	int		sz;

	findplayer (map, &x, &y);
	sz = 75;
	gm->plr = mlx_xpm_file_to_image(gm->mlx, "assets/P.xpm", &sz, &sz);
	gm->pll = mlx_xpm_file_to_image(gm->mlx, "assets/P-2.xpm", &sz, &sz);
	gm->colec = mlx_xpm_file_to_image(gm->mlx, "assets/C.xpm", &sz, &sz);
	gm->exit = mlx_xpm_file_to_image(gm->mlx, "assets/E.xpm", &sz, &sz);
	if (!gm->plr || !gm->pll || !gm->colec || !gm->exit)
		return (0);
	mlx_put_image_to_window(gm->mlx, gm->wn, gm->plr, y * 75, x * 75);
	put_colec(map, gm);
	findexit (map, &x, &y);
	mlx_put_image_to_window(gm->mlx, gm->wn, gm->exit, y * 75, x * 75);
	return (1);
}

int	draw_map(t_map *map, t_gm *gm)
{
	gm->exit = NULL;
	gm->plr = NULL;
	gm->pll = NULL;
	gm->colec = NULL;
	gm->lake = NULL;
	gm->wall = NULL;
	gm->wall1 = NULL;
	if (!draw_bg (map, gm))
		return (freemlx (gm, 0), 0);
	if (!put_pec (map, gm))
		return (freemlx (gm, 0), 0);
	return (1);
}

void	put_bgimg(t_map *map, t_gm *gm)
{
	int		row;
	int		col;
	int		x;
	int		y;

	row = 0;
	while (map->map[row])
	{
		col = 0;
		while (map->map[row][col])
		{
			x = col * 75;
			y = row * 75;
			if (map->map[row + 1] != NULL && map->map[row][col] == '1'
				&& map->map[row + 1][col] != '1')
				mlx_put_image_to_window(gm->mlx, gm->wn, gm->wall1, x, y);
			else if (map->map[row][col] == '1')
				mlx_put_image_to_window(gm->mlx, gm->wn, gm->wall, x, y);
			else
				mlx_put_image_to_window(gm->mlx, gm->wn, gm->lake, x, y);
			col++;
		}
		x = 0;
		row++;
	}
}

int	draw_bg(t_map *map, t_gm *gm)
{
	int		sz;

	sz = 75;
	gm->lake = mlx_xpm_file_to_image(gm->mlx, "assets/0.xpm", &sz, &sz);
	gm->wall = mlx_xpm_file_to_image(gm->mlx, "assets/1.xpm", &sz, &sz);
	gm->wall1 = mlx_xpm_file_to_image(gm->mlx, "assets/1-2.xpm", &sz, &sz);
	if (!gm->lake || !gm->wall || !gm->wall1)
		return (0);
	put_bgimg (map, gm);
	return (1);
}

void	put_colec(t_map *map, t_gm *gm)
{
	int		n;
	int		i;

	n = 0;
	while (map->map[n])
	{
		i = 0;
		while (map->map[n][i] != '\0')
		{
			if (map->map[n][i] == 'C')
				mlx_put_image_to_window(gm->mlx, gm->wn,
					gm->colec, i * 75, n * 75);
			i++;
		}
		n++;
	}
}
