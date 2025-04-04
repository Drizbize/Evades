#include "game.h"

Game::Game(int x, int y)
	: window(std::make_shared<sf::RenderWindow>(sf::VideoMode(x, y), GAME_NAME, sf::Style::Close | sf::Style::Titlebar)),
	fpsShowTimer(FPS_SHOW_UPDATE, &dt)
{
	srand(time(0));

	Service<LogManager>::build(LogLevel::Debug);

	Get<LogManager>().addDriver(new ConsoleLogDriver); // deletes in LogManager


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
	m_currentTime = m_clock.getElapsedTime();
	dt = (m_currentTime.asSeconds() - m_previousTime.asSeconds());
	m_previousTime = m_currentTime;

	float fps = 1.0f / dt;
	if (fpsShowTimer.isEnded())
	{
		std::string text = (std::string)GAME_NAME + " - FPS: " + str(round(fps));
		window->setTitle(sf::String(text.c_str()));
	}
}
