#pragma once
#include <string>
#include <queue>
#include <iostream>
#include <fstream>

#include <SFML\Graphics.hpp>

class EventSaver {
public:
	EventSaver() {}
	~EventSaver() {}

	bool LoadEventsFromFile(std::string fileName);
	bool SaveEventsToFile(std::string fileName);
	int GetEventCounter();
	void SetEventCounter(int);

private:
	std::fstream dataStream;
	std::queue<std::string> events;
	int eventCounter;
};