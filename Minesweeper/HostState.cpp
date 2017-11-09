#include "HostState.h"



void HostState::Init() {
	_data->assetManager.LoadTexture("button image", "Resources/button.png");
	_data->assetManager.LoadFont("button font", "Resources/SOTA.ttf");

	portTextbox = new TextBox(sf::Sprite(_data->assetManager.GetTexture("button image")), &_data->assetManager.GetFont("button font"), _data);
	portTextbox->Center();
}

void HostState::BeforeDestroy() {

}

void HostState::Update(float dt) {
	portTextbox->Update();

	sf::Event e;
	while (_data->window.pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			_data->window.close();
		if (e.type == sf::Event::TextEntered)
			portTextbox->AddKey(e);
	}
}

void HostState::Draw() {
	_data->window.draw(*portTextbox);
}