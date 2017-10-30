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
	return true;
}

bool EventSaver::SaveEventsToFile(std::string fileName) {
	dataStream = std::fstream(fileName, std::ios::out | std::ios::binary);

	std::string line;
	if (!dataStream.is_open()) {
		std::cout << "Somthing went wrong writing events to file \n" << fileName << "\n";
		return false;
	}

	for (int i = 0; i < events.size(); i++) {
		std::string line = events.at(i).ToString();
		dataStream << line << '\n';
	}
	dataStream.close();
	return true;
}

int EventSaver::GetEventCounter() {
	return eventCounter;
}

void EventSaver::SetEventCounter(int counter) {
	eventCounter = counter;
}

Event EventSaver::GetNextEvent() {
	if (eventCounter >= events.size()) return{ EVENT_TYPES::EVENT_UNKNOWN, -1, -1 };
	return events.at(eventCounter++);
}

std::vector<Event> EventSaver::GetAllEvents() {
	return events;
}

void EventSaver::AddEvent(Event event) {
	events.push_back(event);
}