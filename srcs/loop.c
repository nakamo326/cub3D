/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 15:06:12 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/06 12:49:38 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_collision(t_game *game, double x, double y)
{
	int map_x;
	int map_y;

	map_x = x / TILE_SIZE;
	map_y = y / TILE_SIZE;
	if (game->cub.map[map_y][map_x] == '1')
		return (INWALL);
	return (ONFLOOR);
}

void	move_player(t_game *game)
{
	double movestep;
	double new_x;
	double new_y;
	//rotation
	game->player.rotation_angle +=
		game->player.turn_direction * game->player.rotation_speed;
	movestep = game->player.walk_direction * game->player.move_speed;

	new_x = game->player.x + cos(game->player.rotation_angle) * movestep;
	new_y = game->player.y + sin(game->player.rotation_angle) * movestep;
	if (!check_collision(game, new_x, game->player.y))
		game->player.x = new_x;
	if (!check_collision(game, game->player.x, new_y))
		game->player.y = new_y;
}


int	loop(t_game *game)
{
	move_player(game);
	render_minimap(game);

	mlx_put_image_to_window(game->mlx, game->mlx_win, game->map.img_ptr, 0, 0);
	mlx_do_sync(game->mlx);
	return (SUCCESS);
}