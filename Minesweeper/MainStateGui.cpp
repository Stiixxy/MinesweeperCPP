#include "MainStateGui.h"

void MainStateGui::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.setView(view);

	states.transform *= Transformable::getTransform();

	states.texture = m_texture;

	target.draw(m_vertices, states);
}

void MainStateGui::Update() {
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(RENDER_NUMBERS * 4);

	int score = *_pointRefrence;
	int tileWidth = m_texture->getSize().x / 10;

	for (int i = RENDER_NUMBERS - 1; i >= 0; i--) {
		int number = score % 10; //Get last number
		score = score / 10; //Move all numbers 1 to the right

		// find its position in the tileset texture
		int tu = number % (m_texture->getSize().x / tileWidth);
		//int tv = 0;

		sf::Vertex* quad = &m_vertices[i * 4];

		//Define the corners of the number
		quad[0].position = sf::Vector2f(i * tileWidth, 0);
		quad[1].position = sf::Vector2f((i + 1) * tileWidth, 0);
		quad[2].position = sf::Vector2f((i + 1) * tileWidth, m_texture->getSize().y);
		quad[3].position = sf::Vector2f(i * tileWidth, m_texture->getSize().y);

		//Define the textures
		quad[0].texCoords = sf::Vector2f(tu * tileWidth, 0);
		quad[1].texCoords = sf::Vector2f((tu + 1) * tileWidth, 0);
		quad[2].texCoords = sf::Vector2f((tu + 1) * tileWidth, m_texture->getSize().y);
		quad[3].texCoords = sf::Vector2f(tu * tileWidth, m_texture->getSize().y);
	}
}