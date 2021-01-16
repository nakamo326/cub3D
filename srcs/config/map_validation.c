/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 11:13:11 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/16 16:54:15 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_closed_map(t_cub *cub, int x, int y)
{
	if (y < 0 || x < 0 || cub->map[y] == NULL ||
			cub->map[y][x] == '\0')
		return (0);
	if (cub->map[y][x] == '*' || cub->map[y][x] == '1')
		return (0);
	if (y == 0 || x == 0 || cub->map[y + 1] == NULL ||
			cub->map[y][x + 1] == '\0' || cub->map[y + 1][0] == '\0')
		config_error(MAP_ISNT_CLOSED);
	cub->map[y][x] = '*';
	is_closed_map(cub, x + 1, y);
	is_closed_map(cub, x, y + 1);
	is_closed_map(cub, x - 1, y);
	is_closed_map(cub, x, y - 1);
	return (SUCCESS);
}

int		is_valid_map(t_game *game)
{
	int		x;
	int		y;
	bool	p_flag;

	y = 0;
	p_flag = false;
	while (game->cub.map[y] != NULL)
	{
		x = 0;
		while (game->cub.map[y][x] != '\0')
		{
			if (game->cub.map[y][x] == '2')
				store_item_info(&game->cub, x, y);
			if (ft_strchr("NSWE", game->cub.map[y][x]) && p_flag)
				config_error(MULTIPLE_PLAYER);
			if (ft_strchr("NSWE", game->cub.map[y][x]))
				p_flag = store_pl_info(game, x, y);
			x++;
		}
		y++;
	}
	if (p_flag == false)
		config_error(NO_PLAYER);
	return (is_closed_map(&game->cub, game->player.x / TILE_SIZE,
										game->player.y / TILE_SIZE));
}
