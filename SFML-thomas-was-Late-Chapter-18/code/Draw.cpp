#include "Engine.h"

using namespace sf;
using namespace std;

void Engine::draw()
{
	// Rub out the last frame
	m_Window.clear(Color::White);
	
	// Update the shader parameters
	m_RippleShader.setUniform("uTime", m_GameTimeTotal.asSeconds());

	// Switch to background view
	m_Window.setView(m_BGMainView);
	// Draw the background
	m_Window.draw(m_BackgroundSprite);

	// Draw the background, complete with shader effect
	m_Window.draw(m_BackgroundSprite, &m_RippleShader);

	// Switch to m_MainView
	m_Window.setView(m_MainView);		

	// Draw the Level
	m_Window.draw(m_VALevel, &m_TextureTiles);

	// Draw thomas
	m_Window.draw(m_Thomas.getSprite());

	for (int i = 0; i < m_Enemies.size(); i++)
	{
		m_Window.draw(m_Enemies[i].getSprite());
	}

	for (int i = 0; i < m_Powerups.size(); i++)
	{
		m_Window.draw(m_Powerups[i].getSprite());
	}

	for (int i = 0; i < 100; i++)
	{
		if (bullets[i].isInFlight())
		{
			m_Window.draw(bullets[i].getShape());
		}
	}

	// Draw the particle system
	if (m_PS.running())
	{
		m_Window.draw(m_PS);
	}
	
	// Draw the HUD
	// Switch to m_HudView
	m_Window.setView(m_HudView);
	m_Window.draw(m_Hud.getLevel());
	m_Window.draw(m_Hud.getTime());

	if (m_Thomas.isTimeFrozen())
	{
		// Draw the frozen overlay
		m_Window.draw(frozenOverlay);
	}

	if (!m_Playing)
	{
		m_Window.draw(m_Hud.getMessage());
	}
	
	// Show everything we have just drawn
	m_Window.display();
}