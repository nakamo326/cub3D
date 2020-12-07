/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:52:52 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/07 10:59:12 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	update_rotation_and_movestep(t_game *game)
{
	double movestep;

	game->player.rotation_angle +=
		game->player.turn_direction * game->player.rotation_speed;
	if (game->player.walk_direction != 0)
		movestep = game->player.walk_direction * game->player.move_speed;
	if (game->player.sidewalk_direction != 0)
		movestep = game->player.sidewalk_direction * game->player.move_speed;
	return (movestep);
}

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

	movestep = update_rotation_and_movestep(game);
	new_x = game->player.x;
	new_y = game->player.y;
	if (game->player.walk_direction != 0)
	{
		new_x = game->player.x + cos(game->player.rotation_angle) * movestep;
		new_y = game->player.y + sin(game->player.rotation_angle) * movestep;
	}
	if (game->player.sidewalk_direction != 0)
	{
		new_x = game->player.x + sin(game->player.rotation_angle) * movestep;
		new_y = game->player.y + cos(game->player.rotation_angle) * movestep;
	}
	if (!check_collision(game, new_x, game->player.y))
		game->player.x = new_x;
	if (!check_collision(game, game->player.x, new_y))
		game->player.y = new_y;
}