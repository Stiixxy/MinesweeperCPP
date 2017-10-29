#include "MainState.h" 
#include "DEFENITIONS.h"

void MainState::Init() {
	_data->assetManager.LoadTexture("Minesweeper spritesheet", TILE_SPRITESHEET);
	_data->assetManager.LoadTexture("Minesweeper temp", "Resources/tile0.png");

	grid = new Grid(DEFAULT_GRID_WIDTH, DEFAULT_GRID_HEIGHT);
	map = new TileMap();

	map->setTexture(&_data->assetManager.GetTexture("Minesweeper spritesheet"));
	map->setTiles(sf::Vector2u(SPRITE_WIDTH, SPRITE_HEIGHT), grid->GetTiles(), grid->GetSize().x, grid->GetSize().y);

	gridView = sf::View(sf::FloatRect(0, 0, grid->GetSize().x * SPRITE_WIDTH, grid->GetSize().y * SPRITE_HEIGHT));

	grid->RandomiseBombs(DEFAULT_GRID_BOMBS);
}

void MainState::BeforeDestroy() {
	_data->assetManager.UnloadTexture("Minesweeper spritesheet");
}

void MainState::Update(float dt) {
	PollEvents(dt);
	HandleInput(dt);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _alive && !grid->HasWon()) {
		if (!_clickedLastFrame) {
			_clickedLastFrame = true;
			sf::Vector2i mousePos = _data->inputManager.GetMousePosition();
			sf::Vector2f worldPos = _data->window.mapPixelToCoords(mousePos);
			sf::Vector2i tilePos = grid->MouseToGridPos(worldPos);
			int result = grid->ClickTile(tilePos.x, tilePos.y);

			if (grid->HasWon())
				grid->ShowBombs();

			if (result != TILE_RETURNS::ALREAD_CLICKED) map->setTiles(sf::Vector2u(SPRITE_WIDTH, SPRITE_HEIGHT), grid->GetTiles(), grid->GetSize().x, grid->GetSize().y);
			if (result == TILE_RETURNS::BOMB) _alive = false;
		}
	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && _alive && !grid->HasWon()) {
		if (!_clickedLastFrame) {
			_clickedLastFrame = true;
			sf::Vector2i mousePos = _data->inputManager.GetMousePosition();
			sf::Vector2f worldPos = _data->window.mapPixelToCoords(mousePos);
			sf::Vector2i tilePos = grid->MouseToGridPos(worldPos);
			if (grid->ToggleFlag(tilePos.x, tilePos.y)) map->setTiles(sf::Vector2u(SPRITE_WIDTH, SPRITE_HEIGHT), grid->GetTiles(), grid->GetSize().x, grid->GetSize().y);
		}
	} else {
		_clickedLastFrame = false;
	}

}

void MainState::Draw() {
	_data->window.setView(gridView);
	_data->window.draw(*map);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) {
		gridView.zoom(1.01);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) {
		gridView.zoom(0.99);
	}

	//Moving
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		gridView.move(-GRIDVIEW_MOVEMENT_SPEED * dt, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		gridView.move(GRIDVIEW_MOVEMENT_SPEED * dt, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		gridView.move(0, -GRIDVIEW_MOVEMENT_SPEED * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		_data->stateManager.AddState(StateRef(new MainState(_data)));
	}
}