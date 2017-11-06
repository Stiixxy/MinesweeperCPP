#include "MainMenuState.h"

void MainMenuState::Init() {
	_data->assetManager.LoadTexture("button", "Resources/numbers.png");

	b = new Button(sf::Sprite(_data->assetManager.GetTexture("button")), _data, &OnButtonClicked, (void*)this);
	b->Center();

}

void MainMenuState::BeforeDestroy() {}

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

void OnButtonClicked(void * creator){
	MainMenuState *state = (MainMenuState*)creator;

	state->InMemberFunction();
}
