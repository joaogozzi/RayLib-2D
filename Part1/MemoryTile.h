#pragma once
#include <raylib.h>
#include "MemoryTileStatus.h"

class MemoryTile
{
public:
	MemoryTile(int row, int col, int gap, int tileSize, int gridSize, int num);
	Rectangle rect;

	int number;
	int fontSize = 60;

	MemoryTileStatus status = MemoryTileStatus::Hidden;

	void Draw();
};