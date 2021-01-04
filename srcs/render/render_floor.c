#include "cub3d.h"

int		get_floor_texture(t_game *game, double x_ratio, double y_ratio)
{
	int		color;
	char	*addr;
	t_tex	tex;
	int		x;
	int		y;

	tex = game->tex_sp;
	x = round(x_ratio * tex.width);
	y = round(y_ratio * tex.height);
	addr = (char *)tex.addr;
	color = *(int *)(addr + y * tex.len + x * (tex.bpp / 8));
	return (color);
}

void	render_floor(t_game *game, double dist_plane, int i, int j)
{
	while(j < game->cub.window_height)
	{
		double distance = game->player.z / (j - game->cub.window_height / 2) * dist_plane;
		double correct_distance = distance / cos(game->rays[i].ray_angle - game->player.rotation_angle);
		double x = game->player.x + correct_distance * cos(game->rays[i].ray_angle);
		double y = game->player.y + correct_distance * sin(game->rays[i].ray_angle);
		double x_ratio = fmod(x, TILE_SIZE) / TILE_SIZE;
		double y_ratio = fmod(y, TILE_SIZE) / TILE_SIZE;
		int color = get_floor_texture(game, x_ratio, y_ratio);
		my_mlx_pixel_put(&game->view, i , j, color);
		j++;
	}
}
