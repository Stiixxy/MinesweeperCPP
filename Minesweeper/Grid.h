#pragma once

#include <SFML\Graphics.hpp>
#include <stdlib.h>
#include "EventSaver.h"

enum TILE_RETURNS{
	BOMB = -1,
	FALSE_TILE = -2,
	ALREAD_CLICKED = -3
};

enum TILE_TYPES {
	UNCLICKED = -1,
	BOMB_DIED = -2,
	BOMB_SHOWED = -3,
	FLAGGED = -4
};

class Grid {
public:
	Grid(int width, int height);
	Grid(int width, int height, EventSaver* saver);

	~Grid() {}

	int GetIndex(int x, int y);
	int GetBombs(int x, int y);
	bool IsInGrid(int x, int y);
	bool IsClicked(int x, int y);
	bool IsBomb(int x, int y);
	bool ToggleFlag(int x, int y);
	void ClickAdjecent(int x, int y);
	void AddBomb(int x, int y);
	void RandomiseBombs(int bombCount);
	bool HasWon();
	void ShowBombs();

	int ClickTile(int x, int y);
	int* GetTiles();
	sf::Vector2i MouseToGridPos(sf::Vector2f);
	sf::Vector2u GetSize();
private:
	bool* m_bombs;
	int* m_clicked;
	EventSaver* eventSaver;
	int tilesRemaining;
	sf::Vector2u _size;
};