#include "enemy.h"
#include "graphics.h"
#include "config.h"

void Enemy::update()
{
	pos_x += speed*graphics::getDeltaTime() / 75.0f;
	

	if (pos_x > CANVAS_WIDTH - right_gap && speed > 0) {
		speed = -speed;
		pos_y += 10;
		projectile_pos += 10;
	}

	if (pos_x < left_gap && speed < 0) {
		speed = -speed;
		pos_y += 10;
		projectile_pos += 10;
	}

	if (pos_y > CANVAS_HEIGHT ) pos_y = CANVAS_HEIGHT;

	if (graphics::getGlobalTime() > 2000.0f) {
		
	firing = true;
	}

	if (projectile_pos > 2*CANVAS_HEIGHT) {
		projectile_pos = pos_y + alien_height / 2;
		firing = false;
	}

	

	if (destroyed) 
		graphics::playSound(std::string(ASSET_PATH) + "invaderkilled.wav", 0.1f, false);
	
		
	
}

void Enemy::draw()
{
}

float Enemy::right_gap = 700;
float Enemy::left_gap = 25;


void Enemy::draw(int i, int j)
{
	graphics::Brush br;
	if (sinf(graphics::getGlobalTime() / 200.0f) > 0) {
		if (i >= 3)
			br.texture = std::string(ASSET_PATH) + "alien2.png";
		else if (i == 0)
			br.texture = std::string(ASSET_PATH) + "alien3.png";
		else
			br.texture = std::string(ASSET_PATH) + "alien.png";
	}
	else {
		if (i >= 3)
			br.texture = std::string(ASSET_PATH) + "movingalien2.png";
		else if (i == 0)
			br.texture = std::string(ASSET_PATH) + "movingalien3.png";
		else
			br.texture = std::string(ASSET_PATH) + "movingalien.png";
	}
	
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x + 75*j, pos_y + 40*i, alien_width, alien_height, br);
}

void Enemy::fire(int i, int j)
{
	graphics::Brush br;
	br.fill_color[1] = 0.5f;
	br.fill_color[0] = 0.6f;
	br.fill_color[2] = 0.4f;
	graphics::drawRect(pos_x + 75*j, projectile_pos + 40*i, 2, projectile_height, br);
	projectile_pos += 10.0f * graphics::getDeltaTime() / 15.0f;
}

Enemy::Enemy()
{

}


Enemy::~Enemy()
{
}

void Enemy::init()
{
}
