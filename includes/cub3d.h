/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 11:01:45 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/05 14:13:26 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <stdbool.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <assert.h>
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include "../get_next_line/get_next_line.h"

#define PI 3.14159265
#define TWO_PI 6.28318530
#define MAP_BUF_SIZE 64
#define TILE_SIZE 64
#define ERROR -1
#define SUCCESS 1
#define INWALL 1
#define ONFLOOR 0
#define FOV (60 * PI / 180)

typedef struct	s_img {
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}				t_img;

typedef struct	s_tex {
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
	int		width;
	int		height;
}				t_tex;

typedef struct	s_pl
{
	double	x;
	double	y;
	double	z;
	char	spawn_direction;
	int		turn_direction;
	int		walk_direction;
	int		sidewalk_direction;
	double	rotation_angle;
	double	move_speed;
	double	turn_speed;
}				t_pl;

typedef struct	s_sprite
{
	int		num;
	double	x;
	double	y;
	double	distance;

}				t_sprite;

typedef struct	s_ray
{
	double	ray_angle;
	bool	hwall_hit;
	double	hwall_x;
	double	hwall_y;
	bool	vwall_hit;
	double	vwall_x;
	double	vwall_y;
	double	distance;
	bool	facing_up;
	bool	facing_down;
	bool	facing_right;
	bool	facing_left;
}				t_ray;

typedef struct	s_line
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		delta_x;
	int		delta_y;
	bool	steep;
}				t_line;

typedef struct	s_cub
{
	int		window_width;
	int		window_height;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*sp_path;
	int		f_color;
	int		c_color;
	char	*map[MAP_BUF_SIZE + 1];
	int		map_maxrow;
	int		map_maxcol;
	bool	win_f;
	bool	no_path_f;
	bool	so_path_f;
	bool	we_path_f;
	bool	ea_path_f;
	bool	sp_path_f;
	bool	f_color_f;
	bool	c_color_f;
	t_list	*items;
	double	map_scale;
}				t_cub;

typedef struct	s_game
{
	void	*mlx;
	void	*mlx_win;
	t_cub	cub;
	t_img	view;
	t_pl	player;
	t_ray	*rays;
	t_tex	tex_n;
	t_tex	tex_s;
	t_tex	tex_w;
	t_tex	tex_e;
	t_tex	tex_sp;
}				t_game;

typedef enum	e_id
{
	R,
	NO,
	SO,
	WE,
	EA,
	S,
	F,
	C,
	MAP
}				t_id;
typedef enum	e_err_conf
{
	READ_ERROR = 0,
	MALLOC_ERROR = 2,
	ISNT_CUBFILE,
	MULTIPLE_ID,
	INVALID_FORMAT,
	INVALID_RESO,
	INVALID_FILEPATH,
	INVALID_COLOR,
	NO_MAP_INFILE,
	MULTIPLE_PLAYER,
	NO_PLAYER,
	MAP_ISNT_CLOSED
}				t_err_conf;

void	init_val(t_game *game);
void	err_exit(char *errormsg);
void	config_error(int ret);
int		quit_game(void *param);
//void	free_cub_info(void);
int		read_cub(int fd, t_cub *cub);
int		input_resolution(char *line, t_cub *cub);
int		input_path(char *line, int identifier, t_cub *cub);
int		input_color(char *line, int identifier, t_cub *cub);
int		is_validmapline(char *line, t_cub *cub);
int		set_flag(int identifier, t_cub *cub);
int		perse_map(int fd, t_cub *cub);
int		is_valid_map(t_game *game);
void	store_pl_info(t_game *game, int x, int y);
void	store_item_info(t_cub *cub, int x, int y);
void	adjust_mapscale(t_game *game);
int		is_cub(char *filepath);
int		check_valid_params(t_game *game);
void	open_wall_texture(t_game *game);

void	render_minimap(t_game *game);
void	render_map_object(t_game *game);
int		keypress_hook(int keycode, t_game *game);
int		keyrelease_hook(int keycode, t_game *game);
int		loop(t_game *game);
void	move_player(t_game *game);
int		check_collision(t_cub cub, double x, double y);
void	cast_all_rays(t_game *game);
double	normalize_angle(double angle);
void	render_projected_wall(t_game *game);
int		get_wall_texture(t_game *game, int i, double x_ratio, double y_ratio);
void	render_floor(t_game *game, double dist_plane, int i, int j);
void	render_sprite(t_game *game);

//utils
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);
int		get_color(char c, int trgb);
void	draw_line(t_game *game, t_line line, int color);
double	get_distance(double x0, double y0, double x1, double y1);


//for debug
void	test_render_gridline(t_img *map, t_cub cub);
void	test_print_cub(t_cub cub);
void	test_print_map(t_cub cub);
void	test_print_items(t_game game);

#endif
