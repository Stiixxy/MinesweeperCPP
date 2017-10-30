#include "EventSaver.h"
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
		events.push_back(line);
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
		dataStream << events.at(i) << "\n";
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

std::string EventSaver::GetNextEvent() {
	if (eventCounter >= events.size()) return NULL;
	return events.at(eventCounter++);
}

std::vector<std::string> EventSaver::GetAllEvents() {
	return events;
}

void EventSaver::AddEvent(std::string event) {
	events.push_back(event);
}