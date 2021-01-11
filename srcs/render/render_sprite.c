#include "cub3d.h"

int		get_sprite_texture(t_game *game, double x_ratio, double y_ratio)
{
	int		x;
	int		y;
	int		color;
	char	*addr;
	t_tex	tex;

	tex = game->tex_sp;
	x = round(x_ratio * tex.width);
	y = round(y_ratio * tex.height);

	addr = (char *)tex.addr;
	color = *(int *)(addr + y * tex.len + x * (tex.bpp / 8));
	return (color);
}

bool	is_ray_in_sprite(t_ray ray, t_sprite *sprite)
{
	if (sprite->left_angle > sprite->right_angle)
	{
		if ((ray.ray_angle >= sprite->left_angle && ray.ray_angle <= TWO_PI) ||
		(ray.ray_angle >= 0 && ray.ray_angle <= sprite->right_angle))
		return (true);
	}
	else
	{
		if (ray.ray_angle >= sprite->left_angle &&
				ray.ray_angle <= sprite->right_angle)
			return (true);
	}
	return (false);
}

double	get_sprite_x(t_ray ray, t_sprite *sprite)
{
	double	size;
	double	result;

	if (sprite->left_angle > sprite->right_angle)
	{
		size = (TWO_PI - sprite->left_angle) + sprite->right_angle;
		if (ray.ray_angle < PI)
			result = ((TWO_PI - sprite->left_angle) + ray.ray_angle) / size;
		else
			result = (ray.ray_angle - sprite->left_angle) / size;
	}
	else
	{
		result = (ray.ray_angle - sprite->left_angle)
			/ (sprite->right_angle - sprite->left_angle);
	}
	return (result);
}


void	render_sprite_strip(t_game *game, t_sprite *sprite, int i, double correct_distance)
{
	double	distance_plane;
	double	sprite_size;
	int		sprite_start;
	double	x_ratio;
	double	y_ratio;
	int		color;
	int		j;

	distance_plane = (game->cub.window_width / 2) / tan(FOV / 2);
	sprite_size = (TILE_SIZE / correct_distance) * distance_plane;
	sprite_start = round((game->cub.window_height / 2) - (sprite_size / 2));
	x_ratio = get_sprite_x(game->rays[i], sprite);
	j = sprite_start > 0 ? sprite_start : 0;
	while (j < game->cub.window_height && j < sprite_size + sprite_start)
	{
		y_ratio = (j - sprite_start) / sprite_size;
		color = get_sprite_texture(game, x_ratio, y_ratio);
		if (color != 0x000000)
			my_mlx_pixel_put(&game->view, i, j, color);
		j++;
	}
}

void	projection_sprite(t_game *game, t_sprite *sprite)
{
	double	correct_distance;
	int		i;

	//if (sprite->visible == false)
	//	return ;
	correct_distance = sprite->distance
		* cos(sprite->angle - game->player.rotation_angle);
	i = 0;
	while (i < game->cub.window_width)
	{
		if (game->zbuffer[i] > correct_distance &&
				is_ray_in_sprite(game->rays[i], sprite))
			render_sprite_strip(game, sprite, i, correct_distance);
		i++;
	}
}

void	render_sprite(t_game *game)
{
	t_list *lst_p;
	t_sprite *sprite;

	sort_items(game->cub.items);
	lst_p = game->cub.items;
	while (lst_p != NULL)
	{
		sprite = lst_p->content;
		projection_sprite(game, sprite);
		lst_p = lst_p->next;
	}
}
