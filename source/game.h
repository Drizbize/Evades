#pragma once

#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <memory>

#include "SFML/Graphics.hpp"

#include "Settings.h"

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

	Game(uint x, uint y);
	~Game();

	void logic();
	void render();
	void update_dt();

private:
	sf::Clock m_clock;
	utls::Timer fpsShowTimer;
};