/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testcode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 10:35:24 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/05 11:15:01 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	test_print_cub(t_cub cub)
{
	printf("window width: %d\n", cub.window_width);
	printf("window height: %d\n", cub.window_height);
	printf("no_path: %s\n", cub.no_path);
	printf("so_path: %s\n", cub.so_path);
	printf("we_path: %s\n", cub.we_path);
	printf("ea_path: %s\n", cub.ea_path);
	printf("sp_path: %s\n", cub.sp_path);
	printf("fcolor: %d, %d, %d\n", cub.f_color[0],cub.f_color[1],cub.f_color[2]);
	printf("ccolor: %d, %d, %d\n", cub.c_color[0],cub.c_color[1],cub.c_color[2]);
	//print_map();
}

void	print_map(t_cub cub)
{
	int i;

	i = 0;
	while (cub.map[i] != NULL)
	{
		printf("map[%2d]:%s\n", i, cub.map[i]);
		i++;
	}
}

void	render_gridline(t_img *map, t_cub cub)
{
	int i;
	int j;


	j = 0;
	while (j < cub.map_maxcol)
	{
		i = 0;
		while (i < cub.map_maxrow * 20)
			my_mlx_pixel_put(map, j * 20, i++, 0xB4B4B4);
		j++;
	}
	j = 0;
	while (j < cub.map_maxrow)
	{
		i = 0;
		while (i < cub.map_maxcol * 20)
			my_mlx_pixel_put(map, i++, j * 20, 0xB4B4B4);
		j++;
	}
}