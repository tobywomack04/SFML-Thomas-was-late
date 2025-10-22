#include "Powerup.h"
#include "TextureHolder.h"

using namespace sf;
using namespace std;

Powerup::Powerup(Vector2f pos, string type)
{
	// Associate a texture with the sprite
	if (type == "Freeze")
	{
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/powerups/snowflake.png"));
		m_Type = "Freeze";
	}
	else if (type == "Speed")
	{
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/powerups/donut.png"));
		m_Type = "Speed";
	}
	else // Jump powerup
	{
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/powerups/rabbit.png"));
		m_Type = "Jump";
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

string Powerup::getType() {
	return m_Type;
}