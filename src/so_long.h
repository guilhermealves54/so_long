/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:19:18 by gribeiro          #+#    #+#             */
/*   Updated: 2025/01/28 15:50:21 by gribeiro         ###   ########.fr       */
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

typedef struct s_map
{
	char	**map;
}	t_map;

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

// Map creation
t_map	*create_map(t_map	*map, char *tmp_map);

#endif