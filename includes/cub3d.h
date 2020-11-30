/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 11:01:45 by ynakamot          #+#    #+#             */
/*   Updated: 2020/11/30 22:24:30 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include "../get_next_line/get_next_line.h"

#define PI 3.14159
#define ERROR -1

typedef struct	s_cub
{
	int		window_width;
	int		window_height;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*sp_path;
	int		f_color;
	int		c_color;
	char	**map;
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
	INVALID
}				t_id;

typedef enum	e_err_conf
{
	READ_ERROR = 0,
	INVALID_FORMAT = 2,
	INVALID_RESO
}				t_err_conf;

//image data 必要？
typedef struct	s_data {
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
}				t_data;

extern t_cub cub_info;

void	err_exit(char *errormsg);
void	config_error(int ret);


#endif