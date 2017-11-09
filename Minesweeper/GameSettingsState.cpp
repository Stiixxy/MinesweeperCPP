#include "GameSettingsState.h"
#include "MainMenuState.h"
#include "ClientState.h"
#include "HostState.h"
#include "GUIFunctions.h"

#include <iostream>
#include <ctime>
#include <thread>

/*
TODO:
	-implement multiplayer state and multiplayer host in mainstate
*/

void GameSettingsState::Init() {
	_data->assetManager.LoadTexture("button image", "Resources/button.png");
	_data->assetManager.LoadTexture("button arrow up", "Resources/arrowup.png");
	_data->assetManager.LoadTexture("button arrow down", "Resources/arrowdown.png");
	_data->assetManager.LoadFont("button font", "Resources/SOTA.ttf");

	InitGUI();
}

void GameSettingsState::InitGUI() {
	startButton = new Button<GameSettingsState>(sf::Sprite(_data->assetManager.GetTexture("button image")), _data, &GameSettingsState::OnStartClick, this);
	startButton->Center();
	startButton->GetSprite()->move(0, _data->window.getSize().y * .125);
	startButton->InitText("Start new game", &_data->assetManager.GetFont("button font"));
	startButton->AutoSetFontSize(.8);
	startButton->CenterText();

	hostButton = new Button<GameSettingsState>(sf::Sprite(_data->assetManager.GetTexture("button image")), _data, &GameSettingsState::OnHostClick, this);
	hostButton->GetSprite()->setScale(.5, 1);
	hostButton->Center();
	hostButton->GetSprite()->move(hostButton->GetSprite()->getGlobalBounds().width * -.5, _data->window.getSize().y * .25 + hostButton->GetSprite()->getGlobalBounds().height * .25);
	hostButton->InitText("Host", &_data->assetManager.GetFont("button font"));
	hostButton->AutoSetFontSize(.8);
	hostButton->CenterText();

	joinButton = new Button<GameSettingsState>(sf::Sprite(_data->assetManager.GetTexture("button image")), _data, &GameSettingsState::OnJoinClick, this);
	joinButton->GetSprite()->setScale(.5, 1);
	joinButton->Center();
	joinButton->GetSprite()->move(joinButton->GetSprite()->getGlobalBounds().width * .5, _data->window.getSize().y * .25 + hostButton->GetSprite()->getGlobalBounds().height * .25);
	joinButton->InitText("Join", &_data->assetManager.GetFont("button font"));
	joinButton->AutoSetFontSize(.8);
	joinButton->CenterText();

	backButton = new Button<GameSettingsState>(sf::Sprite(_data->assetManager.GetTexture("button image")), _data, &GameSettingsState::OnBackClick, this);
	backButton->Center();
	backButton->GetSprite()->move(0, _data->window.getSize().y * .25 + backButton->GetSprite()->getGlobalBounds().height * 1.5);
	backButton->InitText("Back", &_data->assetManager.GetFont("button font"));
	backButton->AutoSetFontSize(.8);
	backButton->CenterText();

	gridSizeText = sf::Text(std::to_string(gridWidth) + ":" + std::to_string(gridHeight), _data->assetManager.GetFont("button font"));
	gridSizeText.setColor(sf::Color::Red);
	CenterText(gridSizeText, _data->window);
	gridSizeText.move(0, _data->window.getSize().y * -.25);

	gridText = sf::Text("Grid size:", _data->assetManager.GetFont("button font"));
	gridText.setColor(sf::Color::Red);
	CenterText(gridText, _data->window);
	gridText.move(0, _data->window.getSize().y * -.25 - gridSizeText.getGlobalBounds().height);

	bombCountText = sf::Text("Bombs: " + std::to_string(bombs), _data->assetManager.GetFont("button font"));
	bombCountText.setColor(sf::Color::Red);
	CenterText(bombCountText, _data->window);

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

	bombsUP = new Button<GameSettingsState>(sf::Sprite(_data->assetManager.GetTexture("button arrow up")), _data, &GameSettingsState::OnBombsUp, this);
	bombsUP->GetSprite()->setScale(.05, .05);
	bombsUP->Center();
	bombsUP->GetSprite()->move(-bombCountText.getGlobalBounds().width / 2 - bombsUP->GetSprite()->getGlobalBounds().width, -bombCountText.getGlobalBounds().height / 2);
	bombsUP->GetSprite()->setColor(sf::Color::White);

	bombsDOWN = new Button<GameSettingsState>(sf::Sprite(_data->assetManager.GetTexture("button arrow down")), _data, &GameSettingsState::OnBombsDown, this);
	bombsDOWN->GetSprite()->setScale(.05, .05);
	bombsDOWN->Center();
	bombsDOWN->GetSprite()->move(-bombCountText.getGlobalBounds().width / 2 - bombsDOWN->GetSprite()->getGlobalBounds().width, bombsDOWN->GetSprite()->getGlobalBounds().height / 2);
	bombsDOWN->GetSprite()->setColor(sf::Color::White);

}

void GameSettingsState::BeforeDestroy() {

}

void GameSettingsState::Update(float dt) {
	startButton->Update();
	backButton->Update();

	hostButton->Update();
	joinButton->Update();

	heightUP->Update();
	heightDOWN->Update();

	widthUP->Update();
	widthDOWN->Update();

	bombsUP->Update();
	bombsDOWN->Update();
}

void GameSettingsState::Draw() {
	_data->window.setView(_data->window.getDefaultView());

	_data->window.draw(*startButton);
	_data->window.draw(*backButton);

	_data->window.draw(*hostButton);
	_data->window.draw(*joinButton);

	_data->window.draw(*heightUP);
	_data->window.draw(*heightDOWN);

	_data->window.draw(*widthUP);
	_data->window.draw(*widthDOWN);

	_data->window.draw(*bombsDOWN);
	_data->window.draw(*bombsUP);

	_data->window.draw(bombCountText);

	_data->window.draw(gridSizeText);
	_data->window.draw(gridText);
}

void GameSettingsState::OnStartClick() {
	_data->stateManager.AddState(StateRef(new MainState(_data, sf::Vector2i(gridWidth, gridHeight), bombs)));
}

void GameSettingsState::OnJoinClick() {
	_data->stateManager.AddState(StateRef(new ClientState(_data)));
}

void GameSettingsState::OnHostClick() {
	_data->stateManager.AddState(StateRef(new HostState(_data)));
}

void GameSettingsState::OnBackClick() {
	_data->stateManager.AddState(StateRef(new MainMenuState(_data)));
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

void GameSettingsState::OnBombsUp() {
	bombs++;
	bombCountText.setString("Bombs: " + std::to_string(bombs));
}

void GameSettingsState::OnBombsDown() {
	bombs--;
	bombCountText.setString("Bombs: " + std::to_string(bombs));
}

void GameSettingsState::PollEvents(float dt) {
	sf::Event event;

	while (_data->window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			_data->window.close();
	}
}
