/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:04:08 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/12 21:07:39 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_skybox(t_game *game)
{
	const	char *path = "./texture/parallax-industrial.xpm";

	game->tex_sky.img_ptr = mlx_xpm_file_to_image(game->mlx, (char *)path,
		&game->tex_sky.width, &game->tex_sky.height);
	game->tex_sky.addr = mlx_get_data_addr(game->tex_sky.img_ptr,
		&game->tex_sky.bpp, &game->tex_sky.len, &game->tex_sky.endian);
}

void	open_floor(t_game *game)
{
	const	char *path = "./texture/floor.xpm";

	game->tex_floor.img_ptr = mlx_xpm_file_to_image(game->mlx, (char *)path,
		&game->tex_floor.width, &game->tex_floor.height);
	game->tex_floor.addr = mlx_get_data_addr(game->tex_floor.img_ptr,
		&game->tex_floor.bpp, &game->tex_floor.len, &game->tex_floor.endian);
}

void	open_texture(t_game *game)
{
	game->tex_n.img_ptr = mlx_xpm_file_to_image(game->mlx, game->cub.no_path,
		&game->tex_n.width, &game->tex_n.height);
	game->tex_n.addr = mlx_get_data_addr(game->tex_n.img_ptr,
		&game->tex_n.bpp, &game->tex_n.len, &game->tex_n.endian);
	game->tex_s.img_ptr = mlx_xpm_file_to_image(game->mlx, game->cub.so_path,
		&game->tex_s.width, &game->tex_s.height);
	game->tex_s.addr = mlx_get_data_addr(game->tex_s.img_ptr,
		&game->tex_s.bpp, &game->tex_s.len, &game->tex_s.endian);
	game->tex_w.img_ptr = mlx_xpm_file_to_image(game->mlx, game->cub.we_path,
		&game->tex_w.width, &game->tex_w.height);
	game->tex_w.addr = mlx_get_data_addr(game->tex_w.img_ptr,
		&game->tex_w.bpp, &game->tex_w.len, &game->tex_w.endian);
	game->tex_e.img_ptr = mlx_xpm_file_to_image(game->mlx, game->cub.ea_path,
		&game->tex_e.width, &game->tex_e.height);
	game->tex_e.addr = mlx_get_data_addr(game->tex_e.img_ptr,
		&game->tex_e.bpp, &game->tex_e.len, &game->tex_e.endian);
	game->tex_sp.img_ptr = mlx_xpm_file_to_image(game->mlx, game->cub.sp_path,
		&game->tex_sp.width, &game->tex_sp.height);
	game->tex_sp.addr = mlx_get_data_addr(game->tex_sp.img_ptr,
		&game->tex_sp.bpp, &game->tex_sp.len, &game->tex_sp.endian);
	if (BONUS_F == 1)
		open_skybox(game);
	if (BONUS_F == 1)
		open_floor(game);
	ft_putendl_fd("All textures are opened.", 0);
}
