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

static int	check_symbols(t_map *map, int *pec)
{
	int		i;
	int		n;

	n = 0;
	while (map->map[n])
	{
		i = 0;
		while (map->map[n][i] != '\0')
		{
			if (map->map[n][i] == 'P')
				pec[0]++;
			else if (map->map[n][i] == 'E')
				pec[1]++;
			else if (map->map[n][i] == 'C')
				pec[2]++;
			i++;
		}
		n++;
	}
	if (pec[0] != 1 || pec[1] != 1 || pec[2] < 1)
		return (0);
	return (1);
}
static int	*findplayer(t_map *map, int *pcord)
{
	int		n;
	int		i;

	n = 0;
	while (map->map[n])
	{
		i = 0;
		while (map->map[n][i] != '\0')
		{
			if (map->map[n][i] == 'P')
			{
				pcord[0] = n;
				pcord[1] = i;
			}
			i++;
		}
		n++;
	}
	return (pcord);
}

static void	freevisitd(int **visitd)
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

static int	**fillvisitd (t_map *map, int **visitd)
{
	int		n;
	int		i;

	n = 0;
	while (map->map[n])
	{
		i = 0;
		while (map->map[n][i])
		{
			visitd[n][i] = 0;
			i++;
		}
		n++;
	}
	return (visitd);
}

static int	chck_path (t_map *map, int *pcord, int **visitd)
{
	return (1);
}

static int	check_wayout(t_map *map)
{
	int		pcord[2];
	int		**visitd;
	int		n;

	findplayer(map, pcord);
	n = 0;
	while (map->map[n])
		n++;
	visitd = malloc ((n + 1) * sizeof (int *));
	if (!visitd)
		return (0);
	visitd[n] = NULL;
	n = 0;
	while (visitd[n])
	{
		visitd[n] = malloc ((ft_strlen (map->map[n])) * sizeof (int));
		if (!visitd[n])
			return (freevisitd (visitd), 0);
		n++;
	}
	visitd = fillvisitd (map, visitd);
	if (!chck_path (map, pcord, visitd))
		return (freevisitd (visitd), 0);


	int i = 0;
	n = 0;
	while (map->map[n])
	{
		i = 0;
		while (map->map[n][i])
			printf ("%i", visitd[n][i++]);
		n++;
		printf ("\n");
	}
	
	return (freevisitd (visitd), 1);
}

static int	valid_map(t_map *map)
{
	int		pec[3];

	pec[0] = 0; //p
	pec[1] = 0; //e
	pec[2] = 0; //c
	if (!check_clsdret (map))
		return (0);
	if (!check_symbols (map, pec))
		return (0);
	if (!check_wayout (map))
		return (0);
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
