/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:19:08 by gribeiro          #+#    #+#             */
/*   Updated: 2025/03/18 16:24:41 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ber_filetype(char **argv);
static char	*read_map(char **argv, char *tmp_map);
void		gmloop(t_gm *gm);
int			open_gi(t_map *map);

int	main(int argc, char **argv)
{
	t_map	*map;
	char	*tmp_map;

	map = NULL;
	tmp_map = NULL;
	if (argc != 2 || argv[1][0] == '\0')
		return (ft_printf ("Map not found.\n"), 1);
	if (!ber_filetype (argv))
		return (ft_printf ("Map not found.\n"), 1);
	tmp_map = read_map (argv, tmp_map);
	if (!tmp_map)
		return (1);
	map = create_map (map, tmp_map);
	if (!map)
		return (free (tmp_map), 0);
	free (tmp_map);
	if (!valid_map (map))
	{
		ft_printf ("Invalid map.\n");
		return (freemem(map, 3), 1);
	}
	if (!open_gi(map))
		return (ft_printf ("Error loading graphics.\n"), 1);
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
	gmloop (&gm);
	return (0);
}
