/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 12:18:39 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/05 14:25:53 by ynakamot         ###   ########.fr       */
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

//void	render_items(t_img *map, int x, int y)
//{
//
//}

void	render_map_object(t_game *game)
{
	//t_list *lstptr;
	//int *cordinate;
	//int x;
	//int y;
	//change after define map_tilesize
	render_player(&game->map, game->player.x * 20 + 10,
					game->player.y * 20 + 10);

	//lstptr = *(game->cub.items);
	//while (lstptr != NULL)
	//{
	//	cordinate = lstptr->content;
	//	x = cordinate[0];
	//	y = cordinate[1];
	//	render_player(&game->map, x * 20 + 10, y * 20 + 10);
	//	lstptr = lstptr->next;
	//}

}