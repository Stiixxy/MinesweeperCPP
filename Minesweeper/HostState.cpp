#include "HostState.h"

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include "GUIFunctions.h"
#include "GameSettingsState.h"
#include "MainState.h"

void HostState::Init() {
	_data->assetManager.LoadTexture("button image", "Resources/button.png");
	_data->assetManager.LoadFont("button font", "Resources/SOTA.ttf");

	portTextbox = new TextBox(sf::Sprite(_data->assetManager.GetTexture("button image")), &_data->assetManager.GetFont("button font"), _data, "Port");
	portTextbox->Center();
	portTextbox->GetSprite()->move(0, _data->window.getSize().y * -.25);
	portTextbox->SetValue("5000");

	portText = sf::Text("Port:", _data->assetManager.GetFont("button font"));
	portText.setColor(sf::Color::Red);
	CenterText(portText, _data->window);
	portText.move(0, _data->window.getSize().y * -.25 - portTextbox->GetSprite()->getGlobalBounds().height);

	backButton = new Button<HostState>(sf::Sprite(_data->assetManager.GetTexture("button image")), _data, &HostState::OnBackClick, this);
	backButton->Center();
	backButton->GetSprite()->move(0, _data->window.getSize().y * .2 + backButton->GetSprite()->getGlobalBounds().height * 1.5);
	backButton->InitText("Back", &_data->assetManager.GetFont("button font"));
	backButton->AutoSetFontSize(.8);
	backButton->CenterText();

	hostButton = new Button<HostState>(sf::Sprite(_data->assetManager.GetTexture("button image")), _data, &HostState::OnHostClick, this);
	hostButton->Center();
	hostButton->GetSprite()->move(0, _data->window.getSize().y * .2);
	hostButton->InitText("Host", &_data->assetManager.GetFont("button font"));
	hostButton->AutoSetFontSize(.8);
	hostButton->CenterText();

}

void HostState::BeforeDestroy() {

}

void HostState::Update(float dt) {
	//portTextbox->Update();
	hostButton->Update();
	backButton->Update();

	sf::Event e;
	while (_data->window.pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			_data->window.close();
		if (e.type == sf::Event::TextEntered)
			portTextbox->AddKey(e);
	}
}

void HostState::Draw() {
	_data->window.setView(_data->window.getDefaultView());

	_data->window.draw(portText);
	_data->window.draw(*portTextbox);

	_data->window.draw(*hostButton);
	_data->window.draw(*backButton);
}

void HostState::OnHostClick() {
	if (portTextbox->GetValue().isEmpty()) return;
	std::string s = portTextbox->GetValue();
	int port = std::stoi(s);

	std::cout << "Creating game on " << port << "\n";
	_data->stateManager.AddState(StateRef(new MainState(_data, port, _gridSize, _bombs)));
}

void HostState::OnBackClick() {
	_data->stateManager.AddState(StateRef(new GameSettingsState(_data)));
}