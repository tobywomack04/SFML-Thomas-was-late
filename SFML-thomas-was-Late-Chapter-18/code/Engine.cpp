#include "Engine.h"
#include <fstream>
#include <iomanip>
#include <iostream>'

using namespace sf;
using namespace std;

void Engine::createNewSave()
{
	ofstream saveFile("gameData/score/highscores.txt");

	if (!saveFile.is_open())
	{
		cerr << "Error creating save file" << endl;
		return;
	}
	
	for (size_t i = 0; i < scoreBoard.size(); i++)
	{
		saveFile << fixed << setprecision(5) << scoreBoard[i];
		
		if (i < scoreBoard.size() - 1)
		{
			saveFile << " ";
		}
	}

	saveFile << endl;
}

bool Engine::loadSaveFile()
{
	ifstream loadFile("gameData/score/highscores.txt");

	if (!loadFile.is_open())
	{
		cout << "No save file found" << endl;
		return false;
	}

	for (size_t i = 0; i < scoreBoard.size(); i++)
	{
		if (!(loadFile >> scoreBoard[i]))
		{
			cout << "Error reading score at index " << i << endl;
			return false;
		}
	}

	cout << "Score loaded" << endl;
	return true;
}

void Engine::updateSaveFile()
{
	ofstream saveFile("gameData/score/highscores.txt");

	if (!saveFile.is_open())
	{
		cerr << "Failed to open save file for writing" << endl;
		return;
	}

	for (size_t i = 0; i < scoreBoard.size(); i++)
	{
		saveFile << fixed << setprecision(5) << scoreBoard[i];
		
		if (i < scoreBoard.size() - 1)
		{
			saveFile << " ";
		}
	}

	saveFile << endl;
}

void Engine::addHighScore(float newScore)
{
	for (int i = 0; i < scoreBoard.size(); i++)
	{
		if (newScore < scoreBoard[i] || scoreBoard[i] == 0)
		{
			for (int j = i; j < scoreBoard.size(); j++)
			{
				float temp = scoreBoard[j];
				scoreBoard[j] = newScore;
				newScore = temp;
			}

			break;
		}
	}
}

Engine::Engine() : m_Enemies(m_LM.getEnemies()), m_Powerups(m_LM.getPowerups())
{
	// Get the screen resolution and create an SFML window and View
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(resolution.x, resolution.y), "Thomas was late", Style::Fullscreen);

	// Initialize the full screen view
	m_MainView.setSize(resolution);
	m_HudView.reset(FloatRect(0, 0, resolution.x, resolution.y));

	// Inititialize the split-screen Views
	m_LeftView.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));

	m_RightView.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));

	m_BGLeftView.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));

	m_BGRightView.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));
	
	frozenOverlay.setSize((Vector2f(m_Window.getSize().x, m_Window.getSize().y)));
	frozenOverlay.setFillColor(sf::Color(173, 216, 230, 50));

	// Can this graphics card use shaders?
	if (!sf::Shader::isAvailable())
	{
		// Time to get a new PC
		m_Window.close();
	}
	else
	{
		// Load two shaders (1 vertex, 1 fragment)
		m_RippleShader.loadFromFile("shaders/vertShader.vert", "shaders/rippleShader.frag");
	}

	m_BackgroundTexture = TextureHolder::GetTexture("graphics/background.png");

	// Associate the sprite with the texture
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	// Load the texture for the background vertex array
	m_TextureTiles = TextureHolder::GetTexture("graphics/tiles_sheet.png");

	// Initialize the particle system
	m_PS.init(1000);

	scoreBoard.resize(10);

}// End Engine constructor

void Engine::run()
{
	// Timing 	
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();

		// Update the total game time
		m_GameTimeTotal += dt;

		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();
	}
}