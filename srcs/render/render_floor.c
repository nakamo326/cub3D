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

//void	render_floor(t_game *game, int y, double dist_plane)
//{
//	int x = 0;
//	double correct_distance;
//	double distance = game->player.z / (y - game->cub.window_height / 2) * dist_plane;
//
//	while(x < game->cub.window_width)
//	{
//		correct_distance = distance / cos(game->rays[x].ray_angle - game->player.rotation_angle);
//		double pos_x = game->player.x + correct_distance * cos(game->rays[x].ray_angle);
//		double pos_y = game->player.y + correct_distance * sin(game->rays[x].ray_angle);
//		double x_ratio = fmod(pos_x, TILE_SIZE) / TILE_SIZE;
//		double y_ratio = fmod(pos_y, TILE_SIZE) / TILE_SIZE;
//		int color = get_floor_texture(game, x_ratio, y_ratio);
//		my_mlx_pixel_put(&game->view, x, y, color);
//		x++;
//	}
//}


void	render_floor(t_game *game, double dist_plane, int i, int j)
{
	double correct_distance;

	while(j < game->cub.window_height)
	{
		double distance = game->player.z / (j - game->cub.window_height / 2) * dist_plane;
		correct_distance = distance / cos(game->rays[i].ray_angle - game->player.rotation_angle);
		double x = game->player.x + correct_distance * cos(game->rays[i].ray_angle);
		double y = game->player.y + correct_distance * sin(game->rays[i].ray_angle);
		double x_ratio = fmod(x, TILE_SIZE) / TILE_SIZE;
		double y_ratio = fmod(y, TILE_SIZE) / TILE_SIZE;
		int color = get_floor_texture(game, x_ratio, y_ratio);
		my_mlx_pixel_put(&game->view, i , j, color);
		j++;
	}
}