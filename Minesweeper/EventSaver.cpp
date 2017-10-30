#include "EventSaver.h"
#include <stdio.h>

bool EventSaver::LoadEventsFromFile(std::string fileName) {
	dataStream = std::fstream(fileName, std::ios::in | std::ios::binary);

	std::string line;
	if (dataStream.is_open()) {
		while (std::getline(dataStream, line))
		{
			events.push(line);
		}
		dataStream.close();
		return true;
	} else {
		printf("Somthing went wrong loading events from file %s\n", fileName);
	}

}

bool EventSaver::SaveEventsToFile(std::string fileName) {
	return false;
}

int EventSaver::GetEventCounter() {
	return -1;
}

void EventSaver::SetEventCounter(int) {
}