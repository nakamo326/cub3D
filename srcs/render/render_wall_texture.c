
#include "cub3d.h"

t_tex	choose_texture(t_ray ray, t_game game)
{
	if (ray.facing_up &&)

}

int		get_wall_texture(t_game *game, int i, double x_ratio, double y_ratio)
{
	int		color;
	//int		trgb[4];
	char *addr;
	t_tex	tex;
	int x;
	int y;

	tex = choose_texture(game->rays[i], game);
	//tex = game->tex_n;
	x = round(x_ratio * tex.width);
	y = round(y_ratio * tex.height);

	addr = (char *)tex.addr;
	color = *(int *)(addr + y * tex.len + x * (tex.bpp / 8));

	return (color);

}