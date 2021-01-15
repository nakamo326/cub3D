/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 11:01:45 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/15 16:41:33 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
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

#ifndef BONUS_F
# define BONUS_F 0
# endif

#define PI 3.14159265
#define TWO_PI 6.28318530
#define MAP_BUF_SIZE 64
#define TILE_SIZE 64
#define ERROR -1
#define SUCCESS 1
#define INWALL 1
#define ONFLOOR 0
#define FOV (60 * PI / 180)

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_M 109
#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_RIGHT 65363
#define KEY_LEFT 65361
#define KEY_ESC 65307
#define KEY_ENTER 65293

typedef struct	s_img {
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
	int		w;
	int		h;
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
	int		life;
}				t_pl;

typedef struct	s_sprite
{
	int		num;
	double	x;
	double	y;
	int		life;
	double	distance;
	double	corr_dist;
	double	angle;
	double	right_cor[2];
	double	right_angle;
	double	left_cor[2];
	double	left_angle;
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
	bool	save_flag;
	bool	map_toggle;
	bool	shot;
	t_cub	cub;
	t_img	view;
	t_pl	player;
	t_ray	*rays;
	double	*zbuffer;
	double	dist_plane;
	t_tex	tex_n;
	t_tex	tex_s;
	t_tex	tex_w;
	t_tex	tex_e;
	t_tex	tex_sp;
	t_tex	tex_sky;
	t_tex	tex_floor;
	t_tex	tex_ani_sp[5];
	t_tex	tex_ani_lot[3];
	int		frame;
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
	INVALID_ARG,
	ISNT_CUBFILE,
	MULTIPLE_ID,
	INVALID_FORMAT,
	INVALID_RESO,
	INVALID_FILEPATH,
	INVALID_COLOR,
	NO_MAP_INFILE,
	MULTIPLE_PLAYER,
	NO_PLAYER,
	MAP_ISNT_CLOSED,
	MISSING_PARAMS
}				t_err_conf;

void	init_val(t_game *game);
void	is_valid_args(int argc, char *argv[], t_game *game);
void	err_exit(char *errormsg);
void	config_error(int ret);
int		quit_game(void *param);
void	export_bmp(t_game *game);

int		read_cub(int fd, t_cub *cub);
int		input_resolution(char *line, t_cub *cub);
int		input_path(char *line, int identifier, t_cub *cub);
int		input_color(char *line, int identifier, t_cub *cub);
int		is_validmapline(char *line, t_cub *cub);
int		set_flag(int identifier, t_cub *cub);
int		perse_map(int fd, t_cub *cub);
int		is_valid_map(t_game *game);
bool	store_pl_info(t_game *game, int x, int y);
void	store_item_info(t_cub *cub, int x, int y);
void	adjust_mapscale(t_game *game);
int		is_cub(char *filepath);
void	check_valid_params(t_game *game);
void	open_all_texture(t_game *game);

void	render_minimap(t_game *game);
void	render_map_object(t_game *game);
int		keypress_hook(int keycode, t_game *game);
int		keyrelease_hook(int keycode, t_game *game);
int		loop(t_game *game);
void	move_player(t_game *game);
int		check_collision(t_cub cub, double x, double y);
void	check_horizontal_intersections(t_ray *ray, t_pl player, t_cub cub);
void	check_vertical_intersection(t_ray *ray, t_pl player, t_cub cub);
void	cal_item_info(t_list *items, t_pl player);
void	is_visible_sprite(t_game *game);
void	cast_all_rays(t_game *game);
void	render_projected_wall(t_game *game);
int		get_wall_texture(t_game *game, int i, double x_ratio, double y_ratio);
void	render_floor(t_game *game, int i, int j);
void	render_sky(t_game *game);
void	render_sprite(t_game *game);
void	render_sprite_strip(t_game *game, t_sprite *sp, int i);
t_tex	choose_sp_tex(t_sprite *sp, t_game *game);
void	cal_shot(t_game *game);
void	render_reticle(t_game *game);
void	render_hitpoint(t_game *game);

//utils
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);
int		get_color(char c, int trgb);
double	normalize_angle(double angle);
double	get_distance(double x0, double y0, double x1, double y1);
void	draw_line(t_game *game, t_line line, int color);
void	sort_items(t_list *items);
bool	is_angle_in_sprite(double angle, t_sprite *sprite);
int		add_shadow(int color, t_game *game, double dist);

//for debug
void	test_render_gridline(t_img *map, t_cub cub);
void	test_print_cub(t_cub cub);
void	test_print_map(t_cub cub);
void	test_print_items(t_game game);

#endif
