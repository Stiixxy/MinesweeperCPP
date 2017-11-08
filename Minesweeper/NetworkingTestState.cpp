#include "NetworkingTestState.h"

#include <stdio.h>

void NetworkingTestState::Init() {

}

void NetworkingTestState::BeforeDestroy() {

}

void NetworkingTestState::Update(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
		listener.listen(5000);

		sf::TcpSocket client;
		listener.accept(client);

		client.send("test", 5);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
		socket.connect("127.0.0.1", 5000);

		char data[10];
		size_t received;
		socket.receive(data, 10, received);
		printf("%s\n", data);
	}
}

void NetworkingTestState::Draw() {

}