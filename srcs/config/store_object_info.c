/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_object_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 11:02:58 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/06 11:14:55 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_item_info(t_cub *cub, int x, int y)
{
	t_list		*new;
	t_sprite	*item_info;
	static int	num = 0;
	item_info = malloc(sizeof(t_sprite));
	item_info->x = x;
	item_info->y = y;
	item_info->number = num++;
	if (!(new = ft_lstnew(item_info)))
		config_error(MALLOC_ERROR);
	ft_lstadd_back(&cub->items, new);
	cub->map[y][x] = '0';
}

void	store_pl_info(t_game *game, int x, int y)
{
	game->player.x = x * TILE_SIZE + TILE_SIZE /2;
	game->player.y = y * TILE_SIZE + TILE_SIZE /2;
	if (game->cub.map[y][x] == 'N')
		game->player.rotation_angle = 270 * PI / 180;
	if (game->cub.map[y][x] == 'S')
		game->player.rotation_angle = 90 * PI / 180;
	if (game->cub.map[y][x] == 'W')
		game->player.rotation_angle = 0 * PI / 180;
	if (game->cub.map[y][x] == 'E')
		game->player.rotation_angle = 180 * PI / 180;
	game->cub.map[y][x] = '0';
}