#pragma once
#include "gameobject.h"
#include "graphics.h"
#include "config.h"

class Player : public GameObject 
{

	float speed = 10;
public:
	float player_width = 50;
	float player_height = 50;
	float pos_x = CANVAS_WIDTH / 2;
	float pos_y = CANVAS_HEIGHT-player_height/2;
	float projectile_height = 16;
	float projectile_pos = pos_y - player_height / 2 - projectile_height/2;
	float initial_x = pos_x;
	int lives = 2;
	bool firing = false;
	void update() override;
	void draw() override;
	void init() override;
	void fire();
};