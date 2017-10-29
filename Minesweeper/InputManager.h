#pragma once

#include <SFML\Graphics.hpp>

class InputManager {
public:
	InputManager() {}
	~InputManager() {}

	void SetRenderWindow(sf::RenderWindow *);

	bool IsSpriteClicked(sf::Sprite, sf::Mouse::Button);
	
	sf::Vector2i GetMousePosition();

private:
	sf::RenderWindow *_window;
};