#include "Frame.h"

Frame::Frame(sf::RenderWindow& window, const Udim2& size)
{
	m_window = &window;

	frameColor.bind(updateFunc);
	outlineColor.bind(updateFunc);
	thickness.bind(updateFunc);

	this->size = size;
	update();
}

Frame::~Frame()
{
}

void Frame::m_render()
{
	m_window->draw(m_rect);
}

void Frame::m_update()
{
	//LogManager::Info("Updated!");

	auto [Pos, Size] = getUpdatedPosSize();

	m_rect.setSize(Size);
	m_rect.setPosition(Pos);

	transparency = std::clamp(transparency.get(), 0.f, 1.f);

	frameColor->a = (1 - transparency) * 255;
	outlineColor->a = (1 - transparency) * 255;

	m_rect.setFillColor(frameColor);
	m_rect.setOutlineThickness(thickness);
	m_rect.setOutlineColor(outlineColor);
}
