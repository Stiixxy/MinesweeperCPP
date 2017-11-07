#include "DEFENITIONS.h"
#include "MainState.h" 
#include "EventSaver.h"
#include "Event.h"
#include <iostream>

void MainState::Init() {
	_data->assetManager.LoadTexture("Minesweeper spritesheet", TILE_SPRITESHEET);
	_data->assetManager.LoadTexture("Minesweeper numbers", NUMBERS_SPRITESHEET);
	saver = new EventSaver();

	if (loadSave.empty()) {
		grid = new Grid(newGridSize.x, newGridSize.y, saver);
		grid->RandomiseBombs(DEFAULT_GRID_BOMBS);
	} else {
		LoadFromFile(loadSave);
	}

	gridView = sf::View(sf::FloatRect(0, 0, grid->GetSize().x * SPRITE_WIDTH, grid->GetSize().y * SPRITE_HEIGHT));
	gridView.setViewport(sf::FloatRect(0, 1 - GRID_Y_PERCENTAGE, 1, GRID_Y_PERCENTAGE));

	map = new TileMap();
	map->setTexture(&_data->assetManager.GetTexture("Minesweeper spritesheet"));
	UpdateMap();
	gui = new MainStateGui(&points, &playTime,  &_data->assetManager.GetTexture("Minesweeper numbers"));
	
}

void MainState::BeforeDestroy() {
	_data->assetManager.UnloadTexture("Minesweeper spritesheet");
	_data->assetManager.UnloadTexture("Minesweeper numbers");
}

void MainState::Update(float dt) {
	_data->window.setView(gridView);
	PollEvents(dt);
	if (!_data->window.hasFocus()) return;
	HandleInput(dt);
	gui->Update();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _alive && !grid->HasWon()) {
		if (!_clickedLastFrame) {
			_clickedLastFrame = true;
			sf::Vector2i mousePos = _data->inputManager.GetMousePosition();
			sf::Vector2f worldPos = _data->window.mapPixelToCoords(mousePos);
			sf::Vector2i tilePos = grid->MouseToGridPos(worldPos);
			int result = grid->ClickTile(tilePos.x, tilePos.y);

			if (grid->HasWon())
				grid->ShowBombs();

			if (result != TILE_RETURNS::ALREAD_CLICKED) UpdateMap();
			if (result == TILE_RETURNS::BOMB) _alive = false;
		}
	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && _alive && !grid->HasWon()) {
		if (!_clickedLastFrame) {
			_clickedLastFrame = true;
			sf::Vector2i mousePos = _data->inputManager.GetMousePosition();
			sf::Vector2f worldPos = _data->window.mapPixelToCoords(mousePos);
			sf::Vector2i tilePos = grid->MouseToGridPos(worldPos);
			if (grid->ToggleFlag(tilePos.x, tilePos.y)) UpdateMap();
		}
	} else {
		_clickedLastFrame = false;
	}

	if (_alive && !grid->HasWon()) {
		playTime += dt;
	}

	points += grid->GetAndClearPoints();
}

void MainState::UpdateMap() {
	map->setTiles(sf::Vector2u(SPRITE_WIDTH, SPRITE_HEIGHT), grid->GetTiles(), grid->GetSize().x, grid->GetSize().y);
}

void MainState::Draw() {
	_data->window.setView(gridView);
	_data->window.draw(*map);
	_data->window.draw(*gui);
}

void MainState::PollEvents(float dt) {
	sf::Event event;
	while (_data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_data->window.close();
	}
}

void MainState::HandleInput(float dt) {
	//Zooming
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) {
		gridView.zoom(1.01);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) {
		gridView.zoom(0.99);
	}

	//Moving
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		gridView.move(-GRIDVIEW_MOVEMENT_SPEED * dt, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		gridView.move(GRIDVIEW_MOVEMENT_SPEED * dt, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		gridView.move(0, -GRIDVIEW_MOVEMENT_SPEED * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		gridView.move(0, GRIDVIEW_MOVEMENT_SPEED * dt);
	}

	//Fix position
	if (gridView.getCenter().x - gridView.getSize().x / 2 < 0) gridView.setCenter(gridView.getSize().x / 2, gridView.getCenter().y);
	if (gridView.getCenter().y - gridView.getSize().y / 2 < 0) gridView.setCenter(gridView.getCenter().x, gridView.getSize().y / 2);

	if (gridView.getSize().x > grid->GetSize().x * SPRITE_WIDTH) gridView.setSize(grid->GetSize().x * SPRITE_WIDTH, gridView.getSize().y);
	if (gridView.getSize().y > grid->GetSize().y * SPRITE_HEIGHT) gridView.setSize(gridView.getSize().x, grid->GetSize().y * SPRITE_HEIGHT);

	if (gridView.getCenter().y + gridView.getSize().y / 2 > grid->GetSize().y * SPRITE_HEIGHT) gridView.setCenter(gridView.getCenter().x, grid->GetSize().y * SPRITE_HEIGHT - gridView.getSize().y / 2);
	if (gridView.getCenter().x + gridView.getSize().x / 2 > grid->GetSize().x * SPRITE_WIDTH) gridView.setCenter(grid->GetSize().x * SPRITE_WIDTH - gridView.getSize().x / 2, gridView.getCenter().y);


	//reset game
	static bool rWasPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		if (!rWasPressed) {
			if (!grid->HasWon()) {
				points = 0;
				playTime = 0;
				saver->ClearEvents();
			}
			grid = new Grid(newGridSize.x, newGridSize.y, saver);
			grid->RandomiseBombs(DEFAULT_GRID_BOMBS);
			_alive = true;
			UpdateMap();
			rWasPressed = true;
		}
	} else {
		rWasPressed = false;
	}

	//Save and load game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		if (saver->SaveEventsToFile(DEFAULT_SAVE_PATH)) {
			printf("Succesfully saved game\n");
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
		static bool hasLoaded = false;
		if (!hasLoaded) {
			LoadFromFile(DEFAULT_SAVE_PATH);
			hasLoaded = true;
			UpdateMap();
		}
	}

}

bool MainState::LoadFromFile(std::string fileName) {
	if (!saver->LoadEventsFromFile(fileName)) return false;
	saver->Pause();

	Event e;
	while (saver->GetNextEvent(e)) {
		switch (e.type) {
		case EVENT_TYPES::GRID_CREATED:
			grid = new Grid(e.x, e.y, saver);
			newGridSize = sf::Vector2i(e.x, e.y);
			break;
		case EVENT_TYPES::BOMB_ADDED:
			grid->AddBomb(e.x, e.y);
			break;
		case EVENT_TYPES::FLAG_TOGGLED:
			grid->ToggleFlag(e.x, e.y);
			break;
		case EVENT_TYPES::TILE_CLICKED:
			grid->ClickTile(e.x, e.y);
			break;
		}
		points += grid->GetAndClearPoints();
	}

	saver->Resume();
}