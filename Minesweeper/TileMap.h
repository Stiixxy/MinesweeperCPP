#pragma once

#include <SFML\Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
	void setTiles(sf::Vector2u, const int* tiles, unsigned int width, unsigned int height);
	void setTexture(sf::Texture *tex);

private:
	int translateTileNumber(int);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	sf::VertexArray m_vertices;
	sf::Texture* m_tileset;
};