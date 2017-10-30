#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

enum EVENT_TYPES {
	EVENT_UNKNOWN = -1,
	GRID_CREATED = 0,
	ADD_POINTS = 1,
	TILE_CLICKED = 2,
	BOMB_ADDED = 3,
	FLAG_TOGGLED = 4,
};

class Event {
public:
	Event(std::string string) {
		std::stringstream stream(string);
		std::string segment;
		std::vector<std::string> elements;
		while (std::getline(stream, segment, ':')) {
			elements.push_back(segment);
		}
		std::string eventTypeString = elements.at(0);
		type = (EVENT_TYPES)(std::stoi(elements.at(0)));


		x = std::stoi(elements.at(1));
		y = std::stoi(elements.at(2));
	}

	Event(EVENT_TYPES t, int nx, int ny){
		type = t;
		x = nx;
		y = ny;
	}

	std::string ToString() {
		std::string string = std::to_string(type) + ":" + std::to_string(x) + ":" + std::to_string(y);
		return string;
	}

	EVENT_TYPES type;
	int x, y;
};