#pragma once

#include <SFML\Graphics.hpp>
#include "Game.h"


template <class T>
class Button : public sf::Drawable {
public:
	Button(sf::Sprite, GameDataRef data, void(T::*onclick)(), T *t);

	void Update();

	sf::Sprite *GetSprite();

	void CenterX();
	void CenterY();
	void Center();

	void InitText(sf::String s, sf::Font *f, int = 30);
	void SetText(sf::String s);
	void SetFont(sf::Font f);
	void SetFontSize(int i);

	void AutoSetFontSize(float percent = 1);
	void CenterText();

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool TextFits(float percent);

	T *_t;

	sf::Sprite _sprite;
	sf::Text _text;

	void(T::*onClick)();

	bool WasClicked = false;

	GameDataRef data;
};