/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:19:08 by gribeiro          #+#    #+#             */
/*   Updated: 2025/02/12 22:18:55 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ber_filetype(char **argv);
static char	*read_map(char **argv, char *tmp_map);

void	put_bgimg(t_map *map, t_game *gm)
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
				mlx_put_image_to_window(gm->mlx, gm->win, gm->wall1, x, y);
			else if (map->map[row][col] == '1')
				mlx_put_image_to_window(gm->mlx, gm->win, gm->wall, x, y);
			else
				mlx_put_image_to_window(gm->mlx, gm->win, gm->lake, x, y);
			col++;
		}
		x = 0;
		row++;
	}
}

int	draw_bg(t_map *map, t_game *game)
{
	int		sz;

	sz = 75;
	game->lake = mlx_xpm_file_to_image(game->mlx, "assets/0.xpm", &sz, &sz);
	game->wall = mlx_xpm_file_to_image(game->mlx, "assets/1.xpm", &sz, &sz);
	game->wall1 = mlx_xpm_file_to_image(game->mlx, "assets/1-2.xpm", &sz, &sz);
	if (!game->lake || !game->wall || !game->wall1)
		return (0);
	put_bgimg (map, game);
	return (1);
}

void	put_colec(t_map *map, t_game *game)
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
				mlx_put_image_to_window(game->mlx, game->win, game->colec, i * 75, n * 75);
			i++;
		}
		n++;
	}
}

void	findexit(t_map *map, int *x, int *y)
{
	int		n;
	int		i;

	n = 0;
	while (map->map[n])
	{
		i = 0;
		while (map->map[n][i] != '\0')
		{
			if (map->map[n][i] == 'E')
			{
				*x = n;
				*y = i;
			}
			i++;
		}
		n++;
	}
}

int	put_pec(t_map *map, t_game *game)
{
	int		x;
	int		y;
	int		sz;

	findplayer (map, &x, &y);
	sz = 75;
	game->plr = mlx_xpm_file_to_image(game->mlx, "assets/P.xpm", &sz, &sz);
	game->pll = mlx_xpm_file_to_image(game->mlx, "assets/P-2.xpm", &sz, &sz);
	game->colec = mlx_xpm_file_to_image(game->mlx, "assets/C.xpm", &sz, &sz);
	game->exit = mlx_xpm_file_to_image(game->mlx, "assets/E.xpm", &sz, &sz);
	if (!game->plr || !game->colec)
		return (0);
	mlx_put_image_to_window(game->mlx, game->win, game->plr, y*75, x*75);
	put_colec(map, game);
	findexit (map, &x, &y);
	mlx_put_image_to_window(game->mlx, game->win, game->exit, y*75, x*75);
	return (1);
}

int	freemlx(t_game *game)
{
	t_map	*map;

	map = game->map;
	if (game->exit)
		mlx_destroy_image(game->mlx, game->exit);
	if (game->plr)
		mlx_destroy_image(game->mlx, game->plr);
	if (game->pll)
		mlx_destroy_image(game->mlx, game->pll);
	if (game->colec)
		mlx_destroy_image(game->mlx, game->colec);
	if (game->lake)
		mlx_destroy_image(game->mlx, game->lake);
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->wall1)
		mlx_destroy_image(game->mlx, game->wall1);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	freemem (map, 3);
	exit(0);
}

int	draw_map(t_map *map, t_game *game)
{
	if (!draw_bg (map, game))
		return (freemlx (game), 0);
	if (!put_pec (map, game))
		return (freemlx (game), 0);
	return (1);
}

int	mov_up(t_map *map, t_game *game, int x, int y)
{
	if (map->map[x - 1][y] == '0')
	{
		map->map[x - 1][y] = 'P';
		map->map[x][y] = '0';
		mlx_put_image_to_window(game->mlx, game->win, game->plr, y * 75, (x - 1) * 75);
		mlx_put_image_to_window(game->mlx, game->win, game->lake, y * 75, x * 75);
		return (1);
	}	
	else if (map->map[x - 1][y] == 'C')
	{
		map->map[x - 1][y] = 'P';
		map->map[x][y] = '0';
		mlx_put_image_to_window(game->mlx, game->win, game->plr, y * 75, (x - 1) * 75);
		mlx_put_image_to_window(game->mlx, game->win, game->lake, y * 75, x * 75);
		map->col += 1;
		if (map->col == map->c_nbr)
			map->v_exit = 1;
		return (1);
	}
	else if (map->map[x - 1][y] == 'E')
	{
		if (map->v_exit == 1)
			freemlx(game);
	}
	return (0);
}

int	mov_down(t_map *map, t_game *game, int x, int y)
{
	if (map->map[x + 1][y] == '0')
	{
		map->map[x + 1][y] = 'P';
		map->map[x][y] = '0';
		mlx_put_image_to_window(game->mlx, game->win, game->plr, y * 75, (x + 1) * 75);
		mlx_put_image_to_window(game->mlx, game->win, game->lake, y * 75, x * 75);
		return (1);
	}	
	else if (map->map[x + 1][y] == 'C')
	{
		map->map[x + 1][y] = 'P';
		map->map[x][y] = '0';
		mlx_put_image_to_window(game->mlx, game->win, game->plr, y * 75, (x + 1) * 75);
		mlx_put_image_to_window(game->mlx, game->win, game->lake, y * 75, x * 75);
		map->col += 1;
		if (map->col == map->c_nbr)
			map->v_exit = 1;
		return (1);
	}
	else if (map->map[x + 1][y] == 'E')
	{
		if (map->v_exit == 1)
			freemlx(game);
	}
	return (0);
}

int	mov_right(t_map *map, t_game *game, int x, int y)
{
	if (map->map[x][y + 1] == '0')
	{
		map->map[x][y + 1] = 'P';
		map->map[x][y] = '0';
		mlx_put_image_to_window(game->mlx, game->win, game->plr, (y + 1) * 75, x * 75);
		mlx_put_image_to_window(game->mlx, game->win, game->lake, y * 75, x * 75);
		return (1);
	}	
	else if (map->map[x][y + 1] == 'C')
	{
		map->map[x][y + 1] = 'P';
		map->map[x][y] = '0';
		mlx_put_image_to_window(game->mlx, game->win, game->plr, (y + 1) * 75, x * 75);
		mlx_put_image_to_window(game->mlx, game->win, game->lake, y * 75, x * 75);
		map->col += 1;
		if (map->col == map->c_nbr)
			map->v_exit = 1;
		return (1);
	}
	else if (map->map[x][y + 1] == 'E')
	{
		if (map->v_exit == 1)
			freemlx(game);
	}
	return (0);
}

int	mov_left(t_map *map, t_game *game, int x, int y)
{
	if (map->map[x][y - 1] == '0')
	{
		map->map[x][y - 1] = 'P';
		map->map[x][y] = '0';
		mlx_put_image_to_window(game->mlx, game->win, game->pll, (y - 1) * 75, x * 75);
		mlx_put_image_to_window(game->mlx, game->win, game->lake, y * 75, x * 75);
		return (1);
	}	
	else if (map->map[x][y - 1] == 'C')
	{
		map->map[x][y - 1] = 'P';
		map->map[x][y] = '0';
		mlx_put_image_to_window(game->mlx, game->win, game->pll, (y - 1) * 75, x * 75);
		mlx_put_image_to_window(game->mlx, game->win, game->lake, y * 75, x * 75);
		map->col += 1;
		if (map->col == map->c_nbr)
			map->v_exit = 1;
		return (1);
	}
	else if (map->map[x][y - 1] == 'E')
	{
		if (map->v_exit == 1)
			freemlx(game);
	}
	return (0);
}

void	mov_player(t_game *game, int key)
{
	int	x;
	int y;
	int	mov_chg;
	t_map	*map;
	
	map = game->map;
	mov_chg = map->movs;
	findplayer (map, &x, &y);
	if (key == 97)
		map->movs += mov_left(map, game, x, y);
	else if (key == 100)
		map->movs += mov_right(map, game, x, y);
	else if (key == 115)
		map->movs += mov_down(map, game, x, y);
	else if (key == 119)
		map->movs += mov_up(map, game, x, y);
	if (map->movs > mov_chg)
		printf ("Number of movements: %i\n", map->movs); //ALTERAR PARA FT_PRINTF.
}

int key_press(int keycode, t_game *game)
{
    if (keycode == 65307)
        freemlx(game);
    if (keycode == 97)
        mov_player(game, 97);
    if (keycode == 100)
        mov_player(game, 100);
    if (keycode == 115)
        mov_player(game, 115);
    if (keycode == 119)
        mov_player(game, 119);
    return (0);
}

void	gameloop(t_game *game)
{
	mlx_hook (game->win, 17, 0, freemlx, game);
	mlx_hook (game->win, 2, 1L << 0, key_press, game);
	mlx_loop (game->mlx);
}

int	open_gui(t_map *map)
{
	t_game	game;
	int		w;
	int		h;
	int		i;

	i = 0;
	w = 0;
	game.map = map;
	map->col = 0;
	map->v_exit = 0;
	while (map->map[0][i++])
		w++;
	i = 0;
	h = 0;
	while (map->map[i++])
		h++;
	game.mlx = mlx_init();
	game.win = mlx_new_window (game.mlx, w * 75, h * 75, "So_Long");
	if (!draw_map (map, &game))
		return (0);
	gameloop (&game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	char	*tmp_map;

	map = NULL;
	tmp_map = NULL;
	if (argc != 2 || argv[1][0] == '\0')
		return (0);
	if (!ber_filetype (argv))
		return (0);
	tmp_map = read_map (argv, tmp_map);
	if (!tmp_map)
		return (0);
	map = create_map (map, tmp_map);
	if (!map)
		return (free (tmp_map), 0);
	free (tmp_map);
	if (!valid_map (map))
		return (freemem(map, 3), 0);
	open_gui(map);	// pode terminar programa aqui
	return (freemem(map, 3), 0);
}

static int	ber_filetype(char **argv)
{
	int		i;

	i = ft_strlen (argv[1]);
	if (ft_strncmp (argv[1] + i - 4, ".ber", 4) != 0)
		return (0);
	return (1);
}

static char	*read_map(char **argv, char *tmp_map)
{
	char	buff[11];
	char	*temp;
	int		fd;
	int		r;

	fd = open (argv[1], O_RDONLY);
	if (fd < 0)
		return (NULL);
	r = 1;
	tmp_map = ft_strdup ("");
	if (!tmp_map)
		return (NULL);
	while (r > 0)
	{
		r = read (fd, buff, 10);
		buff[r] = '\0';
		temp = NULL;
		temp = tmp_map;
		tmp_map = ft_strjoin (tmp_map, buff);
		if (!tmp_map)
			return (NULL);
		free (temp);
	}
	close (fd);
	return (tmp_map);
}
