#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include <memory>
#include "DEFENITIONS.h"
#include "StateManager.h"
#include "AssetManager.h"
#include "InputManager.h"

struct GameData {
	sf::RenderWindow window;
	StateManager stateManager;
	AssetManager assetManager;
	InputManager inputManager;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game {
public:
	Game();
	~Game() {};

	void SetFPS(float);
	void SetRPS(float);

private:
	float _frameTime = 1.0f / GAME_START_FPS;
	float _renderTime = 1.0f / GAME_START_RPS;

	GameDataRef _data = std::make_shared<GameData>();

	void Run();

};