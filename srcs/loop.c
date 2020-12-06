/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 15:06:12 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/06 10:37:08 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_game *game)
{
	//this.rotationAngle += this.turnDirection * this.rotationSpeed;
	//var moveStep = this.walkDirection * this.moveSpeed;
	///////////////////////////////////////
	//// TODO: Implement wall collision
	///////////////////////////////////////
	double movestep;

	game->player.rotation_angle +=
		game->player.turn_direction * game->player.rotation_speed;
	movestep = game->player.walk_direction * game->player.move_speed;

	game->player.x += cos(game->player.rotation_angle) * movestep;
	game->player.y += sin(game->player.rotation_angle) * movestep;
}


int	loop(t_game *game)
{
	move_player(game);
	render_minimap(game);

	mlx_put_image_to_window(game->mlx, game->mlx_win, game->map.img_ptr, 0, 0);

	return (SUCCESS);
}