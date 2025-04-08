#include "game.h"

Game::Game(uint x, uint y)
	: window(std::make_shared<sf::RenderWindow>(sf::VideoMode({x, y}), GAME_NAME, sf::Style::Close | sf::Style::Titlebar)),
	fpsShowTimer(FPS_SHOW_UPDATE, &dt)
{
	srand(time(0));

	Service<LogManager>::build(LogLevel::Debug);
	Get<LogManager>().addDriver(new ConsoleLogDriver); // deletes in LogManager

	m_clock.start();
}

Game::~Game()
{

}

void Game::logic()
{

}

void Game::render()
{

}

void Game::update_dt()
{
	dt = m_clock.restart().asSeconds();

	float fps = 1.0f / dt;
	if (fpsShowTimer.isEnded())
	{
		std::string text = (std::string)GAME_NAME + " - FPS: " + str(round(fps));
		window->setTitle(sf::String(text.c_str()));
	}
}
