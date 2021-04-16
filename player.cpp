#include "player.h"
#include "graphics.h"
#include "config.h"

void Player::update()
{
	if (graphics::getKeyState(graphics::SCANCODE_LEFT) && !firing) {
		pos_x -= speed * graphics::getDeltaTime() / 30.0f;
		initial_x -= speed * graphics::getDeltaTime() / 30.0f;
	}
	else if (graphics::getKeyState(graphics::SCANCODE_LEFT) && firing) {
		pos_x -= speed * graphics::getDeltaTime() / 30.0f;
	
	}
	if (graphics::getKeyState(graphics::SCANCODE_RIGHT) && !firing) {
		pos_x += speed * graphics::getDeltaTime() / 30.0f;
		initial_x += speed * graphics::getDeltaTime() / 30.0f;
	}
	else if (graphics::getKeyState(graphics::SCANCODE_RIGHT) && firing) {
		pos_x += speed * graphics::getDeltaTime() / 30.0f;
	}

	if (pos_x < player_width / 2) pos_x = player_width / 2;
	if (pos_x > CANVAS_WIDTH - player_width / 2) pos_x = CANVAS_WIDTH - player_width / 2;

	
	if (graphics::getKeyState(graphics::SCANCODE_SPACE) && !firing) {
		graphics::playSound(std::string(ASSET_PATH) + "laser.mp3", 0.3f, false);
		firing = true;
	}

	if (projectile_pos < 0) {
		projectile_pos = pos_y - player_height / 2 - projectile_height / 2;
		firing = false;
	}
	if (!firing) {
		initial_x = pos_x;
		projectile_pos = pos_y - player_height / 2 - projectile_height / 2;
	}
	
}

void Player::draw()
{
	graphics::Brush br;
	graphics::Brush br2;
	br.texture = std::string(ASSET_PATH) + "spaceship.png";
	br.outline_opacity = 0.0f;
	float t = sinf(graphics::getGlobalTime()/100.0f);
	if (t > 0 && t < 0.5f)
		br2.texture = std::string(ASSET_PATH) + "fire2.png";
	else if(t>0.5f)
		br2.texture = std::string(ASSET_PATH) + "fire.png";
	else if (t<0 && t>-0.5f)
		br2.texture = std::string(ASSET_PATH) + "fire3.png";
	else
		br2.texture = std::string(ASSET_PATH) + "fire4.png";
	br2.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, player_width, player_height, br);
	if (lives==1)
		graphics::drawRect(pos_x, pos_y, 3*player_width/4, 3*player_height/4, br2);

}

void Player::init()
{
}

void Player::fire()
{       
		graphics::Brush br;
		br.fill_color[1] = 0.5f;
		br.fill_color[0] = 0.6f;
		br.fill_color[2] = 0.4f;
		graphics::drawRect(initial_x, projectile_pos, 2, projectile_height, br);
		
		projectile_pos -= speed * graphics::getDeltaTime() / 20.0f;
		
	
}

