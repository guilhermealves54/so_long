#include "so_long.h"

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
	while ((r = read (fd, buff, 10)) > 0)
	{
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

static	int freemem(t_map *map, int n)
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

static int	line_size(char *tmp_map)
{
	int		i;

	i = 0;
	while (tmp_map[i] != '\0' && tmp_map[i] != '\n')
		i++;
	return (i);
}

static t_map *fill_map(t_map *map, char *tmp_map)
{
	int		i;
	int		n;
	int		l;

	i = 0;
	n = 0;
	while (tmp_map[i] != '\0')
	{
		map->map[n] = malloc (line_size (&tmp_map[i]) * sizeof(char));
		if (!map->map[n])
			return (freemem(map, 3), NULL);
		l = 0;
		while (tmp_map[i] != '\0' && tmp_map[i] != '\n')
		{
			map->map[n][l] = tmp_map[i];
			i++;
			l++;
		}
		map->map[n][l] = '\0';
		n++;
		i++;
	}
	return (map);
}

static t_map	*create_map(t_map	*map, char *tmp_map)
{
	int		i;
	int		l;

	i = 0;
	l = 0;
	map = malloc (sizeof(t_map));
	if (!map)
		return (freemem(map, 1), NULL);
	while (tmp_map[i] != '\0')
	{
		if (tmp_map[i] == '\n')
			l++;
		i++;
	}
	map->map = malloc (l * sizeof(char*));
	if (!map->map)
		return (freemem(map, 2), NULL);
	while (l >= 0)
		map->map[l--] = NULL;
	i = 0;
	fill_map (map, tmp_map);
	return (map);
}

static int	check_clsdret(t_map *map)
{
	size_t	i;
	int		n;

	n = 0;
	while (map->map[n])
	{
		i = 0;
		while(map->map[n][i] != '\0')
			i++;
		if (i != ft_strlen (map->map[0]))
			return (0);
		n++;
	}
	n--;
	i = 0;
	while (map->map[n][i] && map->map[n][i] == '1' && map->map[0][i] == '1')
		i++;
	if (i != ft_strlen (map->map[0]))
		return (0);
	while (n >= 0 && map->map[n][0] == '1' && map->map[n][i - 1] == '1')
		n--;
	if (n + 1 != 0)
		return (0);
	return (1);
}

static	int valid_map(t_map *map)
{
	// check if map is rectangular and closed
	if (!check_clsdret (map))
		return (0);
	
	// check if there is only one P, only one E and at leas 1 C
	// check if there is a way out
	return (1);
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
	int n = 0;
	while (map->map[n])
		printf ("%s\n", map->map[n++]);
	free (tmp_map);
	printf ("%i\n", valid_map (map));
	if (!valid_map (map))
		return (freemem(map, 3), 0);
	return (freemem(map, 3), 0);
}
