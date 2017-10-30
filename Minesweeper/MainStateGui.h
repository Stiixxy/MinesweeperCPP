#pragma once
#include <SFML\Graphics.hpp>

#include "Gui.h"
#include "DEFENITIONS.h"

#define RENDER_NUMBERS 5

class MainStateGui : public sf::Transformable, public sf::Drawable {
public:
	MainStateGui(int* pointref, sf::Texture* tex) : _pointRefrence(pointref), m_texture(tex) {
		view = sf::View(sf::FloatRect(0, 0, RENDER_NUMBERS * tex->getSize().x / 10, RENDER_NUMBERS * tex->getSize().y));
		view.setViewport(sf::FloatRect(0, 0, 1, (1 - GRID_Y_PERCENTAGE) * 5));
	}
	MainStateGui() {}

	void Update();
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	sf::View view;
	int* _pointRefrence;
	sf::VertexArray m_vertices;
	sf::Texture* m_texture;

	
};