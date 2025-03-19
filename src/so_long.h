/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:19:18 by gribeiro          #+#    #+#             */
/*   Updated: 2025/03/19 15:50:30 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx/mlx.h"
# include "../ft_printf/ft_printf.h"

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

typedef struct s_gm
{
	void	*mlx;
	void	*wn;
	void	*lake;
	void	*wall;
	void	*wall1;
	void	*plr;
	void	*pll;
	void	*exit;
	void	*colec;
	t_map	*map;
}	t_gm;

//	Lib
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);

// Memory Cleanup
int		freemem(t_map *map, int n);
void	freevisitd(char **visitd);
int		freemlx(t_gm *gm, int out);

// Map Validation
int		check_wayout(t_map *map);
int		valid_map(t_map *map);
void	findplayer(t_map *map, int *x, int *y);
void	findexit(t_map *map, int *x, int *y);

// Map creation
t_map	*create_map(t_map	*map, char *tmp_map);

// Graphics & gmplay
int		mov_left(t_map *map, t_gm *gm, int x, int y);
int		mov_right(t_map *map, t_gm *gm, int x, int y);
int		mov_down(t_map *map, t_gm *gm, int x, int y);
int		mov_up(t_map *map, t_gm *gm, int x, int y);
int		put_pec(t_map *map, t_gm *gm);
int		draw_map(t_map *map, t_gm *gm);
void	put_bgimg(t_map *map, t_gm *gm);
int		draw_bg(t_map *map, t_gm *gm);
void	put_colec(t_map *map, t_gm *gm);
int		key_press(int keycode, t_gm *gm);
void	mov_player(t_gm *gm, int key);
int		chk_assets(void);

#endif