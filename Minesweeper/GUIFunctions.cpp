#pragma once
#include "GUIFunctions.h"

void CenterText(sf::Text &t, sf::RenderWindow &w) {

	float x = w.getSize().x / 2;
	x -= t.getGlobalBounds().width / 2;

	float y = w.getSize().y / 2;
	y -= t.getGlobalBounds().height / 2;
	y -= t.getGlobalBounds().height / 4;//For the offset of text

	t.setPosition(x, y);

}