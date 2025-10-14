#include "Enemy.h"
#include "TextureHolder.h"
#include <iostream>

using namespace sf;
using namespace std;

Enemy::Enemy(Vector2f pos)
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/bob.png"));

	// Place the player at the starting point
	m_StartPosition.x = pos.x;
	m_StartPosition.y = pos.y;
	m_Position.x = pos.x;
	m_Position.y = pos.y;
}

void Enemy::update(float dtAsSeconds) {

    if (m_Position.x > m_StartPosition.x + 100) {
        movingRight = false;
    }
    else if (m_Position.x < m_StartPosition.x - 100) {
        movingRight = true;
    }

    if (movingRight) {
        m_Position.x += speed * dtAsSeconds;
    }
    else {
        m_Position.x -= speed * dtAsSeconds;
    }

    m_Sprite.setPosition(m_Position);
}

FloatRect Enemy::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite Enemy::getSprite()
{
	return m_Sprite;
}