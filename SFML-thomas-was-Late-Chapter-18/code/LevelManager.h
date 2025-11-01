#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Powerup.h"

using namespace sf;
using namespace std;


class LevelManager
{
private:
	Vector2i m_LevelSize;
	Vector2f m_StartPosition;
	float m_TimeModifier = 1;
	float m_BaseTimeLimit = 0;
	int m_CurrentLevel = 0;
	const int NUM_LEVELS = 4;

	// Vectors to store the enemies and powerups
	vector<Enemy> m_Enemies;
	vector<Powerup> m_Powerups;

public:

	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	float getTimeLimit();

	Vector2f getStartPosition();

	int** nextLevel(VertexArray& rVaLevel);

	Vector2i getLevelSize();

	int getCurrentLevel();

	// Enemy and powerup vectors
	vector<Enemy>& getEnemies();
	vector<Powerup>& getPowerups();
};
