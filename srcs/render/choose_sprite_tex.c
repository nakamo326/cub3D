/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_sprite_tex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:25:39 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/16 20:03:04 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_damage(t_game *game)
{
	if (game->player.life > 0)
		game->player.life -= 25;
}

t_tex	open_lottery(t_sprite *sp, t_game *game)
{
	if (sp->num == -1)
	{
		if (game->frame >= 0)
			sp->num = 0;
		if (game->frame >= 2)
			sp->num = 1;
		if (game->frame >= 4)
		{
			get_damage(game);
			sp->num = 2;
		}
	}
	return (game->tex_ani_lot[sp->num]);
}

t_tex	choose_sp_tex(t_sprite *sp, t_game *game)
{
	t_tex tex;

	if (sp->life == 3)
		tex = game->tex_ani_sp[0];
	if (sp->life == 2)
		tex = game->tex_ani_sp[1];
	if (sp->life == 1)
		tex = game->tex_ani_sp[2];
	if (sp->life == 0)
		tex = open_lottery(sp, game);
	return (tex);
}
