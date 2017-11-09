#include "EventSaver.h"
#include "Event.h"
#include <stdio.h>
#include <iostream>

bool EventSaver::LoadEventsFromFile(std::string fileName) {
	dataStream = std::fstream(fileName, std::ios::in | std::ios::binary);

	std::string line;
	if (!dataStream.is_open()) {
		std::cout << "Somthing went wrong loading events from file \n" << fileName << "\n";
		return false;
	}

	while (std::getline(dataStream, line))
	{
		Event e(line);
		events.push_back(e);
	}
	dataStream.close();
	_upToDate = true;
	return true;
}

bool EventSaver::SaveEventsToFile(std::string fileName) {
	if (_upToDate) return false;
	dataStream = std::fstream(fileName, std::ios::out | std::ios::binary);

	std::string line;
	if (!dataStream.is_open()) {
		std::cout << "Somthing went wrong writing events to file " << fileName << "\n";
		return false;
	}

	for (int i = 0; i < events.size(); i++) {
		std::string line = events.at(i).ToString();
		dataStream << line << '\n';
	}
	dataStream.close();
	_upToDate = true;
	return true;
}

int EventSaver::GetEventCounter() {
	return eventCounter;
}

void EventSaver::SetEventCounter(int counter) {
	eventCounter = counter;
}

bool EventSaver::GetNextEvent(Event &event) {
	if (eventCounter >= events.size()) return false;
	event = events.at(eventCounter++);
	return true;
}

std::vector<Event> EventSaver::GetAllEvents() {
	return events;
}

void EventSaver::AddEvent(Event event) {
	if (_paused) return;
	_upToDate = false;
	events.push_back(event);
}

void EventSaver::Pause() {
	_paused = true;
}

void EventSaver::Resume() {
	_paused = false;
}

void EventSaver::ClearEvents() {
	events.clear();
	eventCounter = 0;
}

bool EventSaver::IsUpToDate() {
	return _upToDate;
}

void EventSaver::Host(int port) {

	std::cout << "Starting server on " << port << ".\n";

	_port = port;
	sendThread = new sf::Thread(&EventSaver::HostSend, this);
	sendThread->launch();

}

void EventSaver::Connect(sf::IpAddress host, int port) {

	std::cout << "Connecting to host " << host << ":" << port << ".\n";

	_host = host;
	_port = port;

	receiveThread = new sf::Thread(&EventSaver::ClientReceive, this);
	receiveThread->launch();

}

void EventSaver::HostSend() {

	host.listen(_port);
	host.accept(client);

	sf::Packet p;
	std::string text = "Ping received";
	p << text;

	client.send(p);
	client.receive(p);

	p >> text;
	std::cout << text << "\n";

	receiveThread = new sf::Thread(&EventSaver::HostReceive, this);
	receiveThread->launch();

	while (1) {
		while (unsentEvents.size() == 0) {
			_sleep(1);
		}
		sf::Packet  sendPacket;
		sendPacket << unsentEvents.front();
		unsentEvents.pop();
		client.send(sendPacket);
	}

}

void EventSaver::ClientReceive() {
	events.clear();
	std::queue<Event> newQueue;
	std::swap(unsentEvents, newQueue);
	eventCounter = 0;

	sf::IpAddress ip = sf::IpAddress(_host);
	client.connect(ip, _port);

	sf::Packet p;
	client.receive(p);

	std::string text;
	p >> text;

	std::cout << text << "\n";

	text = "Pong received";
	p = sf::Packet();
	p << text;

	client.send(p);

	sendThread = new sf::Thread(&EventSaver::ClientSend, this);
	sendThread->launch();

	while (1) {
		sf::Packet p;
		client.receive(p);

		Event e;
		p >> e;

		receivedEvents.push(e);
		//std::cout << e.type << ":" << e.x << ":" << e.y << "\n";
	}
}

void EventSaver::HostReceive() {
	while (1) {
		sf::Packet p;
		client.receive(p);

		Event e;
		p >> e;

		receivedEvents.push(e);
		//std::cout << e.type << ":" << e.x << ":" << e.y << "\n";
	}
}

void EventSaver::ClientSend() {
	while (1) {
		while (unsentEvents.size() == 0) {
			_sleep(1);
		}
		sf::Packet  sendPacket;
		sendPacket << unsentEvents.front();
		unsentEvents.pop();
		client.send(sendPacket);
	}
}