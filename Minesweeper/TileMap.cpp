#include "TileMap.h"
#include "Grid.h"

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();

	states.texture = m_tileset;

	target.draw(m_vertices, states);
}

void TileMap::setTexture(sf::Texture *texture) {
	m_tileset = texture;
}

void TileMap::setTiles(sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height) {

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int tileNumber = translateTileNumber(tiles[i + j*width]);

			// find its position in the tileset texture
			int tu = tileNumber % (m_tileset->getSize().x / tileSize.x);
			int tv = tileNumber / (m_tileset->getSize().x / tileSize.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}
	}

}

int TileMap::translateTileNumber(int number) {
	if (number == TILE_TYPES::UNCLICKED) return 13;
	if (number == TILE_TYPES::BOMB_DIED) return 10;
	if (number == TILE_TYPES::FLAGGED) return 12;
	if (number == TILE_TYPES::BOMB_SHOWED) return 8;
	if (number <= 7 && number >= 0) return number;


	printf("Unknown tilenumber returning question mark tile: %i\n", number);
	return 11;
}