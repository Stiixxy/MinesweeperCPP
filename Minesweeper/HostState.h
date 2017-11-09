#pragma once

#include "DEFENITIONS.h"
#include "State.h"
#include "Game.h"
#include "MainState.h"

#include "TextBox.h"
#include "Button.h"
#include "Button.cpp"

class HostState : public State {
public:
	HostState(GameDataRef data) : _data(data) {}

	virtual void Init();
	virtual void BeforeDestroy();

	virtual void Update(float dt);
	virtual void Draw();

	void OnHostClick();
	void OnBackClick();

private:
	GameDataRef _data;

	sf::Text portText;
	TextBox *portTextbox;

	Button<HostState> *hostButton;
	Button<HostState> *backButton;

};