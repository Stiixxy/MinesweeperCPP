#include "NetworkingTestState.h"

#include <stdio.h>
#include <iostream>
sf::Thread *t;

void NetworkingTestState::Init() {

}

void NetworkingTestState::BeforeDestroy() {

}

void NetworkingTestState::Update(float dt) {
	if (!_data->window.hasFocus()) return;
	static bool hasLaunched = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
		if (hasLaunched) return;
		hasLaunched = true;
		t = new sf::Thread(&NetworkingTestState::AcceptConnection, this);
		t->launch();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
		socket.connect("127.0.0.1", 5000);

		sf::Packet p;
		socket.receive(p);
		std::string text;
		p >> text;
		std::cout << text << "\n";
		socket.disconnect();
	}
}

void NetworkingTestState::Draw() {

}

void NetworkingTestState::AcceptConnection() {
	listener.listen(5000);

	sf::TcpSocket client;
	printf("Server is now waiting for a connection!\n");
	listener.accept(client);

	sf::Packet p;
	std::string text = "test";
	p << text;
	client.send(p);
	client.disconnect();
	listener.close();
}