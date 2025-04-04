#pragma once

#include "Base.h"
#include "Utils/utils.h"
#include "SFML/Graphics.hpp"
#include "Utils/LogManager.h"

class Frame : public Igui
{
public:
	utls::EventVar<sf::Color> frameColor = sf::Color(215, 215, 215);
	utls::EventVar<sf::Color> outlineColor = sf::Color(20, 10, 25);
	utls::EventVar<float> thickness = 2.f;

	Frame(sf::RenderWindow& window, const Udim2& size = Udim2::fromOffset(150, 75));
	~Frame();
private:
	sf::RectangleShape m_rect;

	virtual void m_render() override;
	virtual void m_update() override;
};