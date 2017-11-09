#pragma once

#include "DEFENITIONS.h"
#include "State.h"
#include "Game.h"
#include "MainState.h"

#include "TextBox.h"
#include "Button.h"
#include "Button.cpp"

class ClientState : public State {
public:
	ClientState(GameDataRef data) : _data(data) {}

	virtual void Init();
	virtual void BeforeDestroy();

	virtual void Update(float dt);
	virtual void Draw();

	void OnJoinClick();
	void OnBackClick();

private:
	GameDataRef _data;

	sf::Text portText;
	TextBox *portTextbox;

	sf::Text ipText;
	TextBox *ipTextbox;

	TextBox *activeTextBox;

	Button<ClientState> *joinButton;
	Button<ClientState> *backButton;

};