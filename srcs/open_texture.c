/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:04:08 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/13 16:16:51 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_tex(t_game *game, t_tex *tex, char *path)
{
	tex->img_ptr = mlx_xpm_file_to_image(game->mlx, path,
		&tex->width, &tex->height);
	tex->addr = mlx_get_data_addr(tex->img_ptr,
		&tex->bpp, &tex->len, &tex->endian);
}

void	open_ani_sp(t_game *game, t_tex tex_ar[])
{
	open_tex(game, &tex_ar[0], "./texture/ani_sprite/oilbarrel0.xpm");
	open_tex(game, &tex_ar[1], "./texture/ani_sprite/oilbarrel1.xpm");
	open_tex(game, &tex_ar[2], "./texture/ani_sprite/oilbarrel2.xpm");
	open_tex(game, &tex_ar[3], "./texture/ani_sprite/oilbarrel_halfup.xpm");
	open_tex(game, &tex_ar[4], "./texture/ani_sprite/oilbarrel_halfdown.xpm");
}

void	open_ani_fire(t_game *game, t_tex tex_ar[])
{
	open_tex(game, &tex_ar[0], "./texture/ani_sprite/fire0.xpm");
	open_tex(game, &tex_ar[1], "./texture/ani_sprite/fire1.xpm");
	open_tex(game, &tex_ar[2], "./texture/ani_sprite/fire2.xpm");
}

void	open_all_texture(t_game *game)
{
	open_tex(game, &game->tex_n, game->cub.no_path);
	open_tex(game, &game->tex_s, game->cub.so_path);
	open_tex(game, &game->tex_w, game->cub.we_path);
	open_tex(game, &game->tex_e, game->cub.ea_path);
	open_tex(game, &game->tex_sp, game->cub.sp_path);
	if (BONUS_F == 1)
	{
		open_tex(game, &game->tex_sky, "./texture/parallax-industrial.xpm");
		open_tex(game, &game->tex_floor, "./texture/floor.xpm");
		open_ani_sp(game, game->tex_ani_sp);
		open_ani_fire(game, game->tex_ani_fire);
	}
	ft_putendl_fd("All textures are opened.", 0);
}
