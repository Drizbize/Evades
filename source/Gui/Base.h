#pragma once

#include <list>

#include "SFML/Graphics.hpp"
#include "GuiUtils.h"
#include "Utils/utils.h"
#include "Utils/LogManager.h"

#define updateFunc std::bind(&Igui::update, this)

// Interface of gui class, to create a new gui class first param must be 'sf::RenderWindow&'
class Igui
{
public:
	utls::EventVar<Udim2> position = Udim2();
	utls::EventVar<Udim2> size = Udim2();
	utls::EventVar<sf::Vector2f> anchorPoint = sf::Vector2f(0.f, 0.f);
	utls::EventVar<float> transparency = 0.f;

	std::list<Igui*> children;

	Igui();
	virtual ~Igui();

	void render();
	void update();

	template<typename T, typename... Args>
	T& addChild(Args&&... args)
	{
		T* newGui = new T(*m_window, std::forward<Args>(args)...);
		children.push_back(newGui);

		newGui->m_parentFrame = this;

		return *newGui;
	}
protected:
	sf::RenderWindow* m_window = nullptr;
	Igui* m_parentFrame = nullptr;

	//void updateChildren();
	//void renderChildren();

	virtual void m_render() = 0;
	virtual void m_update() = 0;

	std::pair<sf::Vector2f, sf::Vector2f> getUpdatedPosSize();
};