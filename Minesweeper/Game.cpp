#include "Game.h"

#include <stdlib.h>
#include <time.h>
#include "SplashState.h"

Game::Game() {
	srand(time(NULL));

	_data->window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Close | sf::Style::Titlebar);
	_data->stateManager.AddState(StateRef(new SplashState(this->_data)));
	_data->inputManager.SetRenderWindow(&_data->window);

	this->Run();
}

void Game::Run() {
	int showFpsEvery = 5;
	float elapsedFrameTime = 0, elapsedRenderTime = 0, secondTime = 0;
	int frameCount = 0, renderCount = 0;
	sf::Clock clock;

	while (this->_data->window.isOpen()) {
		_data->stateManager.ProcessStateChanges();

		float timeChange = clock.getElapsedTime().asSeconds();
		clock.restart();
		elapsedFrameTime += timeChange;
		elapsedRenderTime += timeChange;
		secondTime += timeChange;
		

		if (elapsedFrameTime > _frameTime) {
			_data->stateManager.GetActiveState()->Update(elapsedFrameTime);
			
			sf::Event event;
			while (_data->window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) _data->window.close();
			}

			frameCount++;
			elapsedFrameTime = 0;
		}

		if (elapsedRenderTime > _renderTime) {
			_data->window.clear();
			_data->stateManager.GetActiveState()->Draw();
			_data->window.display();

			renderCount++;
			elapsedRenderTime = 0;
		}

		if (secondTime > showFpsEvery) {
			printf("FPS: %i, RPS:%i\n", frameCount / showFpsEvery, renderCount / showFpsEvery);
			frameCount = 0;
			renderCount = 0;
			secondTime = 0;
		}
	}
	
}

void Game::SetFPS(float frames) {
	_frameTime = 1.0f / frames;
}


void Game::SetRPS(float frames) {
	_renderTime = 1.0f / frames;
}