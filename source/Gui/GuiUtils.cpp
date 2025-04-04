#include "GuiUtils.h"

Udim::Udim(const Udim& other)
{
	scale = other.scale;
	offset = other.offset;
}

Udim::Udim(float scale, float offset): scale(scale), offset(offset)
{
}

Udim Udim::operator+(const Udim& other)
{
	return Udim(scale + other.scale, offset + other.offset);
}

Udim Udim::operator-(const Udim& other)
{
	return Udim(scale - other.scale, offset - other.offset);
}

Udim Udim::operator* (float mult)
{
	return Udim(scale * mult, offset * mult);
}

bool Udim::operator==(const Udim& other)
{
	return (scale == other.scale && offset == other.offset);
}

bool Udim::operator!=(const Udim& other)
{
	return (scale != other.scale || offset != other.offset);
}

// ---------------------------

Udim2::Udim2(const Udim2& other)
{
	posX = other.posX;
	posY = other.posY;
}

Udim2::Udim2(float scaleX, float offsetX, float scaleY, float offsetY)
	: posX(Udim(scaleX, offsetX)), posY(Udim(scaleY, offsetY))
{
}

Udim2::Udim2(Udim x, Udim y): posX(x), posY(y)
{
}

Udim2 Udim2::fromScale(float x, float y)
{
	return Udim2(x, 0, y, 0);
}

Udim2 Udim2::fromOffset(float x, float y)
{
	return Udim2(0, x, 0, y);
}

sf::Vector2f Udim2::getScale() const
{
	return sf::Vector2f(posX.scale, posY.scale);
}

sf::Vector2f Udim2::getOffset() const
{
	return sf::Vector2f(posX.offset, posY.offset);
}

sf::Vector2f Udim2::get2dSize(const sf::Vector2f& windowSize) const
{
	return getOffset() + sf::Vector2f(getScale().x * windowSize.x, getScale().y * windowSize.y);
}

void Udim2::setScale(float x, float y)
{
	posX.scale = x;
	posY.scale = y;
}

void Udim2::setOffset(float x, float y)
{
	posX.offset = x;
	posY.offset = y;
}

Udim2 Udim2::operator+(const Udim2& other)
{
	return Udim2(posX + other.posX, posY + other.posY);
}

Udim2 Udim2::operator-(const Udim2& other)
{
	return Udim2(posX - other.posX, posY - other.posY);
}

Udim2 Udim2::operator* (float mult)
{
	return Udim2(posX * mult, posY * mult);
}

bool Udim2::operator==(const Udim2& other)
{
	return (posX == other.posX && posY == other.posY);
}

bool Udim2::operator!=(const Udim2& other)
{
	return (posX != other.posX || posY != other.posY);
}

// -------

bool FontManager::isInit = false;
std::map<FontType, sf::Font> FontManager::m_fontMap;

void FontManager::init()
{
	m_fontMap[FontType::Arial] = getLoadedFont(FontType::Arial);

	isInit = true;
}

const sf::Font& FontManager::getFont(FontType font)
{
	if (!isInit)
	{
		init();
	}
	return m_fontMap[font];
}

sf::Font FontManager::getLoadedFont(FontType type)
{
	sf::Font font;
	switch (type)
	{
	case FontType::Arial:
		font.loadFromFile("Resources/Fonts/Arial.ttf");
		break;
	default:
		break;
	}

	return font;
}

float getWidthOfText(const sf::Text& text)
{
	return text.getLocalBounds().width;
}
