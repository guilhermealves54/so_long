/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:19:08 by gribeiro          #+#    #+#             */
/*   Updated: 2025/03/19 16:50:55 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ber_filetype(char **argv);
static char	*read_map(char **argv, char *tmp_map, int fd);
void		gmloop(t_gm *gm);
int			open_gi(t_map *map);

int	main(int argc, char **argv)
{
	t_map	*map;
	char	*tmp_map;
	int		fd;

	map = NULL;
	tmp_map = NULL;
	fd = -1;
	if (argc != 2 || argv[1][0] == '\0')
		return (write (2, "Error\nMap not found.\n", 21), 1);
	if (!ber_filetype (argv))
		return (write (2, "Error\nMap not found.\n", 21), 1);
	if (!chk_assets ())
		return (write (2, "Error\nAssets missing.\n", 22), 1);
	tmp_map = read_map (argv, tmp_map, fd);
	if (!tmp_map || tmp_map[0] != '1')
		return (write (2, "Error\nInvalid map.\n", 19), 1);
	map = create_map (map, tmp_map);
	if (!map)
		return (write (2, "Error\n", 6), free (tmp_map), 1);
	free (tmp_map);
	if (!valid_map (map))
		return (write (2, "Error\nInvalid map.\n", 19), freemem(map, 3), 1);
	if (!open_gi(map))
		return (write (2, "Error\nError loading graphics.\n", 30), 1);
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

static char	*read_map(char **argv, char *tmp_map, int fd)
{
	char	buff[11];
	char	*temp;
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
		if (r < 0)
			return (free (tmp_map), NULL);
		buff[r] = '\0';
		temp = NULL;
		temp = tmp_map;
		tmp_map = ft_strjoin (tmp_map, buff);
		if (!tmp_map)
			return (NULL);
		free (temp);
	}
	return (close (fd), tmp_map);
}

void	gmloop(t_gm *gm)
{
	mlx_hook (gm->wn, 17, 0, freemlx, gm);
	mlx_hook (gm->wn, 2, 1L << 0, key_press, gm);
	mlx_loop (gm->mlx);
}

int	open_gi(t_map *map)
{
	t_gm	gm;
	int		w;
	int		h;
	int		i;

	i = 0;
	w = 0;
	gm.map = map;
	map->col = 0;
	map->v_exit = 0;
	while (map->map[0][i++])
		w++;
	i = 0;
	h = 0;
	while (map->map[i++])
		h++;
	gm.mlx = mlx_init();
	gm.wn = mlx_new_window (gm.mlx, w * 75, h * 75, "So_Long");
	if (!draw_map (map, &gm))
		return (0);
	return (gmloop (&gm), 1);
}
