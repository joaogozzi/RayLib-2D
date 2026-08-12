#pragma once
#include "raylib.h"
#include <string>
#include <array>

class Game2048
{
public:
	static const int screenWidth = 900;
	static const int screenHeight = 900;

	struct Board
	{
		float width = 800;
		float height = 800;

		Rectangle rect = { (screenWidth - width) / 2, (screenHeight - height) / 2, width, height };

		void Draw()
		{
			DrawRectangleRec(rect, DARKGRAY);
		}
	};

	struct Cell
	{
		int value = 0;
		Rectangle rect = Rectangle{ 0, 0, 180, 180 };
		Color color = GRAY;
		float fontSize = 40;

		void Draw()
		{
			// Colors
			switch (value)
			{
			case 2:
				color = CYAN;
				break;

			case 4:
				color = BLUE;
				break;

			case 8:
				color = GREEN;
				break;

			case 16:
				color = DARKGREEN;
				break;

			case 32:
				color = YELLOW;
				break;

			case 64:
				color = ORANGE;
				break;

			case 128:
				color = RED;
				break;

			case 256:
				color = PINK;
				break;

			case 512:
				color = VIOLET;
				break;

			case 1024:
				color = PURPLE;
				break;

			case 2048:
				color = DARKPURPLE;
				break;

			default:
				color = GRAY;
				break;
			}

			int textWidth = MeasureText(std::to_string(value).c_str(), fontSize);

			DrawRectangleRec(rect, color);

			if (value != 0)
				DrawText(std::to_string(value).c_str(), (rect.x + (rect.width / 2)) - textWidth / 2, (rect.y + (rect.height / 2)) - fontSize / 2, fontSize, BLACK);
		}

		void Update()
		{

		}

		void SpawnCell()
		{
			value = 2;
		}
	};

	Board board;
	std::array<std::array<Cell, 4>, 4> cells;

	void Main();
	void Start();
	void Update();
	int RandomNum(int min, int max);
};