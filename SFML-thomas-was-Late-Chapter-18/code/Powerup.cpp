#include "Powerup.h"
#include "TextureHolder.h"

using namespace sf;
using namespace std;

Powerup::Powerup(Vector2f pos, string type)
{
	// Associate a texture with the sprite
	if (type == "health")
	{
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/heart.png"));
		m_Type = "health";
	}
	else if (type == "ammo")
	{
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/ammo.png"));
		m_Type = "ammo";
	}
	else if (type == "speed")
	{
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/speed.png"));
		m_Type = "speed";
	}

	// Place the powerup at the starting point
	m_Position.x = pos.x;
	m_Position.y = pos.y;
	m_Sprite.setPosition(m_Position);
}

FloatRect Powerup::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite Powerup::getSprite()
{
	return m_Sprite;
}