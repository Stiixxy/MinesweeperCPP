#include "TextBox.h"

TextBox::TextBox(sf::Sprite s, sf::Font *f, GameDataRef data) : _sprite(s), _data(data) {
	_text.setFont(*f);
	_text.setFillColor(TEXTCOLOR);
}

void TextBox::Update() {
	_text.setPosition(_sprite.getPosition());
	if (dotUpdateClock.getElapsedTime().asSeconds() > DOTTIME) {
		hasDot = (hasDot) ? false : true;
		UpdateString();
	}
}

void TextBox::SetValue(std::string value) {

	_value = value;
	UpdateString();

}

void TextBox::UpdateString() {
	sf::String s = GetValue();
	if (hasDot) s += ".";
	_text.setString(s);
	AutoSetFontSize(.8);
	CenterText();
}

void TextBox::AddKey(sf::Event keyEvent) {
	if (keyEvent.type != sf::Event::TextEntered) return;
	if (keyEvent.text.unicode > 127)
		return; //Check if asci caracter
	if (keyEvent.text.unicode == 8) {
		//Backspace was pressed
		if (_value.size() == 0)return;
		_value.pop_back();
		UpdateString();
		return;
	}
	char c = static_cast<char>(keyEvent.text.unicode);
	_value.push_back(c);
	UpdateString();
}

void TextBox::CenterX() {
	unsigned int x = _data->window.getSize().x;
	x /= 2;

	x -= _sprite.getGlobalBounds().width / 2;

	_sprite.setPosition(x, _sprite.getPosition().y);
}

void TextBox::CenterY() {
	unsigned int y = _data->window.getSize().y;
	y /= 2;

	y -= _sprite.getGlobalBounds().height / 2;

	_sprite.setPosition(_sprite.getPosition().x, y);
}

void TextBox::Center() {
	CenterX();
	CenterY();
}

void TextBox::AutoSetFontSize(float percent) {
	if (_text.getString().isEmpty()) return;
	int fontSize = 1;
	_text.setCharacterSize(fontSize);
	while (TextFits(percent)) {
		fontSize++;
		_text.setCharacterSize(fontSize);
	}
	fontSize--;
	_text.setCharacterSize(fontSize);
}

void TextBox::Init(sf::String s, int maxLength) {}

sf::String TextBox::GetValue() {
	return _value;
}

sf::Sprite *TextBox::GetSprite() {
	return &_sprite;
}

void TextBox::draw(sf::RenderTarget &target, sf::RenderStates states) const {

	target.draw(_sprite);
	target.draw(_text);

}

bool TextBox::TextFits(float percent) {
	if (_text.getGlobalBounds().width > _sprite.getGlobalBounds().width)return false;// width is bigger then allowed
	if (_text.getGlobalBounds().height > _sprite.getGlobalBounds().height * percent)return false;
	return true;
}

void TextBox::CenterText() {
	float x = _sprite.getGlobalBounds().width / 2 + _sprite.getPosition().x;
	x -= _text.getGlobalBounds().width / 2;

	float y = _sprite.getGlobalBounds().height / 2 + _sprite.getPosition().y;
	y -= _text.getGlobalBounds().height / 2;
	y -= _text.getGlobalBounds().height / 4; //For the text offset from the top

	_text.setPosition(x, y);
}