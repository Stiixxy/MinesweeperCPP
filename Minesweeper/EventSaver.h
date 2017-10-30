#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <SFML\Graphics.hpp>

#include "Event.h"

class EventSaver {
public:
	EventSaver() {}
	~EventSaver() {}

	bool LoadEventsFromFile(std::string fileName);
	bool SaveEventsToFile(std::string fileName);
	int GetEventCounter();
	void SetEventCounter(int);

	bool GetNextEvent(Event &event);
	std::vector<Event> GetAllEvents();
	void AddEvent(Event);
	void Pause();
	void Resume();
	void ClearEvents();
private:
	std::fstream dataStream;
	std::vector<Event> events;
	int eventCounter = 0;
	bool _paused = false;
};