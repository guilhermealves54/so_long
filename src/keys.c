/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:26:20 by gribeiro          #+#    #+#             */
/*   Updated: 2025/03/18 16:29:00 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int keycode, t_gm *gm)
{
	if (keycode == 65307)
		freemlx(gm, 1);
	if (keycode == 97)
		mov_player(gm, 97);
	if (keycode == 100)
		mov_player(gm, 100);
	if (keycode == 115)
		mov_player(gm, 115);
	if (keycode == 119)
		mov_player(gm, 119);
	return (0);
}

void	mov_player(t_gm *gm, int key)
{
	int		x;
	int		y;
	int		mov_chg;
	t_map	*map;

	map = gm->map;
	mov_chg = map->movs;
	findplayer (map, &x, &y);
	if (key == 97)
		map->movs += mov_left(map, gm, x, y);
	else if (key == 100)
		map->movs += mov_right(map, gm, x, y);
	else if (key == 115)
		map->movs += mov_down(map, gm, x, y);
	else if (key == 119)
		map->movs += mov_up(map, gm, x, y);
	if (map->movs > mov_chg)
		ft_printf ("Number of movements: %i\n", map->movs);
}
