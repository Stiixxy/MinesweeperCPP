#include <vector>
#include <queue>
#include <stdio.h>

#include "Grid.h"
#include "DEFENITIONS.h"


Grid::Grid(int width, int height) : _size(width, height), m_bombs(new bool[width * height]), m_clicked(new int[width * height]), tilesRemaining(width*height) {
	for (int i = 0; i < width * height; i++) {
		m_bombs[i] = false;
	}

	for (int i = 0; i < width * height; i++) {
		m_clicked[i] = TILE_TYPES::UNCLICKED;
	}
}

Grid::Grid(int width, int height, EventSaver* saver) : _size(width, height), m_bombs(new bool[width * height]), m_clicked(new int[width * height]), tilesRemaining(width*height), eventSaver(saver) {
	for (int i = 0; i < width * height; i++) {
		m_bombs[i] = false;
	}

	for (int i = 0; i < width * height; i++) {
		m_clicked[i] = TILE_TYPES::UNCLICKED;
	}
}

void Grid::RandomiseBombs(int bombCount) {
	while (bombCount > 0) {
		int x = rand() % _size.x;
		int y = rand() % _size.y;
		if (m_bombs[GetIndex(x, y)]) continue;
		AddBomb(x, y);
		bombCount--;
	}
}

void Grid::AddBomb(int x, int y) {
	m_bombs[GetIndex(x, y)] = true;
	tilesRemaining--;
}

int Grid::ClickTile(int x, int y) {
	if (!IsInGrid(x, y)) return TILE_RETURNS::FALSE_TILE;
	if (!IsClicked(x, y)) return TILE_RETURNS::ALREAD_CLICKED;
	if (IsBomb(x, y)) {
		m_clicked[GetIndex(x, y)] = TILE_TYPES::BOMB_DIED;
		return TILE_RETURNS::BOMB;
	}

	tilesRemaining--;
	m_clicked[GetIndex(x, y)] = GetBombs(x, y);
	if (m_clicked[GetIndex(x, y)] == 0)
		ClickAdjecent(x, y);//Its a 0 so click adjecent

	return m_clicked[GetIndex(x, y)];
}

int Grid::GetIndex(int x, int y) {
	return x + (y * _size.y);
}

int Grid::GetBombs(int x, int y) {
	int bombs = 0;
	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			if (!IsInGrid(x + dx, y + dy)) continue;
			if (IsBomb(x + dx, y + dy)) bombs++;
		}
	}
	return bombs;
}

bool Grid::IsInGrid(int x, int y) {
	if (x < 0) return false;
	if (x >= _size.x) return false;
	if (y < 0) return false;
	if (y >= _size.y) return false;
	return true;
}

bool Grid::IsBomb(int x, int y) {
	return m_bombs[GetIndex(x, y)];
}

bool Grid::IsClicked(int x, int y) {
	return (m_clicked[GetIndex(x, y)] == TILE_TYPES::UNCLICKED);
}

int* Grid::GetTiles() {
	return m_clicked;
}

sf::Vector2u Grid::GetSize() {
	return _size;
}

sf::Vector2i Grid::MouseToGridPos(sf::Vector2f mousePos) {
	sf::Vector2i pos;
	int xSize = WINDOW_WIDTH / _size.x;
	int ySize = WINDOW_HEIGHT / _size.y;
	pos.x = (int)mousePos.x / SPRITE_WIDTH;
	pos.y = (int)mousePos.y / SPRITE_HEIGHT;

	return pos;
}

bool Grid::ToggleFlag(int x, int y) {
	//Returns true if somthing changed
	if (!IsInGrid(x, y)) return false;

	if (m_clicked[GetIndex(x, y)] == TILE_TYPES::FLAGGED) {
		m_clicked[GetIndex(x, y)] = TILE_TYPES::UNCLICKED;
	} else if (m_clicked[GetIndex(x, y)] == TILE_TYPES::UNCLICKED) {
		m_clicked[GetIndex(x, y)] = TILE_TYPES::FLAGGED;
	}

	return true;
}

void Grid::ClickAdjecent(int x, int y) {
	//Using flood fill
	//tilesRemaining++; //The one that was removing from clicktile
	if (GetBombs(x, y) != 0) return;
	std::queue<sf::Vector2i> positions;
	positions.push(sf::Vector2i(x, y));

	while (!positions.empty()) {
		sf::Vector2i currentPos = positions.front();
		positions.pop();
		for (int dx = currentPos.x - 1; dx <= currentPos.x + 1; dx++) {
			for (int dy = currentPos.y - 1; dy <= currentPos.y + 1; dy++) {
				if (!IsInGrid(dx, dy)) continue;
				if (m_clicked[GetIndex(dx, dy)] != TILE_TYPES::UNCLICKED) continue;
				int bombs = GetBombs(dx, dy);
				m_clicked[GetIndex(dx, dy)] = bombs;
				tilesRemaining--;
				if (bombs == 0) {
					positions.push(sf::Vector2i(dx, dy));
				}
			}
		}
	}


}

bool Grid::HasWon() {
	return (tilesRemaining <= 0);
}

void Grid::ShowBombs() {
	for (int x = 0; x < _size.x; x++) {
		for (int y = 0; y < _size.y; y++) {
			if (IsBomb(x, y))
				m_clicked[GetIndex(x, y)] = TILE_TYPES::BOMB_SHOWED;
		}
	}
}