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

void	render_floor(t_game *game, int i, int j)
{
	double playerheight = game->cub.window_height / 2;
	double dist_plane = (game->cub.window_width / 2) / tan(FOV / 2);
	while(j < game->cub.window_height)
	{
		double distance = dist_plane * playerheight / (j - playerheight);
		double correct_distance = distance / cos(game->rays[i].ray_angle - game->player.rotation_angle);
		double x = game->player.x + correct_distance * cos(game->rays[i].ray_angle);
		double y = game->player.y + fabs(correct_distance * sin(game->rays[i].ray_angle));
		double x_ratio = fmod(x, TILE_SIZE) / TILE_SIZE;
		double y_ratio = fmod(y, TILE_SIZE) / TILE_SIZE;
		//printf("%f,%f\n", x_ratio, y_ratio);
		int color = get_floor_texture(game, x_ratio, y_ratio);
		my_mlx_pixel_put(&game->view, i , j, color);
		j++;
	}
}
