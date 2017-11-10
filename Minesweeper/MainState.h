#pragma once
#include <string>
#include <queue>

#include "State.h"
#include "Game.h"
#include "Grid.h"
#include "TileMap.h"
#include "EventSaver.h"
#include "MainStateGui.h"

#include "Button.h"
#include "Button.cpp"

/*
TODO:
	-add dynamic option for bombs and size for the host
*/

class MainState : public State {
public:
	MainState(GameDataRef data, sf::Vector2i gridsize, int bombCount) : _data(data), newGridSize(gridsize), newBombCount(bombCount) {}
	MainState(GameDataRef data, std::string save) : _data(data), loadSave(save) {}
	MainState(GameDataRef data, int port, sf::Vector2i gridsize, int bombCount) : _data(data), _port(port), newGridSize(gridsize), newBombCount(bombCount) {}
	MainState(GameDataRef data, int port, sf::IpAddress ip) : _data(data), _port(port), _ip(ip) {}

	virtual void Init();
	virtual void BeforeDestroy(); //For cleanup

	virtual void Update(float dt);
	virtual void Draw();

	void PollEvents(float dt);
	void HandleInput(float dt);

	void OnSaveClick();
	void ExecuteEvent(Event e);

	void UpdateMap();
	bool LoadFromFile(std::string);


private:
	MainStateGui *gui;
	GameDataRef _data;
	Grid *grid;
	TileMap *map;
	EventSaver *saver;

	float playTime = 0;

	sf::View gridView;

	bool _clickedLastFrame = true;
	bool _alive = true;
	int points = 0;

	Button<MainState> *saveButton;

	sf::Sound bombSound;
	sf::Sound applauseSound;

	std::string loadSave;
	sf::Vector2i newGridSize;
	int newBombCount;

	int _port = -1;
	sf::IpAddress _ip = sf::IpAddress::None;

};