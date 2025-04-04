#pragma once

#include <iostream>
#include <vector>
#include <time.h>
#include <string>

#include "SFML/Graphics.hpp"

#include "ConstSettings.h"

#include "Utils/utils.h"
#include "Utils/LogManager.h"
#include "Utils/Service.h"

#include "Utils/Tween.h"

#include "Gui/Frame.h"

class Game
{
public:
	float dt = 0;
	std::shared_ptr<sf::RenderWindow> window;

	Game(int x, int y);
	~Game();

	void logic();
	void render();
	void update_dt();

private:
	sf::Clock m_clock;
	sf::Time m_previousTime = m_clock.getElapsedTime();
	sf::Time m_currentTime;
	utls::Timer fpsShowTimer;
};