#include "cub3d.h"

int		get_sky_color(t_game *game, double x_ratio, double y_ratio)
{
	int		x;
	int		y;
	int		color;
	char	*addr;
	t_tex	tex;

	tex = game->tex_sky;
	x = round(x_ratio * tex.width);
	y = round(y_ratio * tex.height);
	addr = (char *)tex.addr;
	color = *(int *)(addr + y * tex.len + x * (tex.bpp / 8));
	return (color);
}

void	render_sky_strip(t_game *game, int i, double ray_angle)
{
	double	x_ratio;
	double	y_ratio;
	int		color;
	int j;

	x_ratio = ray_angle / FOV;
	if (x_ratio > 1)
		x_ratio -= 1;
	j = 0;
	while (j < game->cub.window_height / 2)
	{
		y_ratio = j / (double)(game->cub.window_height / 2);
		color = get_sky_color(game, x_ratio, y_ratio);
		my_mlx_pixel_put(&game->view, i, j, color);
		j++;
	}

}

void	render_sky(t_game *game)
{
	double	ray_angle;
	double	angle_per_pixel;
	int		i;

	ray_angle= game->player.rotation_angle - FOV / 2;
	angle_per_pixel = FOV / game->cub.window_width;
	i = 0;
	while (i < game->cub.window_width)
	{
		ray_angle = normalize_angle(ray_angle);
		render_sky_strip(game, i, ray_angle);
		ray_angle += angle_per_pixel;
		i++;
	}
}
