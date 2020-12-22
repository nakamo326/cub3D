#include "cub3d.h"

void	open_wall_texture(t_game *game)
{
	char *path;

	path = game->cub.no_path;
	game->tex_n.img.img_ptr = mlx_xpm_file_to_image(game->mlx, path,
		&game->tex_n.width, &game->tex_n.height);
	game->tex_n.img.addr = mlx_get_data_addr(game->tex_n.img.img_ptr,
		&game->tex_n.img.bpp, &game->tex_n.img.len, &game->tex_n.img.endian);
	path = game->cub.so_path;
	game->tex_s.img.img_ptr = mlx_xpm_file_to_image(game->mlx, path,
		&game->tex_s.width, &game->tex_s.height);
	game->tex_s.img.addr = mlx_get_data_addr(game->tex_s.img.img_ptr,
		&game->tex_s.img.bpp, &game->tex_s.img.len, &game->tex_s.img.endian);
	path = game->cub.we_path;
	game->tex_w.img.img_ptr = mlx_xpm_file_to_image(game->mlx, path,
		&game->tex_w.width, &game->tex_w.height);
	game->tex_w.img.addr = mlx_get_data_addr(game->tex_w.img.img_ptr,
		&game->tex_w.img.bpp, &game->tex_w.img.len, &game->tex_w.img.endian);
	path = game->cub.ea_path;
	game->tex_e.img.img_ptr = mlx_xpm_file_to_image(game->mlx, path,
		&game->tex_e.width, &game->tex_e.height);
	game->tex_e.img.addr = mlx_get_data_addr(game->tex_e.img.img_ptr,
		&game->tex_e.img.bpp, &game->tex_e.img.len, &game->tex_e.img.endian);
}