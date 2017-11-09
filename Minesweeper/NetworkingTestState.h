#pragma once

#include "State.h"
#include "Game.h"

#include <SFML\Network.hpp>
#include <SFML\Graphics.hpp>

class NetworkingTestState : public State {
public:
	NetworkingTestState(GameDataRef data) : _data(data) {}

	virtual void Init();
	virtual void BeforeDestroy();

	virtual void Update(float dt);
	virtual void Draw();

private:
	GameDataRef _data;
	sf::TcpSocket socket;
	sf::TcpListener listener;
};