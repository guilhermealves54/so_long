/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:19:08 by gribeiro          #+#    #+#             */
/*   Updated: 2025/01/29 23:56:04 by gribeiro         ###   ########.fr       */
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
			x = col * 100;
			y = row * 100;
			if (map->map[row + 1] != NULL && map->map[row][col] == '1' 
				&& map->map[row + 1][col] != '1')
				mlx_put_image_to_window(gm->mlx, gm->win, map->wall_s, x, y);
			else if (map->map[row][col] == '1')
				mlx_put_image_to_window(gm->mlx, gm->win, map->wall, x, y);
			else
				mlx_put_image_to_window(gm->mlx, gm->win, map->lake, x, y);
			col++;
		}
		x = 0;
		row++;
	}
}

int	draw_bg(t_map *map, t_game *game)
{
	int		sz;

	sz = 100;
	map->lake = mlx_xpm_file_to_image(game->mlx, "assets/0.xpm", &sz, &sz);
	map->wall = mlx_xpm_file_to_image(game->mlx, "assets/1.xpm", &sz, &sz);
	map->wall_s = mlx_xpm_file_to_image(game->mlx, "assets/1-2.xpm", &sz, &sz);
	if (!map->lake || !map->wall || !map->wall_s)
		return (0);
	put_bgimg (map, game);
	game->free = 2;
	return (1);
}

void	findcolec (t_map *map, int *x, int *y)
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
			{
				*x = n;
				*y = i;
			}
			i++;
		}
		n++;
	}
}

int	put_pc(t_map *map, t_game *game)
{
	int		x;
	int		y;
	int		sz;

	findplayer (map, &x, &y);
	sz = 100;
	map->player = mlx_xpm_file_to_image(game->mlx, "assets/P.xpm", &sz, &sz);
	map->colec = mlx_xpm_file_to_image(game->mlx, "assets/C.xpm", &sz, &sz);
	if (!map->player || !map->colec)
		return (0);
	game->free = 3;
	mlx_put_image_to_window(game->mlx, game->win, map->player, y*100, x*100);
	printf ("%i, %i", x, y);
	findcolec (map, &x, &y);
	printf ("%i, %i", x, y);
	mlx_put_image_to_window(game->mlx, game->win, map->colec, y*100, x*100);
	return (1);
}

int	freemlx(t_map *map, t_game *game)
{
	if (game->free == 4)
		mlx_destroy_image(game->mlx, map->exit);
	if (game->free >= 3)
	{
		mlx_destroy_image(game->mlx, map->player);
		mlx_destroy_image(game->mlx, map->colec);
	}
	if (game->free >= 2)
	{
		mlx_destroy_image(game->mlx, map->lake);
		mlx_destroy_image(game->mlx, map->wall);
		mlx_destroy_image(game->mlx, map->wall_s);
	}
	mlx_destroy_window(game->mlx, game->win);
}

int	draw_map(t_map *map, t_game *game)
{
	if (!draw_bg (map, game))
		return (freemlx (map, game), 0);
	if (!put_pc (map, game))
		return (freemlx (map, game), 0);
	return (1);
}

int key_press(int keycode, t_map *map, t_game *game)
{
    if (keycode == 65307)
    {
        freemlx(map, game);
    }
    return (0);
}

void	gameloop(t_map *map, t_game *game)
{
	mlx_hook (game->win, 17, 0, freemlx, &game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	printf("%i\n", game->free);
	mlx_loop (game->mlx);
}

int	open_gui(t_map *map)
{
	t_game	*game;
	int		w;
	int		h;
	int		i;

	game = malloc (sizeof(t_game));
	if (!game)
		return (0);
	i = 0;
	w = 0;
	while (map->map[0][i++])
		w++;
	i = 0;
	h = 0;
	while (map->map[i++])
		h++;
	game->mlx = mlx_init();
	game->win = mlx_new_window (game->mlx, w * 100, h * 100, "So_Long");
	if (!draw_map (map, game))
		return (0);
	game->free = 1;
	gameloop (map, game);
	free (game);
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
