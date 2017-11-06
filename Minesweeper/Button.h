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

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	T *_t;

	sf::Sprite _sprite;
	void *_creator;
	void(T::*onClick)();

	bool WasClicked = false;

	GameDataRef data;
};