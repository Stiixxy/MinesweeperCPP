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
	//if (!_text.getString().isEmpty()) target.draw(_text);

	target.draw(_sprite);
	target.draw(_text);
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


template <class T>
void Button<T>::InitText(sf::String s, sf::Font *f, int i = 30) {
	_text.setString(s);
	_text.setFont(*f);
	_text.setCharacterSize(i);
	_text.setFillColor(sf::Color::Green);
	_text.setPosition(_sprite.getPosition());
}

template <class T>
void Button<T>::SetText(sf::String s) {
	_text.setString(s);
}

template <class T>
void Button<T>::SetFont(sf::Font f) {
	_text.setFont(f);
}

template <class T>
void Button<T> ::SetFontSize(int i) {
	_text.setCharacterSize(i);
}

template <class T>
void Button<T>::AutoSetFontSize(float percent) {

	int fontSize = 1;
	SetFontSize(fontSize);
	while (TextFits(percent)) {
		fontSize++;
		SetFontSize(fontSize);
	}
	fontSize--;
	SetFontSize(fontSize);

}

template <class T>
bool Button<T>::TextFits(float percent) {
	if (_text.getGlobalBounds().width > _sprite.getGlobalBounds().width * percent)return false;// width is bigger then allowed
	if (_text.getGlobalBounds().height > _sprite.getGlobalBounds().height * percent)return false;
	return true;
}

template <class T>
void Button<T>::CenterText() {

	float x = _sprite.getGlobalBounds().width / 2 + _sprite.getPosition().x;
	x -= _text.getGlobalBounds().width / 2;

	float y = _sprite.getGlobalBounds().height / 2 + _sprite.getPosition().y;
	y -= _text.getGlobalBounds().height / 2;

	_text.setPosition(x, y);

}