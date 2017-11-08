#pragma once

#include "State.h"
#include "Game.h"

#include <SFML\Graphics.hpp>

#define splashTime 3

class SplashState : public State {
public:
	SplashState(GameDataRef data) : _data(data) {}

	virtual void Init();
	virtual void BeforeDestroy();

	virtual void Update(float dt);
	virtual void Draw();

private:
	GameDataRef _data;

	sf::Sprite background;

	sf::Clock clock;

};