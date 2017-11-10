#include "pausedState.h"
#include "GUIFunctions.h"
#include "MainMenuState.h"

void PausedState::Init() {	
	_data->assetManager.LoadFont("button font", "Resources/28DL.ttf");
	_data->assetManager.LoadTexture("button", "Resources/button.png");

	//Background
	background.setSize(sf::Vector2f(_data->window.getSize().x, _data->window.getSize().y));
	sf::Color c = sf::Color::Black;
	c.a = 230;
	background.setFillColor(c);

	//Text
	pausedText = sf::Text("Paused", _data->assetManager.GetFont("button font"), 45);
	CenterText(pausedText, _data->window);
	pausedText.move(0, _data->window.getSize().y * -.25);
	pausedText.setColor(sf::Color::Red);

	exitButton = new Button<PausedState>(sf::Sprite(_data->assetManager.GetTexture("button")), _data, &PausedState::OnExitClick, this);
	exitButton->GetSprite()->setScale(.5, .8);
	exitButton->Center();
	exitButton->GetSprite()->move(0, _data->window.getSize().y * .25);
	exitButton->InitText("Exit game", &_data->assetManager.GetFont("button font"));
	exitButton->AutoSetFontSize(.8);
	exitButton->CenterText();
}

void PausedState::BeforeDestroy() {

}


void PausedState::Update(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		if (keyIsPressed) return;
		_data->stateManager.RemoveState();
	} else {
		keyIsPressed = false;
	}

	exitButton->Update();
}

void PausedState::Draw() {
	_data->stateManager.GetState(0)->Draw();

	_data->window.draw(background);

	_data->window.draw(pausedText);
	_data->window.draw(*exitButton);
}

void PausedState::OnExitClick() {
	//THIS DOESNT REMOVE THE OLD GAME
	_data->stateManager.RemoveAllStates();
	_data->stateManager.AddState(StateRef(new MainMenuState(_data)));
}