/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 22:38:51 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/06 12:02:41 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//実際は向いている角度と進むスピードから三角関数でx,yの距離が出せる
	//keyhookでは方向を変えるだけ、リリースで戻す
	//loopの中に更新の関数入れる。横歩きどうする？？

void	update_direction(int keycode, t_game *game)
{
	if (keycode == 119)
		game->player.walk_direction = 1;
	if (keycode == 115)
		game->player.walk_direction = -1;
	if (keycode == 97)
		game->player.turn_direction = -1;
	if (keycode == 100)
		game->player.turn_direction = 1;
}

void	reset_direction(int keycode, t_game *game)
{
	if (keycode == 119)
		game->player.walk_direction = 0;
	if (keycode == 115)
		game->player.walk_direction = 0;
	if (keycode == 97)
		game->player.turn_direction = 0;
	if (keycode == 100)
		game->player.turn_direction = 0;
}

int		keypress_hook(int keycode, t_game *game)
{

	printf("The key you pressed is \"%d\"\n", keycode);
	if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
		update_direction(keycode, game);
	printf("(%f,%f)\n", game->player.x, game->player.y);
	return (SUCCESS);
}

int		keyrelease_hook(int keycode, t_game *game)
{
	printf("The key you released is \"%d\"\n", keycode);
	if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
		reset_direction(keycode, game);

	return (SUCCESS);
}
