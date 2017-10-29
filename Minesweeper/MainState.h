#pragma once

#include "State.h"
#include "Game.h"
#include "Grid.h"
#include "TileMap.h"

class MainState : public State {
public:
	MainState(GameDataRef data) : _data(data) {}

	virtual void Init();
	virtual void BeforeDestroy(); //For cleanup

	virtual void Update(float dt);
	virtual void Draw();

	void PollEvents(float dt);
	void HandleInput(float dt);
private:
	GameDataRef _data;
	Grid *grid;
	TileMap *map;

	sf::View gridView;

	bool _clickedLastFrame = false;
	bool _alive = true;
};