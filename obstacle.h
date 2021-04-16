#pragma once
#include "gameobject.h"
#include "graphics.h"
#include "config.h"

class Obstacle : public GameObject {
public:
	float obstacle_width = 25;
	float obstacle_height = 10;
	float pos_y = CANVAS_HEIGHT - 75;
	int hit_points = 2;
	bool collidable = true;
	graphics::Brush br;
	void update() override;
	void draw() override;
	void draw(int j) ;
	float getPosX(int j);
	void init() override;


};
