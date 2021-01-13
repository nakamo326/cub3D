/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_sprite_tex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:25:39 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/13 16:00:47 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_tex	get_fire(t_sprite sp, t_game *game)
{
	t_tex tex;
	(void)sp;

	tex = game->tex_ani_fire[0];
	return (tex);
}

t_tex	choose_sp_tex(t_sprite sp, t_game *game)
{
	t_tex tex;

	if (sp.life == 3)
		tex = game->tex_ani_sp[0];
	if (sp.life == 2)
		tex = game->tex_ani_sp[1];
	if (sp.life == 1)
		tex = game->tex_ani_sp[2];
	if (sp.life == 0)
		tex = get_fire(sp, game);
	return (tex);
}