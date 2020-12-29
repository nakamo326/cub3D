#include "cub3d.h"

int		get_floor_texture(t_game *game, double x_ratio, double y_ratio)
{
	int		color;
	char *addr;
	t_tex	tex;
	int x;
	int y;

	tex = game->tex_sp;
	x = round(x_ratio * tex.width);
	y = round(y_ratio * tex.height);
	addr = (char *)tex.addr;
	color = *(int *)(addr + y * tex.len + x * (tex.bpp / 8));

	return (color);
}

void	render_floor(t_game *game)
{

}


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


/*
床にテクスチャを付けたい場合は、次のようにする必要があります。
壁の縦縞を描いた後、壁の下のピクセルの下に床を描く必要があります。
テクスチャ座標を計算するには、指定されたピクセル内の床の距離を知る必要があります。
高さ/ 2で床のピクセルを描画する必要があると仮定すると、距離は無限であり、高さのピクセルの距離はたとえば1であるため、高さ/ 2と高さの間のすべてのピクセルの距離は無限から1になります。
したがって、これらの距離の間を簡単に補間できます。

dist = height /（2 * y - height）

テクスチャ座標を計算するには、次のように計算します。
壁の計算からdistWallがすでにあるはずです（意味は、1階のピクセルの真上の壁の下部のポイントです）

weight= dist / distWall;

currentFloorX =weight * XWall +（1 - weight）* playerPosX;
currentFloorY =weight * YWall +（1 - weight）* playerPosY;

floorTexX =（currentFloorX * texWidth）％texWidth;
floorTexY =（currentFloorY * texHeight）％texHeight;



ちなみに、あなたはの代表的なピクセルのためにいくつかのテクスチャ座標を使うことができます
*/