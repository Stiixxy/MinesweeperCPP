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
}

bool EventSaver::IsUpToDate() {
	return _upToDate;
}