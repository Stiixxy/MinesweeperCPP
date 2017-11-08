#include "AssetManager.h"

AssetManager::AssetManager() {
	_failedTexture.create(100, 100);
}

void AssetManager::LoadTexture(std::string name, std::string fileName) {

	sf::Texture tex;

	if (tex.loadFromFile(fileName)) {
		this->_textures[name] = tex;
	}
	
}

void AssetManager::LoadFont(std::string name, std::string fileName) {

	sf::Font font;

	if (font.loadFromFile(fileName)) {
		this->_fonts[name] = font;
	}

}

void AssetManager::LoadSound(std::string name, std::string filename) {

	sf::SoundBuffer buffer;

	if (buffer.loadFromFile(filename)) {
		_sounds[name] = buffer;
	}

}

void AssetManager::SetGlobal(std::string name, void *global) {
	_globals[name] = global;
}

void AssetManager::UnloadTexture(std::string name) {
	_textures.erase(name);
}

void AssetManager::UnloadFont(std::string name) {
	_fonts.erase(name);
}

void AssetManager::UnloadSound(std::string name) {
	_sounds.erase(name);
}

sf::Texture &AssetManager::GetTexture(std::string name) {

	if (_textures.find(name) == _textures.end()) return _failedTexture;

	return this->_textures.at(name);

}

sf::Font &AssetManager::GetFont(std::string name) {

	return this->_fonts.at(name);

}

sf::SoundBuffer &AssetManager::GetSound(std::string name) {
	return _sounds.at(name);
}

void* AssetManager::GetGlobal(std::string name) {

	if (_globals.find(name) == _globals.end()) return NULL;

	return this->_globals.at(name);

}