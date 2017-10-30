#pragma once
#include <string>
#include <vector>
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

	std::string GetNextEvent();
	std::vector<std::string> GetAllEvents();
	void AddEvent(std::string);

private:
	std::fstream dataStream;
	std::vector<std::string> events;
	int eventCounter;
};