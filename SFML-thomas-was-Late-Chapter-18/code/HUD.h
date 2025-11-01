#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

class Hud
{
private:
	Font m_Font;
	Text m_StartText;
	Text m_TimeText;
	Text m_LevelText;
	Text scoreBoardText;
	Text scoreBoardHeading;

public:
	Hud();
	Text getMessage();
	Text getLevel();
	Text getTime();

	void setLevel(String text);
	void setTime(String text);

	void setScoreboard(String text);
	Text getScoreboard();
	Text getScoreboardHeading();
};