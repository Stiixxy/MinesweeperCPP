#include "ClientState.h"

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include "GUIFunctions.h"
#include "GameSettingsState.h"
#include "MainState.h"

void ClientState::Init() {
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

	ipTextbox = new TextBox(sf::Sprite(_data->assetManager.GetTexture("button image")), &_data->assetManager.GetFont("button font"), _data, "IP");
	ipTextbox->Center();
	ipTextbox->SetValue("127.0.0.1");

	ipText = sf::Text("IP:", _data->assetManager.GetFont("button font"));
	ipText.setColor(sf::Color::Red);
	CenterText(ipText, _data->window);
	ipText.move(0, ipTextbox->GetSprite()->getGlobalBounds().height * -1);

	backButton = new Button<ClientState>(sf::Sprite(_data->assetManager.GetTexture("button image")), _data, &ClientState::OnBackClick, this);
	backButton->Center();
	backButton->GetSprite()->move(0, _data->window.getSize().y * .2 + backButton->GetSprite()->getGlobalBounds().height * 1.5);
	backButton->InitText("Back", &_data->assetManager.GetFont("button font"));
	backButton->AutoSetFontSize(.8);
	backButton->CenterText();

	joinButton = new Button<ClientState>(sf::Sprite(_data->assetManager.GetTexture("button image")), _data, &ClientState::OnJoinClick, this);
	joinButton->Center();
	joinButton->GetSprite()->move(0, _data->window.getSize().y * .2);
	joinButton->InitText("Join", &_data->assetManager.GetFont("button font"));
	joinButton->AutoSetFontSize(.8);
	joinButton->CenterText();

}

void ClientState::BeforeDestroy() {

}

void ClientState::Update(float dt) {
	joinButton->Update();
	backButton->Update();

	//Check if a text box is clicked
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) activeTextBox = NULL;
	if (_data->inputManager.IsSpriteClicked(*portTextbox->GetSprite(), sf::Mouse::Left)) activeTextBox = portTextbox;
	if (_data->inputManager.IsSpriteClicked(*ipTextbox->GetSprite(), sf::Mouse::Left)) activeTextBox = ipTextbox;
	//if (activeTextBox != NULL) activeTextBox->Update();

	sf::Event e;
	while (_data->window.pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			_data->window.close();
		if (e.type == sf::Event::TextEntered)
			if(activeTextBox != NULL) activeTextBox->AddKey(e);
	}
}

void ClientState::Draw() {
	_data->window.setView(_data->window.getDefaultView());

	_data->window.draw(portText);
	_data->window.draw(*portTextbox);

	_data->window.draw(ipText);
	_data->window.draw(*ipTextbox);

	_data->window.draw(*joinButton);
	_data->window.draw(*backButton);
}

void ClientState::OnJoinClick() {
	std::string s = portTextbox->GetValue();
	int port = std::stoi(s);
	sf::IpAddress i = ipTextbox->GetValue();

	std::cout << "Connecting to " << i.toString() << ":" << port << "\n";
	_data->stateManager.AddState(StateRef(new MainState(_data, port, i)));
}

void ClientState::OnBackClick() {
	_data->stateManager.AddState(StateRef(new GameSettingsState(_data)));
}