#pragma once
#include <string>
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

#include "Event.h"

class EventSaver {
public:
	EventSaver() {}
	~EventSaver() {}

	bool LoadEventsFromFile(std::string fileName);
	bool SaveEventsToFile(std::string fileName);
	int GetEventCounter();
	void SetEventCounter(int);
	bool IsUpToDate();

	bool GetNextEvent(Event &event);
	std::vector<Event> GetAllEvents();
	void AddEvent(Event);
	void Pause();
	void Resume();
	void ClearEvents();

	void Host(int port);
	void Connect(sf::IpAddress host, int port);

	std::queue<Event> unsentEvents;
	std::queue<Event> receivedEvents;
private:
	std::fstream dataStream;
	std::vector<Event> events;
	int eventCounter = 0;
	bool _paused = false;
	bool _upToDate = true;

	bool _isNetworked;
	bool _isHost;

	sf::TcpListener host;
	sf::TcpSocket client;
	sf::Thread *receiveThread;
	sf::Thread *sendThread;
	sf::IpAddress _host;
	//sf::Mutex networkMutex;
	int _port;

	void HostSend();
	void HostReceive();
	void ClientReceive();
	void ClientSend();
};



