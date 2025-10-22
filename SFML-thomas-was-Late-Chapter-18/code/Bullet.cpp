#include "bullet.h"
#include <iostream>

// The constructor
Bullet::Bullet()
{
	m_BulletShape.setSize(sf::Vector2f(10, 10));
	m_BulletShape.setFillColor(Color::Red);
    m_BulletShape.setOrigin(m_BulletShape.getSize() / 2.f);
}

void Bullet::shoot(float startX, float startY, float targetX, float targetY)
{
	// Calculate normalized direction vector
	sf::Vector2f direction(targetX - startX, targetY - startY);
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0.f)
		direction /= length;
	else
		direction = sf::Vector2f(1.f, 0.f); // fallback

	// Mark in flight
	m_InFlight = true;

	// Spawn bullet slightly in front of the turret
	float spawnOffset = (m_BulletShape.getSize().x * 0.9f);
	m_Position = Vector2f(startX + direction.x * spawnOffset, startY + direction.y * spawnOffset);

	// Bullet velocity components
	m_BulletDistanceX = direction.x * m_BulletSpeed;
	m_BulletDistanceY = direction.y * m_BulletSpeed;

	// Position the shape
	m_BulletShape.setPosition(m_Position);

	// Set max range from the shooter
	float range = 3000.f;
	m_MinX = startX - range;
	m_MaxX = startX + range;
	m_MinY = startY - range;
	m_MaxY = startY + range;
}

void Bullet::stop()
{
	m_InFlight = false;
}

bool Bullet::isInFlight()
{
	return m_InFlight;
}

FloatRect Bullet::getPosition()
{
	return m_BulletShape.getGlobalBounds();
}

RectangleShape Bullet::getShape()
{
	return m_BulletShape;
}

void Bullet::update(float elapsedTime)
{
    // Update the bullet position
    m_Position.x += m_BulletDistanceX * elapsedTime;
    m_Position.y += m_BulletDistanceY * elapsedTime;

    m_BulletShape.setPosition(m_Position);

    // Use the center of the bullet for range checks
    Vector2f centerPos = m_Position + m_BulletShape.getSize() / 2.f;

    if (centerPos.x < m_MinX || centerPos.x > m_MaxX || centerPos.y < m_MinY || centerPos.y > m_MaxY)
    {
        m_InFlight = false;
    }
}