#include "obstacle.h"
#include "graphics.h"
#include "config.h"

void Obstacle::update()
{
}

void Obstacle::draw()
{
}

void Obstacle::draw(int j)
{    
	if (hit_points == 2)
		br.texture = std::string(ASSET_PATH) + "obstacle.png";
	if (hit_points==1)
		br.texture = std::string(ASSET_PATH) + "destroyedobstacle.png";
	if (!collidable)
		br.texture = std::string(ASSET_PATH) + "debris.png";
	br.outline_opacity = 0.0f;
	if (j<=3)
	graphics::drawRect(CANVAS_WIDTH/5 +obstacle_width/2 +j*obstacle_width, pos_y, obstacle_width, obstacle_height, br);
	else if (j<=7)
		graphics::drawRect(CANVAS_WIDTH /2 + obstacle_width/2 + (j-4) * obstacle_width, pos_y, obstacle_width, obstacle_height, br);
	else graphics::drawRect(CANVAS_WIDTH - CANVAS_WIDTH/5+ obstacle_width/2 + (j-8) * obstacle_width, pos_y, obstacle_width, obstacle_height, br);
}

float Obstacle::getPosX(int j)
{
	if (j <= 3)
		return CANVAS_WIDTH / 5 + obstacle_width / 2 + j * obstacle_width;
	else if (j <= 7)
		return CANVAS_WIDTH / 2 + obstacle_width / 2 + (j - 4) * obstacle_width;
	else
		return CANVAS_WIDTH - CANVAS_WIDTH / 5 + obstacle_width / 2 + (j - 8) * obstacle_width;
}

void Obstacle::init()
{
}
