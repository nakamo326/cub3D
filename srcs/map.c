/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 22:40:17 by ynakamot          #+#    #+#             */
/*   Updated: 2020/11/28 23:43:19 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define mapWidth 64
#define mapHeight 64
#define tilesize 20
#define screenWidth 640
#define screenHeight 480
// kari
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

char map[mapWidth][mapHeight]=
{
{'        111111111111111111111111'},
{'        100000000011000000000001'},
{'        101100000111000000200001'},
{'        100100000000000000000001'},
{'11111111101100000111000000000001'},
{'10000000001100000111011111111111'},
{'11110111111111011100000010001'},
{'11110111111111011101010010001'},
{'11000000110101011100000010001'},
{'10002000000000001100000010001'},
{'10000000000000001101010010001'},
{'11000001110101011111011110N0111'},
{'11110111 1110101 101111010001'},
{'11111111 1111111 111111111111'}
};


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + ( y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int     main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	map;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 640, 480, "2DgridMap");
	map.img = mlx_new_image(mlx, 640, 480);
	map.addr = mlx_get_data_addr(map.img, &map.bits_per_pixel, &map.line_length, &map.endian);
	my_mlx_pixel_put(&map, 5,5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, map.img, 0, 0);
	mlx_loop(mlx);
}
