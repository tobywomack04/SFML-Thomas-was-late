#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace sf;
using namespace std;

void Engine::update(float dtAsSeconds)
{
	if (m_NewLevelRequired)
	{
		// Load a level
		loadLevel();

		// Seed the random number generator
		srand(time(NULL));
		
		if (m_LM.getCurrentLevel() == 1 && takeScore)
		{
			addHighScore(highScore);
			updateSaveFile();
			highScore = 0;
			takeScore = false;
		}
		else if (m_LM.getCurrentLevel() == 4)
		{
			takeScore = true;
		}
	}
	
	if (m_Playing)
	{
		if (!paused)
		{
			// Update Thomas
			m_Thomas.update(dtAsSeconds);
		}

		/* Detect collisions and see if characters have reached the goal tile
		The second part of the if condition is only executed when thomas is touching the home tile */
		if (detectCollisions(m_Thomas))
		{
			// New level required
			m_NewLevelRequired = true;

			// Play the reach goal sound
			m_SM.playReachGoal();

			highScore += (m_LM.getTimeLimit() - m_TimeRemaining);
		}

		stringstream ss;
		for (float score : scoreBoard)
		{
			ss << fixed << setprecision(5) << score << "\n";
		}

		m_Hud.setScoreboard(ss.str());

		if (!m_Thomas.isTimeFrozen() && !paused)
		{
			// Count down the time the player has left
			m_TimeRemaining -= dtAsSeconds;

			// Have Thomas and Bob run out of time?
			if (m_TimeRemaining <= 0)
			{
				m_NewLevelRequired = true;
			}

			for (int i = 0; i < m_Enemies.size(); i++)
			{
				// Update the enemy
				m_Enemies[i].update(dtAsSeconds, m_Thomas.getPosition());

				if (m_Enemies[i].getType() == "Turret" && shotTimer.getElapsedTime().asSeconds() > 2)
				{
					// Pass the centre of the player and the centre of the crosshair to the shoot function
					int randDir = rand() % 2; // 0 or 1

					switch (randDir)
					{
					case 0:
						bullets[currentBullet].shoot(m_Enemies[i].getCentre().x, m_Enemies[i].getCentre().y, m_Enemies[i].getCentre().x + 500, m_Enemies[i].getCentre().y);
						m_Enemies[i].faceRight();
						break;

					case 1:
						bullets[currentBullet].shoot(m_Enemies[i].getCentre().x, m_Enemies[i].getCentre().y, m_Enemies[i].getCentre().x - 500, m_Enemies[i].getCentre().y);
						m_Enemies[i].faceLeft();
						break;
					}
					
					currentBullet++;

					if (currentBullet > 99)
					{
						currentBullet = 0;
					}

					shotTimer.restart();
				}
			}

			// Update any bullets that are in-flight
			for (int i = 0; i < 50; i++)
			{
				if (bullets[i].isInFlight())
				{
					bullets[i].update(dtAsSeconds);
				}
			}
		}
	}// End if playing

	// Check if a fire sound needs to be played
	vector<Vector2f>::iterator it;

	// Iterate through the vector of Vector2f objects
	for (it = m_FireEmitters.begin(); it != m_FireEmitters.end(); it++)
	{
		// Where is this emitter?
		// Store the location in pos
		float posX = (*it).x;
		float posY = (*it).y;

		// is the emiter near the player?
		// Make a 500 pixel rectangle around the emitter
		FloatRect localRect(posX - 250, posY - 250, 500, 500);

		// Is the player inside localRect?
		if (m_Thomas.getPosition().intersects(localRect))
		{
			// Play the sound and pass in the location as well
			m_SM.playFire(Vector2f(posX, posY), m_Thomas.getCenter());
		}
	}
		
	m_MainView.setCenter(m_Thomas.getCenter());

	// Time to update the HUD?
	// Increment the number of frames since the last HUD calculation
	m_FramesSinceLastHUDUpdate++;

	// Update the HUD every m_TargetFramesPerHUDUpdate frames
	if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
	{
		// Update game HUD text
		stringstream ssTime;
		stringstream ssLevel;

		// Update the time text
		ssTime << (int)m_TimeRemaining;
		m_Hud.setTime(ssTime.str());

		// Update the level text
		ssLevel << "Level:" << m_LM.getCurrentLevel();
		m_Hud.setLevel(ssLevel.str());

		m_FramesSinceLastHUDUpdate = 0;
	}

	// Update the particles
	if (m_PS.running())
	{
		m_PS.update(dtAsSeconds);
	}
}// End of update function