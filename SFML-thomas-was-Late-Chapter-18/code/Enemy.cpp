#include "Enemy.h"
#include "TextureHolder.h"
#include <iostream>

using namespace sf;
using namespace std;

Enemy::Enemy(Vector2f pos, string type)
{
    // Associate a texture with the sprite
    if (type == "Sideswipe") {
        m_Sprite = Sprite(TextureHolder::GetTexture("graphics/Enemies/bob.png"));
    }
    else if (type == "Stalker") {
        m_Sprite = Sprite(TextureHolder::GetTexture("graphics/Enemies/eyeball.png"));
	}
	else { // Turret enemy
        m_Sprite = Sprite(TextureHolder::GetTexture("graphics/Enemies/turretRight.png"));
    }

    m_Type = type;

    // Place the enemy at the starting point
    m_StartPosition.x = pos.x;
    m_StartPosition.y = pos.y;
    m_Position.x = pos.x;
    m_Position.y = pos.y;
}

void Enemy::update(float dtAsSeconds, FloatRect playerPos) {

    if (m_Type == "Sideswipe") {
        if (m_Position.x > m_StartPosition.x + 100) {
            movingRight = false;
        }
        else if (m_Position.x < m_StartPosition.x - 100) {
            movingRight = true;
        }

        if (movingRight) {
            m_Position.x += m_Speed * dtAsSeconds;
        }
        else {
            m_Position.x -= m_Speed * dtAsSeconds;
        }

        m_Sprite.setPosition(m_Position);
    }
    else if (m_Type == "Stalker") {
        if (playerPos.getPosition().x > m_Position.x)
        {
            m_Position.x = m_Position.x +
                m_Speed * dtAsSeconds;
        }

        if (playerPos.getPosition().y > m_Position.y)
        {
            m_Position.y = m_Position.y +
                m_Speed * dtAsSeconds;
        }

        if (playerPos.getPosition().x < m_Position.x)
        {
            m_Position.x = m_Position.x -
                m_Speed * dtAsSeconds;
        }

        if (playerPos.getPosition().y < m_Position.y)
        {
            m_Position.y = m_Position.y -
                m_Speed * dtAsSeconds;
        }

        // Set position of the sprite
        m_Sprite.setPosition(m_Position);

        // Face the sprite in the correct direction
        float angle = (atan2(playerPos.getPosition().y - m_Position.y, playerPos.getPosition().x - m_Position.x) * 180) / 3.141;
        m_Sprite.setRotation(angle);
    }
	else { // Turret enemy
        m_Sprite.setPosition(m_Position);
    }
}

FloatRect Enemy::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite Enemy::getSprite()
{
	return m_Sprite;
}

string Enemy::getType() {
    return m_Type;
}

void Enemy::resetPosition() {
    m_Position.x = m_StartPosition.x;
    m_Position.y = m_StartPosition.y;
	m_Sprite.setPosition(m_Position);
}

Vector2f Enemy::getCentre()
{
    return Vector2f(m_Position.x + m_Sprite.getGlobalBounds().width / 2, m_Position.y + m_Sprite.getGlobalBounds().height / 2);
}

void Enemy::faceRight () {
    m_Sprite = Sprite(TextureHolder::GetTexture("graphics/Enemies/turretRight.png"));
}

void Enemy::faceLeft() {
    m_Sprite = Sprite(TextureHolder::GetTexture("graphics/Enemies/turretLeft.png"));
}