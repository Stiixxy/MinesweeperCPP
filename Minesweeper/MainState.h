#pragma once
#include <string>

#include "State.h"
#include "Game.h"
#include "Grid.h"
#include "TileMap.h"
#include "EventSaver.h"
#include "MainStateGui.h"

class MainState : public State {
public:
	MainState(GameDataRef data) : _data(data) {}

	virtual void Init();
	virtual void BeforeDestroy(); //For cleanup

	virtual void Update(float dt);
	virtual void Draw();

	void PollEvents(float dt);
	void HandleInput(float dt);

	void UpdateMap();
	bool LoadFromFile(std::string);
private:
	MainStateGui *gui;
	GameDataRef _data;
	Grid *grid;
	TileMap *map;
	EventSaver *saver;

	sf::View gridView;

	bool _clickedLastFrame = false;
	bool _alive = true;
	int points = 0;
};