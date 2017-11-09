#include "SplashState.h"
#include "MainMenuState.h"

void SplashState::Init() {
	_data->assetManager.LoadTexture("background", "Resources/splash.png");

	background = sf::Sprite(_data->assetManager.GetTexture("background"));
	clock.restart();
}

void SplashState::BeforeDestroy() {
	_data->assetManager.UnloadTexture("background");
}

void SplashState::Update(float dt) {
	if (clock.getElapsedTime().asSeconds() > splashTime) {
		_data->stateManager.AddState(StateRef(new MainMenuState(_data)));
	}
}

void SplashState::Draw() {
	_data->window.draw(background);
}