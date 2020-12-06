/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 11:01:45 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/06 10:10:17 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <stdbool.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include "../get_next_line/get_next_line.h"

#define PI 3.14159
#define MAP_BUF_SIZE 64
#define TILE_SIZE 32
#define ERROR -1
#define SUCCESS 1

typedef struct	s_img {
	void *img_ptr;
	char *addr;
	int bpp;
	int len;
	int endian;
}				t_img;

typedef struct	s_pl
{
	double	x;
	double	y;
	char	spawn_direction;//error case
	int		turn_direction;//-1 if left, 1 if right
	int		walk_direction;//-1 if back, 1 if front
	double	rotation_angle;
	double	move_speed;
	double	rotation_speed;
}				t_pl;

typedef struct	s_sprite
{
	int		number;
	double	x;
	double	y;
}				t_sprite;

typedef struct	s_cub
{
	int		window_width;
	int		window_height;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*sp_path;
	int		f_color[3];
	int		c_color[3];
	char	*map[MAP_BUF_SIZE + 1];
	int		map_maxrow;
	int		map_maxcol;
	bool	win_f;
	bool	no_path_f;
	bool	so_path_f;
	bool	we_path_f;
	bool	ea_path_f;
	bool	sp_path_f;
	bool	f_color_f;
	bool	c_color_f;
	t_list	*items;
}				t_cub;

typedef struct	s_game
{
	void	*mlx;
	void	*mlx_win;
	t_cub	cub;
	t_img	map;
	t_pl	player;
}				t_game;

typedef enum	e_id
{
	R,
	NO,
	SO,
	WE,
	EA,
	S,
	F,
	C,
	MAP
}				t_id;
typedef enum	e_err_conf
{
	READ_ERROR = 0,
	MALLOC_ERROR = 2,
	ISNT_CUBFILE,
	MULTIPLE_ID,
	INVALID_FORMAT,
	INVALID_RESO,
	INVALID_FILEPATH,
	INVALID_COLOR,
	NO_MAP_INFILE,
	MULTIPLE_PLAYER,
	MAP_ISNT_CLOSED
}				t_err_conf;

void	init_val(t_game *game);
void	err_exit(char *errormsg);
void	config_error(int ret);
//void	free_cub_info(void);
int		read_cub(int fd, t_cub *cub);
int		input_resolution(char *line, t_cub *cub);
int		input_path(char *line, int identifier, t_cub *cub);
int		input_color(char *line, int identifier, t_cub *cub);
int		is_validmapline(char *line, t_cub *cub);
int		set_flag(int identifier, t_cub *cub);
int		perse_map(int fd, t_cub *cub);
int		is_valid_map(t_game *game);
void	render_minimap(t_game *game);
void	render_map_object(t_game *game);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		keypress_hook(int keycode, t_game *game);
int		keyrelease_hook(int keycode, t_game *game);
int		loop(t_game *game);

//for debug
void	render_gridline(t_img *map, t_cub cub);
void	test_print_cub(t_cub cub);
void	print_map(t_cub cub);


#endif