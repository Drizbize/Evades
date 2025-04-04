#include "Base.h"

Igui::Igui()
{
	position.bind(updateFunc);
	size.bind(updateFunc);
	anchorPoint.bind(updateFunc);
	transparency.bind(updateFunc);
}

Igui::~Igui()
{
	for (Igui* child : children)
	{
		delete child;
	}
}

void Igui::render()
{
	m_render();
	for (Igui* gui : children)
	{
		gui->render();
	}
}

void Igui::update()
{
	m_update();
	for (Igui* gui : children)
	{
		gui->update();
	}
}

std::pair<sf::Vector2f, sf::Vector2f> Igui::getUpdatedPosSize()
{
	sf::Vector2f Pos, Size;

	if (m_parentFrame)
	{
		auto [rPos, rSize] = m_parentFrame->getUpdatedPosSize();
		Pos = rPos;
		Size = rSize;
	}
	else
	{
		Pos = { 0.f, 0.f };
		Size = (sf::Vector2f)m_window->getSize();

		//LogManager::Info(str(Size.x) + " " + str(Size.y));
		//LogManager::Info(str(size->posX.offset) + " " + str(size->posX.offset));
	}

	sf::Vector2f frameSize = size->get2dSize(Size);
	sf::Vector2f anchorPos = sf::Vector2f(anchorPoint->x * frameSize.x, anchorPoint->y * frameSize.y);

	return { position->get2dSize(Size) + Pos - anchorPos, frameSize };
}
