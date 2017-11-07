#include "GameSettingsState.h"
#include "GUIFunctions.h"

#include <iostream>
#include <ctime>
#include <thread>

void GameSettingsState::Init() {
	_data->assetManager.LoadTexture("button image", "Resources/button.png");
	_data->assetManager.LoadTexture("button arrow up", "Resources/arrowup.png");
	_data->assetManager.LoadTexture("button arrow down", "Resources/arrowdown.png");
	_data->assetManager.LoadFont("button font", "Resources/SOTA.ttf");

	InitGUI();

}

void GameSettingsState::InitGUI() {
	startButton = new Button<GameSettingsState>(sf::Sprite(_data->assetManager.GetTexture("button image")), _data, &GameSettingsState::OnStartClick, this);
	startButton->GetSprite()->setScale(1.25, 1.25);
	startButton->Center();
	startButton->GetSprite()->move(0, _data->window.getSize().y * .25);
	startButton->InitText("Start game", &_data->assetManager.GetFont("button font"));
	startButton->AutoSetFontSize(.8);
	startButton->CenterText();

	gridSizeText = sf::Text(std::to_string(gridWidth) + ":" + std::to_string(gridHeight), _data->assetManager.GetFont("button font"));
	gridSizeText.setColor(sf::Color::Red);
	CenterText(gridSizeText, _data->window);
	gridSizeText.move(0, _data->window.getSize().y * -.25);

	heightUP = new Button<GameSettingsState>(sf::Sprite(_data->assetManager.GetTexture("button arrow up")), _data, &GameSettingsState::OnHeightUp, this);
	heightUP->GetSprite()->setScale(.05, .05);
	heightUP->Center();
	heightUP->GetSprite()->move(gridSizeText.getGlobalBounds().width / 2 + heightUP->GetSprite()->getGlobalBounds().width, _data->window.getSize().y * -.25 - gridSizeText.getGlobalBounds().height / 2);
	heightUP->GetSprite()->setColor(sf::Color::White);

	heightDOWN = new Button<GameSettingsState>(sf::Sprite(_data->assetManager.GetTexture("button arrow down")), _data, &GameSettingsState::OnHeightDown, this);
	heightDOWN->GetSprite()->setScale(.05, .05);
	heightDOWN->Center();
	heightDOWN->GetSprite()->move(gridSizeText.getGlobalBounds().width / 2 + heightDOWN->GetSprite()->getGlobalBounds().width, _data->window.getSize().y * -.25 + gridSizeText.getGlobalBounds().height / 2 - heightDOWN->GetSprite()->getGlobalBounds().height);
	heightDOWN->GetSprite()->setColor(sf::Color::White);

	widthUP = new Button<GameSettingsState>(sf::Sprite(_data->assetManager.GetTexture("button arrow up")), _data, &GameSettingsState::OnWidthUp, this);
	widthUP->GetSprite()->setScale(.05, .05);
	widthUP->Center();
	widthUP->GetSprite()->move(-gridSizeText.getGlobalBounds().width / 2 - widthUP->GetSprite()->getGlobalBounds().width, _data->window.getSize().y * -.25 - gridSizeText.getGlobalBounds().height / 2);
	widthUP->GetSprite()->setColor(sf::Color::White);

	widthDOWN = new Button<GameSettingsState>(sf::Sprite(_data->assetManager.GetTexture("button arrow down")), _data, &GameSettingsState::OnWidthDown, this);
	widthDOWN->GetSprite()->setScale(.05, .05);
	widthDOWN->Center();
	widthDOWN->GetSprite()->move(-gridSizeText.getGlobalBounds().width / 2 - widthDOWN->GetSprite()->getGlobalBounds().width, _data->window.getSize().y * -.25 + gridSizeText.getGlobalBounds().height / 2 - heightDOWN->GetSprite()->getGlobalBounds().height);
	widthDOWN->GetSprite()->setColor(sf::Color::White);

}

void GameSettingsState::BeforeDestroy() {

}

void GameSettingsState::Update(float dt) {
	startButton->Update();

	heightUP->Update();
	heightDOWN->Update();

	widthUP->Update();
	widthDOWN->Update();
}

void GameSettingsState::Draw() {
	_data->window.setView(_data->window.getDefaultView());
	
	_data->window.draw(*startButton);

	_data->window.draw(*heightUP);
	_data->window.draw(*heightDOWN);

	_data->window.draw(*widthUP);
	_data->window.draw(*widthDOWN);

	_data->window.draw(gridSizeText);
}

void GameSettingsState::OnStartClick() {
	_data->stateManager.AddState(StateRef(new MainState(_data, sf::Vector2i(gridWidth, gridHeight))));
}

void GameSettingsState::OnHeightUp() {
	gridHeight++;
	gridSizeText.setString(std::to_string(gridWidth) + ":" + std::to_string(gridHeight));
}

void GameSettingsState::OnHeightDown() {
	gridHeight--;
	gridSizeText.setString(std::to_string(gridWidth) + ":" + std::to_string(gridHeight));
}

void GameSettingsState::OnWidthUp() {
	gridWidth++;
	gridSizeText.setString(std::to_string(gridWidth) + ":" + std::to_string(gridHeight));
}

void GameSettingsState::OnWidthDown() {
	gridWidth--;
	gridSizeText.setString(std::to_string(gridWidth) + ":" + std::to_string(gridHeight));
}

void GameSettingsState::PollEvents(float dt) {
	sf::Event event;

	while (_data->window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			_data->window.close();
	}
}