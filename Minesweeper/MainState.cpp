#include "DEFENITIONS.h"
#include "MainState.h" 
#include "EventSaver.h"
#include "pausedState.h"
#include "Event.h"
#include <iostream>

void MainState::Init() {
	_data->assetManager.LoadTexture("Minesweeper spritesheet", TILE_SPRITESHEET);
	_data->assetManager.LoadTexture("Minesweeper numbers", NUMBERS_SPRITESHEET);
	_data->assetManager.LoadTexture("button image", "Resources/buttonRed.png");
	_data->assetManager.LoadSound("bomb", "Resources/Bomb.wav");
	_data->assetManager.LoadSound("applause", "Resources/applause.wav");
	saver = new EventSaver();

	if (loadSave.empty()) {
		grid = new Grid(newGridSize.x, newGridSize.y, saver);
		grid->RandomiseBombs(newBombCount);
	} else {
		LoadFromFile(loadSave);
	}

	gridView = sf::View(sf::FloatRect(0, 0, grid->GetSize().x * SPRITE_WIDTH, grid->GetSize().y * SPRITE_HEIGHT));
	gridView.setViewport(sf::FloatRect(0, 1 - GRID_Y_PERCENTAGE, 1, GRID_Y_PERCENTAGE));

	map = new TileMap();
	map->setTexture(&_data->assetManager.GetTexture("Minesweeper spritesheet"));
	UpdateMap();
	gui = new MainStateGui(&points, &playTime, &_data->assetManager.GetTexture("Minesweeper numbers"));

	//Init save button
	saveButton = new Button<MainState>(sf::Sprite(_data->assetManager.GetTexture("button image")), _data, &MainState::OnSaveClick, this);
	saveButton->GetSprite()->setScale(.3, .3);
	saveButton->CenterX();
	saveButton->GetSprite()->move(0, _data->window.getSize().y * (1 - GRID_Y_PERCENTAGE) / 2 - saveButton->GetSprite()->getGlobalBounds().height / 2);
	saveButton->GetSprite()->setColor(sf::Color::Green);

	//Create sound file
	bombSound = sf::Sound(_data->assetManager.GetSound("bomb"));
	applauseSound = sf::Sound(_data->assetManager.GetSound("applause"));

	//Connect to network
	if (_port != -1) {
		if (_ip == sf::IpAddress::None) {
			//Host
			saver->Host(_port);
		} else {
			//Client
			saver->Connect(_ip, _port);
		}
	}
}

void MainState::BeforeDestroy() {
	_data->assetManager.UnloadTexture("Minesweeper spritesheet");
	_data->assetManager.UnloadTexture("Minesweeper numbers");
}

void MainState::Update(float dt) {
	PollEvents(dt);
	Event e;
	while (saver->receivedEvents.size() > 0) {
		e = saver->receivedEvents.front();
		saver->receivedEvents.pop();
		ExecuteEvent(e);
		saver->AddEvent(e);
		saver->AddToEventCounter(1);
	}
	while (saver->GetNextEvent(e)) {
		saver->unsentEvents.push(e);
	}
	points += grid->GetAndClearPoints();
	gui->Update();
	if (!_data->window.hasFocus()) return;
	_data->window.setView(gridView);
	HandleInput(dt);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _alive && !grid->HasWon()) {
		if (!_clickedLastFrame) {
			_clickedLastFrame = true;
			sf::Vector2i mousePos = _data->inputManager.GetMousePosition();
			sf::Vector2f worldPos = _data->window.mapPixelToCoords(mousePos);
			sf::Vector2i tilePos = grid->MouseToGridPos(worldPos);
			int result = grid->ClickTile(tilePos.x, tilePos.y);

			if (grid->HasWon()) {
				grid->ShowBombs();
				applauseSound.play();
			}

			if (result != TILE_RETURNS::ALREAD_CLICKED) UpdateMap();
			if (result == TILE_RETURNS::BOMB) {
				_alive = false;
				bombSound.play();
			}
		}
	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && _alive && !grid->HasWon()) {
		if (!_clickedLastFrame) {
			_clickedLastFrame = true;
			sf::Vector2i mousePos = _data->inputManager.GetMousePosition();
			sf::Vector2f worldPos = _data->window.mapPixelToCoords(mousePos);
			sf::Vector2i tilePos = grid->MouseToGridPos(worldPos);
			if (grid->ToggleFlag(tilePos.x, tilePos.y)) 
				UpdateMap();
		}
	} else {
		_clickedLastFrame = false;
	}

	if (_alive && !grid->HasWon()) {
		playTime += dt;
	}

	saveButton->Update();
	if (saver->IsUpToDate()) {
		saveButton->GetSprite()->setColor(sf::Color::Green);
	} else {
		saveButton->GetSprite()->setColor(sf::Color::Red);
	}
}

void MainState::UpdateMap() {
	map->setTiles(sf::Vector2u(SPRITE_WIDTH, SPRITE_HEIGHT), grid->GetTiles(), grid->GetSize().x, grid->GetSize().y);
}

void MainState::Draw() {
	_data->window.setView(gridView);
	_data->window.draw(*map);
	_data->window.draw(*gui);
	_data->window.setView(_data->window.getDefaultView());
	_data->window.draw(*saveButton);
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
			rWasPressed = true;
			if (!grid->HasWon()) {
				points = 0;
				playTime = 0;
				saver->ClearEvents();
			}
			grid = new Grid(newGridSize.x, newGridSize.y, saver);
			grid->RandomiseBombs(newBombCount);
			_alive = true;
			UpdateMap();
		}
	} else {
		rWasPressed = false;
	}

	//Pause
	static bool escapePressed = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		if (!escapePressed) {
			_data->stateManager.AddState(StateRef(new PausedState(_data)), false);
			escapePressed = true;
		}
	} else {
		escapePressed = false;
	}
	
}

bool MainState::LoadFromFile(std::string fileName) {
	if (!saver->LoadEventsFromFile(fileName)) return false;
	saver->Pause();

	Event e;
	int bombsCreated = 0;
	while (saver->GetNextEvent(e)) {
		switch (e.type) {
		case EVENT_TYPES::GRID_CREATED:
			grid = new Grid(e.x, e.y, saver);
			newGridSize = sf::Vector2i(e.x, e.y);
			bombsCreated = 0;
			break;
		case EVENT_TYPES::BOMB_ADDED:
			grid->AddBomb(e.x, e.y);
			bombsCreated++;
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

	if (grid->HasWon()) grid->ShowBombs();
	newBombCount = bombsCreated;

	saver->Resume();
}

void MainState::ExecuteEvent(Event e) {
	saver->Pause();

	switch (e.type) {
	case EVENT_TYPES::GRID_CREATED:
		if (!grid->HasWon()) points = 0;
		grid = new Grid(e.x, e.y, saver);
		newGridSize = sf::Vector2i(e.x, e.y);
		newBombCount = 0;

		gridView = sf::View(sf::FloatRect(0, 0, grid->GetSize().x * SPRITE_WIDTH, grid->GetSize().y * SPRITE_HEIGHT));
		gridView.setViewport(sf::FloatRect(0, 1 - GRID_Y_PERCENTAGE, 1, GRID_Y_PERCENTAGE));
		break;
	case EVENT_TYPES::BOMB_ADDED:
		grid->AddBomb(e.x, e.y);
		newBombCount++;
		break;
	case EVENT_TYPES::FLAG_TOGGLED:
		grid->ToggleFlag(e.x, e.y);
		break;
	case EVENT_TYPES::TILE_CLICKED:
		grid->ClickTile(e.x, e.y);
		break;
	}

	if (grid->HasWon()) grid->ShowBombs();
	UpdateMap();
	saver->Resume();
}

void MainState::OnSaveClick() {
	if (saver->IsUpToDate())return;
	if (saver->SaveEventsToFile(DEFAULT_SAVE_PATH)) {
		printf("Succesfully saved game\n");
	}
}