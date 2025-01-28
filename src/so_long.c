/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:19:08 by gribeiro          #+#    #+#             */
/*   Updated: 2025/01/28 16:42:39 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ber_filetype(char **argv);
static char	*read_map(char **argv, char *tmp_map);

int	draw_map(t_map *map, void *mlx)
{
	int		row;
	int		col;

	row = 0;
	while (map->map[row])
	{
		col = 0;
		while (map->map[row][col])
		{
			if (map->map[row][col] == '1')
			
			if (map->map[row][col] == '0' || map->map[row][col] == 'E')

			if (map->map[row][col] == 'P')

			if (map->map[row][col] == 'C')
			
			col++;
		}
		row++;
	}
}

void	op_gui(t_map *map)
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	int		i;

	i = 0;
	width = 0;
	while (map->map[0][i++])
		width++;
	i = 0;
	height = 0;
	while (map->map[i++])
		height++;
	mlx = mlx_init();
	win = mlx_new_window (mlx, width * 100, height * 100, "So_Long");
	mlx_loop (mlx);
	draw_map (map, mlx);
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
	op_gui(map);
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
