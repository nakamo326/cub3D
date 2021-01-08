#include "cub3d.h"

//void	output_bmp(int fd, t_game *game)
//{
//
//}

void	export_bmp(t_game *game)
{
	int	fd;

	cal_item_info(game->cub.items, game->player);
	cast_all_rays(game);
	render_projected_wall(game);
	render_sprite(game);
	mlx_do_sync(game->mlx);
	fd = open("./ss.bmp", O_CREAT | O_WRONLY, S_IRWXU);
	if (fd == ERROR)
		exit(EXIT_FAILURE);
	//output_bmp(fd, game);

}