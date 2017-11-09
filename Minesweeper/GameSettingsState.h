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
	void OnMultiplayerClick();
	void OnBackClick();

	void OnHeightUp();
	void OnHeightDown();

	void OnWidthUp();
	void OnWidthDown();

	void OnBombsUp();
	void OnBombsDown();

private:
	GameDataRef _data;

	sf::Text gridText;

	sf::Text gridSizeText;
	sf::Text bombCountText;

	int gridWidth = DEFAULT_GRID_WIDTH, gridHeight = DEFAULT_GRID_HEIGHT;
	int bombs = DEFAULT_GRID_BOMBS;

	Button<GameSettingsState> *heightUP;
	Button<GameSettingsState> *heightDOWN;

	Button<GameSettingsState> *widthUP;
	Button<GameSettingsState> *widthDOWN;
	
	Button<GameSettingsState> *bombsUP;
	Button<GameSettingsState> *bombsDOWN;

	Button<GameSettingsState> *startButton;
	Button<GameSettingsState> *backButton;
	Button<GameSettingsState> *multiplayerButton;

};