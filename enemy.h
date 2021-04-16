#pragma once
#include "gameobject.h"
#include "config.h"

class Enemy : public GameObject 
{
	float alien_width = 50;
	float alien_height = 30;
public:
	static float left_gap;
	static float right_gap;
	float speed = 0.5f;
	bool destroyed = false;
	bool firing = false;
	float pos_x = CANVAS_WIDTH / 8;
	float pos_y = 2*alien_height;
	float projectile_pos = pos_y + alien_height / 2;
	float projectile_height = 16;
	void update() override;
	void draw() override;
	void init() override;
	void draw(int i, int j);
	void fire(int i, int j);
	Enemy();
	~Enemy();
};