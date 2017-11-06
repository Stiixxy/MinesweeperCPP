#include "Button.h"

Button::Button(sf::Sprite spr, GameDataRef _data, void(*onclick)(void *creator), void *creator) : _sprite(spr), data(_data), onClick(onclick), _creator(creator) {

}

void Button::Update() {

	if (!data->inputManager.IsSpriteClicked(_sprite, sf::Mouse::Left)) {
		WasClicked = false;
		return;
	}

	if (!WasClicked) {
		(*onClick)(_creator);
		WasClicked = true;
	}

}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {

	target.draw(_sprite);

}

sf::Sprite *Button::GetSprite() {
	return &_sprite;
}

void Button::CenterX() {

	unsigned int x = data->window.getSize().x;
	x /= 2;

	x -= _sprite.getGlobalBounds().width / 2;

	_sprite.setPosition(x, _sprite.getPosition().y);

}

void Button::CenterY() {

	unsigned int y = data->window.getSize().y;
	y /= 2;

	y -= _sprite.getGlobalBounds().height / 2;

	_sprite.setPosition(_sprite.getPosition().x, y);

}

void Button::Center() {
	CenterX();
	CenterY();
}