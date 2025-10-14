#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Enemy
{
protected:
	Sprite m_Sprite;

private:
	Vector2f m_Position;
	Vector2f m_StartPosition;

	float speed = rand() % 61 + 90; // Range of (90 - 150)
	bool movingRight = true;

public:
	Enemy(Vector2f pos);

	void update(float dtAsSeconds);

	FloatRect getPosition();

	Sprite getSprite();
};

