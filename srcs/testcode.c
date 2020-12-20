/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testcode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 10:35:24 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/20 14:41:49 by ynakamot         ###   ########.fr       */
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
	printf("fcolor: %0xd\n", cub.f_color);
	printf("ccolor: %0xd\n", cub.c_color);
	printf("map_scale: %f\n", cub.map_scale);
	//print_map();
}

void	test_print_map(t_cub cub)
{
	int i;

	i = 0;
	while (cub.map[i] != NULL)
	{
		printf("map[%2d]:%s\n", i, cub.map[i]);
		i++;
	}
}

void	test_render_gridline(t_img *map, t_cub cub)
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

void	test_print_items(t_game game)
{
	t_list *ptr;
	t_sprite *item_info;

	ptr = game.cub.items;
	while(ptr != NULL)
	{
		item_info = ptr->content;
		printf("item number: %d : %f , %f\n",item_info->number, item_info->x, item_info->y);
		ptr = ptr->next;
	}
}
