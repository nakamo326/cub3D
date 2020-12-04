/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 11:01:45 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/04 13:01:11 by ynakamot         ###   ########.fr       */
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
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include "../get_next_line/get_next_line.h"

#define PI 3.14159
#define MAP_BUF_SIZE 64
#define ERROR -1
#define SUCCESS 1

typedef struct	s_pl
{
	double	x;
	double	y;
	char	direction;
}				t_pl;

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
	bool	win_f;
	bool	no_path_f;
	bool	so_path_f;
	bool	we_path_f;
	bool	ea_path_f;
	bool	sp_path_f;
	bool	f_color_f;
	bool	c_color_f;
	char	*map[MAP_BUF_SIZE + 1];
	int		map_maxrow;
	int		map_maxcol;
	t_pl	player;
}				t_cub;


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

typedef struct	s_data {
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
}				t_data;

void	err_exit(char *errormsg);
void	config_error(int ret);
//void	free_cub_info(void);
int		input_resolution(char *line, t_cub *cub);
int		input_path(char *line, int identifier, t_cub *cub);
int		input_color(char *line, int identifier, t_cub *cub);
void	test_print_cub(t_cub *cub);
void	print_map(t_cub *cub);
int		read_cub(int fd, t_cub *cub);
int		is_validmapline(char *line, t_cub *cub);
int		perse_line(char *line, t_cub *cub);
int		check_identifier(char *line);
int		check_multiple(int identifier, t_cub *cub);
int		set_flag(int identifier, t_cub *cub);
int		perse_map(int fd, t_cub *cub);
int		is_valid_map(t_cub *cub);
int		is_closed_map(t_cub *cub, int x, int y);
void	render_map(t_data *map, t_cub cub);
void	render_gridline(t_data *map, t_cub cub);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif