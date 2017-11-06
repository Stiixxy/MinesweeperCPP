#include "Button.h"

template <class T>
Button<T>::Button(sf::Sprite spr, GameDataRef _data, void(T::*onclick)(), T *t) : _sprite(spr), data(_data), onClick(onclick), _t(t) {

}

template <class T>
void Button<T>::Update() {

	if (!data->inputManager.IsSpriteClicked(_sprite, sf::Mouse::Left)) {
		WasClicked = false;
		return;
	}

	if (!WasClicked) {
		((*_t).*(onClick))();
		WasClicked = true;
	}

}

template <class T>
void Button<T>::draw(sf::RenderTarget &target, sf::RenderStates states) const {

	target.draw(_sprite);

}

template <class T>
sf::Sprite *Button<T>::GetSprite() {
	return &_sprite;
}

template <class T>
void Button<T>::CenterX() {

	unsigned int x = data->window.getSize().x;
	x /= 2;

	x -= _sprite.getGlobalBounds().width / 2;

	_sprite.setPosition(x, _sprite.getPosition().y);

}

template <class T>
void Button<T>::CenterY() {

	unsigned int y = data->window.getSize().y;
	y /= 2;

	y -= _sprite.getGlobalBounds().height / 2;

	_sprite.setPosition(_sprite.getPosition().x, y);

}

template <class T>
void Button<T>::Center() {
	CenterX();
	CenterY();
}