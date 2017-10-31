#pragma once
#include <SFML\Graphics.hpp>

#include "Gui.h"
#include "DEFENITIONS.h"

#define RENDER_NUMBERS 5

class MainStateGui : public sf::Transformable, public sf::Drawable {
public:
	MainStateGui(int* pointref,float*, sf::Texture* tex);
	MainStateGui() {}

	void Setup();
	void Update();
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void SetupVerticies(sf::VertexArray &);
	void UpdateVerticies(sf::VertexArray &verticies, int numberToDraw);

	sf::View pointsView;
	int* _pointRefrence;
	sf::VertexArray score_verticies;

	sf::View timeView;
	float *timeRefrence;
	sf::VertexArray time_vertices;

	sf::Texture* m_texture;

};