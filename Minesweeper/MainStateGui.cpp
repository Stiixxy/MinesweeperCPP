#include "MainStateGui.h"
#include <math.h>

MainStateGui::MainStateGui(int* pointref, float* clockref, sf::Texture* tex) : _pointRefrence(pointref), timeRefrence(clockref), m_texture(tex) {
	pointsView = sf::View(sf::FloatRect(0, 0, RENDER_NUMBERS * tex->getSize().x / 10, RENDER_NUMBERS * tex->getSize().y));
	pointsView.setViewport(sf::FloatRect(0, 0, 1, (1 - GRID_Y_PERCENTAGE) * 5)); //Still no idea why we need the 5 but it works i guess

	timeView = sf::View(sf::FloatRect(0, 0, RENDER_NUMBERS * tex->getSize().x / 10, RENDER_NUMBERS * tex->getSize().y));
	timeView.setViewport(sf::FloatRect(0, 0, RENDER_NUMBERS * tex->getSize().x / 10, RENDER_NUMBERS * tex->getSize().y));

	Setup();
}

void MainStateGui::Setup() {
	SetupVerticies(score_verticies);
	SetupVerticies(time_vertices);
}


void MainStateGui::Update() {
	UpdateVerticies(score_verticies, *_pointRefrence);
	UpdateVerticies(time_vertices, int(*timeRefrence));
	
}

void MainStateGui::SetupVerticies(sf::VertexArray &verticies) {
	//Setup score verticies
	verticies.setPrimitiveType(sf::Quads);
	verticies.resize(RENDER_NUMBERS * 4);

	int tileWidth = m_texture->getSize().x / 10;

	for (int i = RENDER_NUMBERS - 1; i >= 0; i--) {
		sf::Vertex* quad = &verticies[i * 4];

		//Define the corners of the number
		quad[0].position = sf::Vector2f(i * tileWidth, 0);
		quad[1].position = sf::Vector2f((i + 1) * tileWidth, 0);
		quad[2].position = sf::Vector2f((i + 1) * tileWidth, m_texture->getSize().y);
		quad[3].position = sf::Vector2f(i * tileWidth, m_texture->getSize().y);
	}
}

void MainStateGui::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= Transformable::getTransform();

	states.texture = m_texture;

	target.setView(pointsView);
	target.draw(time_vertices, states);
}


void MainStateGui::UpdateVerticies(sf::VertexArray &verticies, int numberToDraw) {
	int tileWidth = m_texture->getSize().x / 10;

	for (int i = RENDER_NUMBERS - 1; i >= 0; i--) {
		int number = numberToDraw % 10; //Get last number
		numberToDraw = numberToDraw / 10; //Move all numbers 1 to the right

		int tu = number % (m_texture->getSize().x / tileWidth);

		sf::Vertex* quad = &verticies[i * 4];

		//Define the textures
		quad[0].texCoords = sf::Vector2f(tu * tileWidth, 0);
		quad[1].texCoords = sf::Vector2f((tu + 1) * tileWidth, 0);
		quad[2].texCoords = sf::Vector2f((tu + 1) * tileWidth, m_texture->getSize().y);
		quad[3].texCoords = sf::Vector2f(tu * tileWidth, m_texture->getSize().y);
	}

}