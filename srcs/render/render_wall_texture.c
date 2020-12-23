
#include "cub3d.h"

t_tex	choose_texture(t_ray ray, t_game *game)
{
	t_tex tex;
	if (ray.facing_up && ray.hwall_hit)
		tex = game->tex_n;
	if (ray.facing_down && ray.hwall_hit)
		tex = game->tex_s;
	if (ray.facing_right && ray.vwall_hit)
		tex = game->tex_w;
	if (ray.facing_left && ray.vwall_hit)
		tex = game->tex_e;
	return (tex);
}

int		get_wall_texture(t_game *game, int i, double x_ratio, double y_ratio)
{
	int		color;
	char *addr;
	t_tex	tex;
	int x;
	int y;

	tex = choose_texture(game->rays[i], game);
	x = round(x_ratio * tex.width);
	y = round(y_ratio * tex.height);

	addr = (char *)tex.addr;
	color = *(int *)(addr + y * tex.len + x * (tex.bpp / 8));

	return (color);

}