/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:19:18 by gribeiro          #+#    #+#             */
/*   Updated: 2025/02/12 03:16:00 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx/mlx.h"
# include <stdio.h> // apagar

// Structs
typedef struct s_map
{
	char	**map;
	int		col;
	int		v_exit;
	int		check_c;
	int		c_nbr;
	int		check_e;
	int		movs;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*lake;
	void	*wall;
	void	*wall1;
	void	*plr;
	void	*pll;
	void	*exit;
	void	*colec;
	t_map	*map;
}	t_game;

//	Lib
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);

// Memory Cleanup
int		freemem(t_map *map, int n);
void	freevisitd(char **visitd);

// Map Validation
int		check_wayout(t_map *map);
int		valid_map(t_map *map);
void	findplayer(t_map *map, int *x, int *y);

// Map creation
t_map	*create_map(t_map	*map, char *tmp_map);

#endif