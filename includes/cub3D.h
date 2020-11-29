/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 11:01:45 by ynakamot          #+#    #+#             */
/*   Updated: 2020/11/29 23:43:54 by ynakamot         ###   ########.fr       */
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

typedef enum e_cuberror
{

}



//image data 必要？
typedef struct s_data {
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
}	t_data;


#endif