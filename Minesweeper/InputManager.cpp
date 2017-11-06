#include "InputManager.h"

bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button) {
	if (!sf::Mouse::isButtonPressed(button)) return false;

	sf::IntRect spriteRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

	if (!spriteRect.contains(GetMousePosition())) return false;
	
	return true;
}

bool InputManager::IsTransformClicked(sf::Transform object, sf::Mouse::Button button) {
	if (!sf::Mouse::isButtonPressed(button)) return false;


}

sf::Vector2i InputManager::GetMousePosition() {
	return sf::Mouse::getPosition(*_window);
}

sf::Vector2f InputManager::GetMouseGamePosition() {
	return  _window->mapPixelToCoords(GetMousePosition());
}

void InputManager::SetRenderWindow(sf::RenderWindow *window) {
	_window = window;
}