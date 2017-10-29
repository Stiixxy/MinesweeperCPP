#include "InputManager.h"

bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button) {
	if (!sf::Mouse::isButtonPressed(button)) return false;

	sf::IntRect spriteRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

	if (!spriteRect.contains(GetMousePosition())) return false;
	
	return true;
}

sf::Vector2i InputManager::GetMousePosition() {
	return sf::Mouse::getPosition(*_window);
}

void InputManager::SetRenderWindow(sf::RenderWindow *window) {
	_window = window;
}