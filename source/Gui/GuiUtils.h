#pragma once

#include <SFML/Graphics.hpp>
#include <map>

struct Udim
{
	float scale;
	float offset;

	Udim(const Udim& other);
	Udim(float scale = 0, float offset = 0);

	Udim operator+ (const Udim& other);
	Udim operator- (const Udim& other);
	Udim operator* (float mult);
	bool operator== (const Udim& other);
	bool operator!= (const Udim& other);
};

struct Udim2
{
	Udim posX;
	Udim posY;

	Udim2() {}
	Udim2(const Udim2& other);
	Udim2(float scaleX, float offsetX, float scaleY, float offsetY);
	Udim2(Udim x, Udim y);
	static Udim2 fromScale(float x, float y);
	static Udim2 fromOffset(float x, float y);

	sf::Vector2f getScale() const;
	sf::Vector2f getOffset() const;
	sf::Vector2f get2dSize(const sf::Vector2f& windowSize) const;

	void setScale(float x, float y);
	void setOffset(float x, float y);

	Udim2 operator+ (const Udim2& other);
	Udim2 operator- (const Udim2& other);
	Udim2 operator* (float mult);
	bool operator== (const Udim2& other);
	bool operator!= (const Udim2 & other);
};

enum class TextDir
{
	Left = 0,
	Right,
	Center
};

enum class FontType
{
	Arial = 0,
};

class FontManager
{
public:
	static void init();
	static const sf::Font& getFont(FontType font);

private:
	FontManager() = default;

	static bool isInit;
	static std::map<FontType, sf::Font> m_fontMap;
	static sf::Font getLoadedFont(FontType type); // !!! -Font paths- !!!
};


// -------- FUNCTIONS -----------

float getWidthOfText(const sf::Text& text);