#include "MainMenuState.h"

void MainMenuState::Init() {
	_data->assetManager.LoadTexture("button", "Resources/numbers.png");
	_data->assetManager.LoadFont("Buttonfont", "Resources/SOTA.ttf");

	b = new Button<MainMenuState>(sf::Sprite(_data->assetManager.GetTexture("button")), _data, &MainMenuState::InMemberFunction, this);
	b->GetSprite()->setScale(3, 3);
	b->Center();
	b->InitText("Test wddqwdwqqwqwdith ", &_data->assetManager.GetFont("Buttonfont"));
	//b->SetFontSize(100);
	b->AutoSetFontSize(.9);
	b->CenterText();

}

void MainMenuState::BeforeDestroy() {

}

void MainMenuState::Update(float dt) {
	b->Update();
}

void MainMenuState::Draw() {
	_data->window.draw(*b);
}

void MainMenuState::PollEvents(float dt) {
	sf::Event event;

	while (_data->window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			_data->window.close();
	}
}

void MainMenuState::InMemberFunction() {
	printf("This is called from the inside the main menu state\n");
}
