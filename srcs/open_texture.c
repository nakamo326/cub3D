#include "cub3d.h"

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
}