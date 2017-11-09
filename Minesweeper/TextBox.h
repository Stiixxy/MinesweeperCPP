#pragma once

#include <SFML\Graphics.hpp>
#include "Game.h"

#include <vector>

#define DOTTIME 0.2
#define TEXTCOLOR sf::Color::Red

class TextBox : public sf::Drawable {
public:
	TextBox(sf::Sprite, sf::Font*, GameDataRef data);

	void Update();

	void CenterX();
	void CenterY();
	void Center();
	void AutoSetFontSize(float percent = 1);
	void CenterText();

	void Init(sf::String s, int maxLength);

	void AddKey(sf::Event keyEvent);
	void UpdateString();
	
	sf::String GetValue();
	sf::Sprite *GetSprite();
public:
	GameDataRef _data;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool TextFits(float percent);

	sf::Sprite _sprite;
	sf::Text _text;

	sf::Clock dotUpdateClock;
	std::vector<char> _value;

	bool hasDot = false;
};