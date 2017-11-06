#pragma once

#include <SFML\Graphics.hpp>
#include "Game.h"

class Button : public sf::Drawable {
public:
	Button(sf::Sprite, GameDataRef data, void(*onclick)(void *creator), void *creator);

	void Update();

	sf::Sprite *GetSprite();

	void CenterX();
	void CenterY();
	void Center();

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	sf::Sprite _sprite;
	void *_creator;
	void(*onClick)(void*);

	bool WasClicked = false;

	GameDataRef data;
};