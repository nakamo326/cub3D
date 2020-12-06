/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 12:18:39 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/06 11:28:58 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_player(t_img *map, int x, int y)
{
	//red dot with anti alias
	my_mlx_pixel_put(map, x, y, 0xFF0000);
	my_mlx_pixel_put(map, x + 1, y, 0xFF0000);
	my_mlx_pixel_put(map, x - 1, y, 0xFF0000);
	my_mlx_pixel_put(map, x, y + 1, 0xFF0000);
	my_mlx_pixel_put(map, x, y - 1, 0xFF0000);
	my_mlx_pixel_put(map, x - 1, y - 1, 0x80110B);
	my_mlx_pixel_put(map, x - 1, y + 1, 0x80110B);
	my_mlx_pixel_put(map, x + 1, y - 1, 0x80110B);
	my_mlx_pixel_put(map, x + 1, y + 1, 0x80110B);
}

void	render_items(t_img *map, int x, int y)
{
	int i;
	int j;

	i = 0;
	x += TILE_SIZE * 3 / 8;
	y += TILE_SIZE * 3 / 8;
	while (i <= TILE_SIZE / 4)
	{
		j = 0;
		while (j <= TILE_SIZE / 4)
		{
			my_mlx_pixel_put(map, x + i, y + j, 0x2DC8FF);
			j++;
		}
		i++;
	}
}

void	render_map_object(t_game *game)
{
	t_list		*lstptr;
	t_sprite	*item_info;

	render_player(&game->map, game->player.x, game->player.y);
	lstptr = game->cub.items;
	while (lstptr != NULL)
	{
		item_info = lstptr->content;
		render_items(&game->map, item_info->x, item_info->y);
		lstptr = lstptr->next;
	}

}