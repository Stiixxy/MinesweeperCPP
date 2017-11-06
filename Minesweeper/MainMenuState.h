#pragma once
#include <string>

#include "State.h"
#include "Game.h"

#include "Button.h"
#include "Button.cpp"

class MainMenuState : public State {
public:
	MainMenuState(GameDataRef data) : _data(data) {}

	virtual void Init();
	virtual void BeforeDestroy(); //For cleanup

	virtual void Update(float dt);
	virtual void Draw();

	void PollEvents(float dt);
	void InMemberFunction();
private:
	GameDataRef _data;

	Button<MainMenuState> *b;
};