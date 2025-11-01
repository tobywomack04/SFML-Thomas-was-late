#include "Engine.h"
#include <iostream>

using namespace sf;
using namespace std;

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			// Handle the player quitting
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				m_Window.close();
			}

			// Handle the player starting the game
			if (Keyboard::isKeyPressed(Keyboard::Return) && !m_Playing)
			{
				m_Playing = true;

				createNewSave();

				gameStarted = true;
			}

			if (Keyboard::isKeyPressed(Keyboard::Tab))
			{
				if (!paused)
				{
					paused = true;
				}
				else
				{
					paused = false;
				}
			}
		}
	}	

	// Handle input specific to Thomas
	if (m_Thomas.handleInput())
	{
		// Play a jump sound
		m_SM.playJump();
	}
}