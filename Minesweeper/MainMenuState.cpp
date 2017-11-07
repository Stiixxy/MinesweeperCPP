#include "MainMenuState.h"
#include "GameSettingsState.h"

void MainMenuState::Init() {
	_data->assetManager.LoadTexture("button image", "Resources/button.png");
	_data->assetManager.LoadFont("button font", "Resources/28DL.ttf");

	playButton = new Button<MainMenuState>(sf::Sprite(_data->assetManager.GetTexture("button image")), _data, &MainMenuState::OnPlayClick, this);
	loadButton = new Button<MainMenuState>(sf::Sprite(_data->assetManager.GetTexture("button image")), _data, &MainMenuState::OnLoadClick, this);
	exitButton = new Button<MainMenuState>(sf::Sprite(_data->assetManager.GetTexture("button image")), _data, &MainMenuState::OnExitClick, this);

	playButton->GetSprite()->setScale(1.25, 1.25);
	loadButton->GetSprite()->setScale(1.25, 1.25);
	exitButton->GetSprite()->setScale(1.25, 1.25);

	playButton->Center();
	playButton->GetSprite()->move(0, _data->window.getSize().y * -.25);

	loadButton->Center();

	exitButton->Center();
	exitButton->GetSprite()->move(0, _data->window.getSize().y * .25);

	playButton->InitText("Play", &_data->assetManager.GetFont("button font"));
	loadButton->InitText("Load", &_data->assetManager.GetFont("button font"));
	exitButton->InitText("Exit", &_data->assetManager.GetFont("button font"));

	playButton->AutoSetFontSize(.8);
	playButton->CenterText();

	loadButton->AutoSetFontSize(.8);
	loadButton->CenterText();

	exitButton->AutoSetFontSize(.8);
	exitButton->CenterText();

}

void MainMenuState::BeforeDestroy() {

}

void MainMenuState::Update(float dt) {
	playButton->Update();
	loadButton->Update();
	exitButton->Update();
}

void MainMenuState::Draw() {
	_data->window.setView(_data->window.getDefaultView());
	_data->window.draw(*playButton);
	_data->window.draw(*loadButton);
	_data->window.draw(*exitButton);
}

void MainMenuState::OnPlayClick() {
	_data->stateManager.AddState(StateRef(new GameSettingsState(_data)));
}

void MainMenuState::OnLoadClick() {
	_data->stateManager.AddState(StateRef(new MainState(_data, DEFAULT_SAVE_PATH)));
}

void MainMenuState::OnExitClick() {
	_data->window.close();
}

void MainMenuState::PollEvents(float dt) {
	sf::Event event;

	while (_data->window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			_data->window.close();
	}
}