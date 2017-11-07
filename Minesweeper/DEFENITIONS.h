#pragma once

#pragma region Window settings

#define WINDOW_HEIGHT	700
#define WINDOW_WIDTH	650
#define WINDOW_TITLE	"Minesweeper"

#pragma endregion

#pragma region Game settings

#define GAME_START_FPS	60.0f
#define GAME_START_RPS	60.0f

#pragma endregion

#pragma region Minesweeper data settings

#define TILE_SPRITESHEET	"Resources/tiles.png"
#define NUMBERS_SPRITESHEET	"Resources/numbers.png"	
#define SPRITE_WIDTH		16
#define SPRITE_HEIGHT		16

#pragma endregion

#pragma region Minesweeper settings

#define DEFAULT_GRID_WIDTH	30
#define DEFAULT_GRID_HEIGHT	30
#define DEFAULT_GRID_BOMBS	60
#define DEFAULT_SAVE_PATH	"Resources/save.txt"
#define GRID_Y_PERCENTAGE	 0.85

#pragma endregion

#pragma region Grid view settings

#define GRIDVIEW_MOVEMENT_SPEED		200
#define GRIDVIEW_ZOOM_SPEED			100

#pragma endregion
