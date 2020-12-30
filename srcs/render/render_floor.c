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
		//double correct_distance = distance * cos(game->rays[i].ray_angle - game->player.rotation_angle);
		double x = game->player.x + distance * cos(game->rays[i].ray_angle);
		double y = game->player.y + distance * sin(game->rays[i].ray_angle);
		double x_ratio = fmod(x, TILE_SIZE) / TILE_SIZE;
		double y_ratio = fmod(y, TILE_SIZE) / TILE_SIZE;
		printf("%f,%f\n", x_ratio, y_ratio);
		int color = get_floor_texture(game, x_ratio, y_ratio);
		my_mlx_pixel_put(&game->view, i , j, color);
		j++;
	}
}



//void	render_floor(t_game *game)
//{
//	for(int y = game->cub.window_height / 2 + 1; y < game->cub.window_height; ++y)
//	{
//		//最初と最後のrayの方向
//		float rayDirX0 = dirX - planeX;
//		float rayDirY0 = dirY - planeY;
//		float rayDirX1 = dirX + planeX;
//		float rayDirY1 = dirY + planeY;
//		double rayDir0 = game->rays[0].ray_angle;
//		double rayDir1 = game->rays[game->cub.window_width].ray_angle;
//
//		// Current y position compared to the center of the screen (the horizon)
//		int p = y - game->cub.window_height / 2;
//
//		// Vertical position of the camera.
//		// NOTE: with 0.5, it's exactly in the center between floor and ceiling,
//		// matching also how the walls are being raycasted. For different values
//		// than 0.5, a separate loop must be done for ceiling and floor since
//		// they're no longer symmetrical.
//		float posZ = 0.5 * game->cub.window_height;
//
////現在の行のカメラから床までの水平距離。
////0.5は、床と天井のちょうど真ん中のz位置です。
////注：これはアフィンテクスチャマッピングであり、床のような完全に水平面と垂直面を除いて、遠近法は正しくありません。
////注：この式は次のように説明されます。カメラの光線は、次の2つのポイントを通過します。特定の高さ（posZ）にあるカメラ自体と、
////カメラの前のポイント（画面を含む想像上の垂直面）です。 ピクセル）カメラからの水平距離が1で、垂直位置pがposZよりも低い（posZ-p）。
////そのポイントを通過するとき、線は垂直方向にp単位、水平方向に1単位移動しました。
////床にぶつかるには、代わりにposZユニットで移動する必要があります。 水平方向に同じ比率で移動します。
////カメラ面を通過する場合の比率は1 / pでした。したがって、posZ倍遠くに移動して床に到達すると、水平方向の合計距離はposZ / pになります。
//		float rowDistance = posZ / p;
//
//		// calculate the real world step vector we have to add for each x (parallel to camera plane)
//		// adding step by step avoids multiplications with a weight in the inner loop
//		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / game->cub.window_width;
//		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / game->cub.window_width;
//
//		// real world coordinates of the leftmost column. This will be updated as we step to the right.
//		float floorX = game->player.x + rowDistance * rayDirX0;
//		float floorY = game->player.y + rowDistance * rayDirY0;
//
//		for(int x = 0; x < game->cub.window_width; ++x)
//		{
//			// the cell coord is simply got from the integer parts of floorX and floorY
//			int cellX = (int)(floorX);
//			int cellY = (int)(floorY);
//
//			// get the texture coordinate from the fractional part
//			int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
//			int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);
//
//			floorX += floorStepX;
//			floorY += floorStepY;
//
//
//			}
//	}
//}


//int		render_floor(t_game *game, int i, int j, double correct_distance)
//{
//
//	double dist = game->cub.window_height / (2 * j - game->cub.window_height); //1 ~ inifinite真ん中が0
//	double weight = dist / game->rays[i].distance;
//	double x_wall = game->rays[i].hwall_hit ? game->rays[i].hwall_x : game->rays[i].vwall_x;
//	double y_wall = game->rays[i].hwall_hit ? game->rays[i].hwall_y : game->rays[i].vwall_y;
//	double currentFloorX = weight * x_wall + (1 - weight) * game->player.x;
//	double currentFloorY = weight * y_wall + (1 - weight) * game->player.y;
//	//printf("%f,%f \n",currentFloorX, currentFloorY);
//
//	double x_ratio = fmod(currentFloorX, TILE_SIZE) / TILE_SIZE;
//	double y_ratio = fmod(currentFloorY, TILE_SIZE) / TILE_SIZE;
//	return (get_floor_texture(game, x_ratio, y_ratio));
//}
