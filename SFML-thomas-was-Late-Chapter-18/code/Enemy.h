#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Enemy
{
private:
	Sprite m_Sprite;
	Vector2f m_Position;
	Vector2f m_StartPosition;

	float m_Speed = rand() % 61 + 90; // Range of (90 - 150)
	bool movingRight = true;

	string m_Type;

public:
	Enemy(Vector2f pos, string type);

	void update(float dtAsSeconds, FloatRect playerPos);

	FloatRect getPosition();

	Sprite getSprite();

	string getType();

	void resetPosition();

	Vector2f getCentre();

	void faceRight();
	void faceLeft();
};

