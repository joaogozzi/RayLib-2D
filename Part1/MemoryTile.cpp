#include "MemoryTile.h"
#include <string>

MemoryTile::MemoryTile(int row, int col, int gap, int tileSize, int gridSize, int num)
{
	float x = gap + (tileSize + gap) * col;
	float y = gap + (tileSize + gap) * row;

	rect = Rectangle{ x, y, (float)tileSize, (float)tileSize };

	number = num;
}

void MemoryTile::Draw()
{
	
	std::string tileText = "";

	Vector2 cen = Vector2{
		rect.x + rect.width / 2,
		rect.y + rect.height / 2
	};

	Color bgColor = RAYWHITE;

	switch (status)
	{
	case Hidden:
		bgColor = RAYWHITE;
		tileText = "?";
		break;

	case Flipped:
		bgColor = ORANGE;
		tileText = std::to_string(number);
		break;

	case Matched:
		bgColor = GREEN;
		tileText = ":)";
		break;
	}

	DrawRectangleRounded(rect, 0.2f, 8, bgColor);

	int textWidth = MeasureText(tileText.c_str(), fontSize);
	Vector2 txtOrigin = Vector2{
								cen.x - (float)textWidth / 2,
								cen.y - (float)fontSize / 2
	};

	DrawText(tileText.c_str(), txtOrigin.x, txtOrigin.y, fontSize, BLACK);
}