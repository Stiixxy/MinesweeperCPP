#pragma once
#include <string>
#include "DEFENITIONS.h"
#include "State.h"
#include "Game.h"
#include "MainState.h"

#include "Button.h"
#include "Button.cpp"

class GameSettingsState : public State {
public:
	GameSettingsState(GameDataRef data) : _data(data) {}

	virtual void Init();
	virtual void BeforeDestroy(); //For cleanup

	virtual void Update(float dt);
	virtual void Draw();

	void InitGUI();

	void PollEvents(float dt);

	void OnStartClick();

	void OnHeightUp();
	void OnHeightDown();

	void OnWidthUp();
	void OnWidthDown();

private:
	GameDataRef _data;

	sf::Text gridSizeText;
	sf::Text gridText;
	int gridWidth = DEFAULT_GRID_WIDTH, gridHeight = DEFAULT_GRID_HEIGHT;

	Button<GameSettingsState> *heightUP;
	Button<GameSettingsState> *heightDOWN;

	Button<GameSettingsState> *widthUP;
	Button<GameSettingsState> *widthDOWN;

	Button<GameSettingsState> *startButton;

};