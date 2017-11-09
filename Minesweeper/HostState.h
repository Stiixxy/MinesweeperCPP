#pragma once

#include "DEFENITIONS.h"
#include "State.h"
#include "Game.h"
#include "MainState.h"

#include "TextBox.h"

class HostState : public State {
public:
	HostState(GameDataRef data) : _data(data) {}

	virtual void Init();
	virtual void BeforeDestroy();

	virtual void Update(float dt);
	virtual void Draw();

private:
	GameDataRef _data;

	TextBox *portTextbox;


};