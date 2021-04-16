#pragma once
#include "player.h"
#include "enemy.h"
#include "obstacle.h"
#include <fstream>
#include "config.h"

class Game {

	Player* player = nullptr;
	bool player_initialized = false;
	Enemy* enemy[5][10];
	Obstacle* obstacle[12];

	bool debugMode = false;
	bool enemy_initialized = false;
	bool obstacles_initialized = false;
	void checkCollision();
	void checkBulletCollision();
	void checkObstacleCollision();
	void checkGameOver();
	bool restart[50];
	bool gameOver = false;
	bool emptyColumn(int j);
	static int a, b;
	int Score = 0;
	std::fstream file;

public:
	void update();
	void draw();
	void drawStartScreen();
	void init();
	Game();
	~Game();
	friend class Enemy;
	bool startGame = false;
	int high_score;
};