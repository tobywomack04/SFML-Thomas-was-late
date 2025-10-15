#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Powerup
{
private:
	Vector2f m_Position;
	string m_Type;
	Sprite m_Sprite;

public:
	Powerup(Vector2f pos, string type);

	FloatRect getPosition();

	Sprite getSprite();

	string getType();
};