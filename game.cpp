#include "game.h"
#include "graphics.h"
#include "config.h"
#include <time.h>


void Game::update()
{

    if (!player_initialized) {
        player_initialized = true;
        player = new Player();
    }
    if (player)
        player->update();

    if (!enemy_initialized) {
        enemy_initialized = true;
        for (int i = 0; i <= 4; i++)
            for (int j = 0; j <= 9; j++)
                enemy[i][j] = new Enemy();
    }

    if (!obstacles_initialized) {
        obstacles_initialized = true;
        for (int i = 0; i <= 11; i++)
            obstacle[i] = new Obstacle();
    }

    checkCollision();
    checkBulletCollision();
    checkObstacleCollision();
    for (int i = 0; i <= 4; i++)
        for (int j = 0; j <= 9; j++) {
            if (enemy[i][j])
                enemy[i][j]->update();

        }


    for (int j = 0; j <= 9; j++) {
        if (emptyColumn(j) && Enemy::left_gap == 25 - j * 75)
            Enemy::left_gap -= 75;
        else if (!emptyColumn(j))
            break;
    }

    for (int j = 9; j >= 0; j--)
        if (emptyColumn(j) && Enemy::right_gap == 700 - (9 - j) * 75)
            Enemy::right_gap -= 75;
        else if (!emptyColumn(j))
            break;


    for (int i = 0; i <= 4; i++)
        for (int j = 0; j <= 9; j++)
            if (enemy[i][j] && enemy[i][j]->destroyed) {
                delete enemy[i][j];
                enemy[i][j] = nullptr;
                restart[i * 10 + j] = true;
            }

    for (int i = 0; i <= 49; i++) {
        if (!restart[i])
            break;
        if (i == 49) {
            enemy_initialized = false;
            obstacles_initialized = false;
            Enemy::right_gap = 700;
            Enemy::left_gap = 25;
            for (int j = 0; j <= 49; j++)
                restart[j] = false;
        }
    }

    srand(time(0));
    if (graphics::getGlobalTime() > 3000.0f && enemy[a][b] && !enemy[a][b]->firing || !enemy[a][b]) {
        a = 4;
        b = rand() % 10 + 0;
        while (emptyColumn(b) && !gameOver && enemy_initialized)
            b = rand() % 10 + 0;
        while (!enemy[a][b] && a > 0)
            a--;
    }

    checkGameOver();
    if (gameOver) {
        delete player;
        player = nullptr;
        graphics::stopMusic();
        file.open("highscore.txt");
        if (Score > high_score)
            file << Score;
        else
            file << high_score;
        file.close();
        for (int i = 0; i <= 4; i++)
            for (int j = 0; j <= 9; j++) {
                delete enemy[i][j];
                enemy[i][j] = nullptr;
            }

    }

    if (graphics::getKeyState(graphics::SCANCODE_RETURN) && gameOver || graphics::getKeyState(graphics::SCANCODE_R)) {
        gameOver = false;
        enemy_initialized = false;
        player_initialized = false;
        obstacles_initialized = false;
        Score = 0;
        Enemy::right_gap = 700;
        Enemy::left_gap = 25;
        init();
        for (int i = 0; i <= 49; i++)
            restart[i] = false;
    }



}

void Game::drawStartScreen()
{
    graphics::Brush br;
    graphics::Brush br2;
    graphics::Brush br3, br4, br5;
    br.texture = std::string(ASSET_PATH) + "startscreen.png";
    br2.texture = std::string(ASSET_PATH) + "startlogo.png";
    br2.outline_opacity = 0.0f;
    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
    graphics::drawRect(CANVAS_WIDTH / 2 , 100, CANVAS_WIDTH / 3, 200, br2);
    graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, 30, std::string("Press Enter to start"), br);
    graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2 + 30, 20, std::string("Instructions:"), br);
    graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2 + 50, 20, std::string("Press Space to shoot"), br);
    graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2 + 70, 20, std::string("Use left and right arrow to move"), br);
    br3.texture = std::string(ASSET_PATH) + "alien2.png";
    br4.texture = std::string(ASSET_PATH) + "alien.png";
    br5.texture = std::string(ASSET_PATH) + "alien3.png";
    br3.outline_opacity = 0.0f;
    br4.outline_opacity = 0.0f;
    br5.outline_opacity = 0.0f;
    graphics::drawRect(CANVAS_WIDTH / 3 + 15, CANVAS_HEIGHT / 2 + 100, 50, 30, br3);
    graphics::drawRect(CANVAS_WIDTH / 3 + 15, CANVAS_HEIGHT / 2 + 140, 50, 30, br4);
    graphics::drawRect(CANVAS_WIDTH / 3 + 15, CANVAS_HEIGHT / 2 + 180, 50, 30, br5);
    graphics::drawText(CANVAS_WIDTH / 3 + 50, CANVAS_HEIGHT / 2 + 110, 20, "=  10  POINTS", br);
    graphics::drawText(CANVAS_WIDTH / 3 + 50, CANVAS_HEIGHT / 2 + 150, 20, "=  20  POINTS", br);
    graphics::drawText(CANVAS_WIDTH / 3 + 50, CANVAS_HEIGHT / 2 + 190, 20, "=  30  POINTS", br);

    char info[40];
    sprintf_s(info, "(%i)", high_score);
    graphics::drawText(15, CANVAS_HEIGHT - 15, 15, std::string("High Score: ") + info, br);
    
}

void Game::checkCollision()
{
    if (player)
    for (int k = 0; k <= 4; k++)
        for (int l = 0; l <= 9; l++) {
            if (enemy[k][l])
            if (abs(player->projectile_pos - enemy[k][l]->pos_y - 40 * k) < 25 && abs(player->initial_x - enemy[k][l]->pos_x - 75 * l) < 25) {
                enemy[k][l]->destroyed = true;
                for (int i = 0; i <= 4; i++)
                    for (int j = 0; j <= 9; j++)
                        if (enemy[i][j] && enemy[i][j]->speed > 0)
                            enemy[i][j]->speed += 0.1f+2*(4-k)/3;
                        else if(enemy[i][j] && enemy[i][j]->speed<0)
                            enemy[i][j]->speed -= 0.1f+2*(4-k)/3;
                if (k == 4 || k == 3)
                    Score += 10;
                else if (k == 0)
                    Score += 30;
                else
                    Score += 20;
                player->firing = false;
                player->initial_x = player->pos_x;
                player->projectile_pos = player->pos_y - player->player_height/2 - player->projectile_height / 2;
            }
        }
}

void Game::checkGameOver()
{
    if (player)
        for (int i = 0; i <= 4; i++)
            for (int j = 0; j <= 9; j++) {
                if (enemy[i][j])
                    if (abs(player->pos_y - enemy[i][j]->pos_y - 40 * i) < 50 && abs(player->pos_x - enemy[i][j]->pos_x - 75 * j) < 25) {
                        gameOver = true;
                        graphics::playSound(std::string(ASSET_PATH) + "explosion.wav", 0.1f, false);
                    }
            }

    if (player)
        for (int i = 0; i <= 4; i++)
            for (int j = 0; j <= 9; j++) {
                if (enemy[i][j])
                    if (abs(player->pos_y - enemy[i][j]->projectile_pos - 40 * i) < 10 && abs(player->pos_x - enemy[i][j]->pos_x - 75 * j) < 25) {
                        enemy[i][j]->projectile_pos = CANVAS_HEIGHT + 16;
                        player->lives--;
                        graphics::playSound(std::string(ASSET_PATH) + "explosion.wav", 0.1f, false);
                        if (player->lives == 0) {
                            gameOver = true;
                        }
                    }
            }
    
        for (int i = 0; i <= 4; i++)
        for (int j = 0; j <= 9; j++)
            if (enemy[i][j] && enemy[i][j]->pos_y == CANVAS_HEIGHT) {
                gameOver = true;
                graphics::playSound(std::string(ASSET_PATH) + "trompone.wav", 0.01f, false);
            }
}


int Game::a = 4;
int Game::b = 0;

void Game::checkBulletCollision()
{
    if (player && player->firing)
    for (int i = 0; i <= 4; i++)
        for (int j = 0; j <= 9; j++) {
            if (enemy[i][j] && enemy[i][j]->projectile_pos > enemy[i][j]->pos_y + 50)
                if (abs(player->projectile_pos - enemy[i][j]->projectile_pos - 40 * i) < player->projectile_height && abs(player->initial_x - enemy[i][j]->pos_x - 75 * j) < 3) {
                    player->firing = false;
                    graphics::playSound(std::string(ASSET_PATH) + "laser.mp3", 0.1f, false);
                    player->projectile_pos = player->pos_y - 25 - player->projectile_height / 2;
                    enemy[i][j]->projectile_pos = CANVAS_HEIGHT + 16;
                }


        }
}

void Game::draw()
{
    graphics::Brush br;
    br.texture = std::string(ASSET_PATH) + "earth.png";
    graphics::drawRect(500, 250, 1000, 500, br);
  
    if (player) 
        player->draw();
    if (player && player->firing)
        player->fire();
    
    for (int i = 0; i <= 4; i++)
        for (int j = 0; j <= 9; j++) {
            if (enemy[i][j])
                enemy[i][j]->draw(i, j);
        }

   
    if (enemy[a][b] && enemy[a][b]->firing) {
        enemy[a][b]->fire(a, b);
    }

    for (int j=0; j<=11; j++)
    obstacle[j]->draw(j);


    if (player) {
        graphics::Brush br2;
        br2.texture = std::string(ASSET_PATH) + "spaceship.png";
        br2.outline_opacity = 0.0f;
        char info[40];
        char info2[40];
        sprintf_s(info, "(%i)", Score);
        sprintf_s(info2, "(%i)", high_score);
        graphics::drawText(15, 15, 15, std::string("Score: ") + info, br);
        graphics::drawText(600, 15, 15, "Press R to Restart", br);
        graphics::drawText(200, 15, 15, std::string("High Score: ") + info2, br);
        graphics::drawText(CANVAS_WIDTH - 150, 15, 15, "Lives : ", br);
        if (player->lives == 2) {
            graphics::drawRect(CANVAS_WIDTH - 85, 15, 30, 30, br2);
            graphics::drawRect(CANVAS_WIDTH - 55, 15, 30, 30, br2);
        }
        else
            graphics::drawRect(CANVAS_WIDTH - 85, 15, 30, 30, br2);

       
    }

    if (gameOver) {
        graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 3, 60, std::string("GAME OVER"), br);
        char info[40];
        char info2[40];
        sprintf_s(info, "(%i)", Score);
        sprintf_s(info2, "(%i)", high_score);
        if (Score <= high_score) {
            graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 3 + 60, 30, std::string("SCORE: ") + info, br);
            graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 3 + 100, 30, std::string("HIGH SCORE: ") + info2, br);
        }
        else 
            graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 3 + 60, 30, std::string("NEW HIGH SCORE: ") + info, br);

        graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 3 + 140, 30, "Press Enter to try again", br);
    }



    if (debugMode) {
        if (emptyColumn(7))
        graphics::drawText(500, 15, 15, "true", br);
        else 
            graphics::drawText(500, 15, 15, "false", br);
    }
    
    
}

void Game::init()
{
    graphics::setFont(std::string(ASSET_PATH) + "bitmap.ttf");
    graphics::playMusic(std::string(ASSET_PATH) + "spaceinvaders1.mp3", 0.1f, true);
    file.open("highscore.txt");
    file >> high_score;
}

bool Game::emptyColumn(int j)
{
    int i;
    for (i = 0; i <= 4; i++)
        if (enemy[i][j])
            return false;
    if (i == 4)
        return true;
}

Game::Game()
{
    for (int i = 0; i <= 4; i++)
        for (int j = 0; j <= 9; j++)
            enemy[i][j] = nullptr;
}

void Game::checkObstacleCollision()
{
    for (int k = 0; k <= 11; k++)
        for (int i = 0; i <= 4; i++)
            for (int j = 0; j <= 9; j++) {
                if (enemy[i][j] && obstacle[k]->collidable)
                    if (abs(obstacle[k]->pos_y - enemy[i][j]->projectile_pos - 40 * i) < 12 && abs(obstacle[k]->getPosX(k) - enemy[i][j]->pos_x - 75 * j) < 13) {
                        enemy[i][j]->projectile_pos = CANVAS_HEIGHT + 16;
                        obstacle[k]->hit_points--;
                        if (obstacle[k]->hit_points == 0)
                            obstacle[k]->collidable = false;
                    }
            }

    for (int i=0; i<=11; i++)
        if (player && obstacle[i]->collidable)
            if (abs(obstacle[i]->pos_y - player->projectile_pos) < 12 && abs(obstacle[i]->getPosX(i) - player->initial_x) < 13) {
                player->firing = false;
                player->projectile_pos = player->pos_y - 25 - player->projectile_height / 2;
            }

    for (int k = 0; k <= 11; k++)
        for (int i = 0; i <= 4; i++)
            for (int j = 0; j <= 9; j++) {
                if (enemy[i][j] && obstacle[k]->collidable)
                    if (abs(obstacle[k]->pos_y - enemy[i][j]->pos_y - 40 * i) < 12 && abs(obstacle[k]->getPosX(k) - enemy[i][j]->pos_x - 75 * j) < 13) {
                            obstacle[k]->collidable = false;
                    }
            }
}

Game::~Game()
{
    if (player)
        delete player;

    for (int i = 0; i <= 4; i++)
        for (int j = 0; j <= 9; j++) {
            if (enemy[i][j])
                delete enemy[i][j];
        }

    for (int i = 0; i <= 11; i++)
        delete obstacle[i];
}
