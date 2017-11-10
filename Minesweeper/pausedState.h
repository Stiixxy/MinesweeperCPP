#pragma once

#include "State.h"
#include "Game.h"

#include "Button.h"
#include "Button.cpp"

#include <SFML\Graphics.hpp>

class PausedState : public State {
public:
	PausedState(GameDataRef data) : _data(data) {}

	virtual void Init();
	virtual void BeforeDestroy();

	virtual void Update(float dt);
	virtual void Draw();

	void OnExitClick();

private:
	GameDataRef _data;

	sf::RectangleShape background;

	sf::Text pausedText;

	Button<PausedState> *exitButton;

	bool keyIsPressed = true;
};