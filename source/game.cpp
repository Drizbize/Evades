#include "game.h"
#include "Settings.h"
#include <chrono>
#include <thread>

Game::Game(uint x, uint y)
	: window(std::make_shared<sf::RenderWindow>(sf::VideoMode({x, y}), GAME_NAME, sf::Style::Close | sf::Style::Titlebar)),
	fpsShowTimer(Settings::FPS_SHOW_UPDATE, &dt)
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
    auto workTime = m_clock.getElapsedTime().asSeconds();
    Settings::waitByMaxFPS(workTime);

    float dt = m_clock.restart().asSeconds();

    float fps = 1.f / dt;
    if (fpsShowTimer.isEnded())
    {
        std::string text = std::string(GAME_NAME) + " - FPS: " + std::to_string(std::lround(fps));
        window->setTitle(text);
    }
}
