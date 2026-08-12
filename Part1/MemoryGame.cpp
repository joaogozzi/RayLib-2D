#include "MemoryGame.h"
#include <iostream>

void MemoryGame::Main()
{
	Start();

	InitWindow(canvasWidth, gameWidthHeight, "Memory Game");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);

		Update();

		EndDrawing();
	}
}

void MemoryGame::Start()
{
	SetupGame();
}

void MemoryGame::Update()
{
	DrawUI();

	if (gameFinished)
		return;

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		Vector2 mouse = GetMousePosition();

		for (int i = 0; i < tiles.size(); i++)
		{
			if (CheckCollisionPointRec(mouse, tiles[i].rect))
			{
				if (compareMode)
					break;

				if (tiles[i].status == MemoryTileStatus::Flipped ||
					tiles[i].status == MemoryTileStatus::Matched)
					break;

				tiles[i].status = MemoryTileStatus::Flipped;

				if (tile1 == nullptr)
					tile1 = &tiles[i];
				else
				{
					tile2 = &tiles[i];
					compareMode = true;
					timeOfSecondClick = GetTime();
				}

				break;
			}
		}
	}

	if (compareMode)
	{
		if (GetTime() > timeOfSecondClick + WAIT_TIME)
		{
			if (tile1->number == tile2->number)
			{
				tile1->status = tile2->status = MemoryTileStatus::Matched;
			}
			else
			{
				tile1->status = tile2->status = MemoryTileStatus::Hidden;
			}

			tile1 = tile2 = nullptr;
			compareMode = false;
		}
	}

	for (MemoryTile tile : tiles)
	{
		tile.Draw();
	}

	bool finished = true;

	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].status != MemoryTileStatus::Matched)
		{
			finished = false;
		}
	}

	gameFinished = finished;
}

void MemoryGame::SetupGame()
{
	gameFinished = false;

	startTime = GetTime();
	tiles.clear();

	int totalSpaceForTiles = gameWidthHeight - gridSize * GAP - GAP;
	int tileSize = totalSpaceForTiles / gridSize;

	std::vector<int> numbers;

	for (int i = 1; i <= gridSize * gridSize / 2; i++)
	{
		numbers.push_back(i);
		numbers.push_back(i);
	}

	for (int row = 0; row < gridSize; row++)
	{
		for (int col = 0; col < gridSize; col++)
		{
			int index = GetRandomValue(0, numbers.size() - 1);
			int num = numbers[index];

			MemoryTile tile(row, col, GAP, tileSize, gridSize, num);
			tiles.push_back(tile);

			numbers.erase(numbers.begin() + index);
		}
	}
}

void MemoryGame::DrawUI()
{
	if (!gameFinished)
	{
		DrawTimer();

		Rectangle resetButton = Rectangle{ canvasWidth - 250, 150, 200, 100 };

		DrawButton("Reset", resetButton, std::bind(&MemoryGame::RestartGame, this));
	}
	else
	{
		int minutes = (int)runningTime / 60;
		int seconds = (int)runningTime % 60;

		std::string timerTxt = TextFormat("%02i:%02i", minutes, seconds);

		float timerSize = MeasureText(timerTxt.c_str(), 60);

		DrawText(timerTxt.c_str(), (canvasWidth / 2) - timerSize / 2, (gameWidthHeight / 2) - 60, 60, BLACK);

		Rectangle finishButton = Rectangle{ (canvasWidth / 2) - 100, (gameWidthHeight / 2) + 25, 200, 100 };

		auto lamb = [this]()
			{
				if (!restarting)
				{
					restarting = true;
					restartTime = GetTime() + 1.0;
				}
			};

		DrawButton("Finish", finishButton, lamb);

		if (restarting && GetTime() >= restartTime)
		{
			RestartGame();
			restarting = false;
		}
	}
}

void MemoryGame::DrawButton(const std::string& buttonText, Rectangle buttonRect, const std::function<void()>& func)
{
	Vector2 mouse = GetMousePosition();

	Color mButtonColor = WHITE;

	Rectangle shadowRect = buttonRect;
	shadowRect.y += 5;

	int fontSize = 40;

	float textWidth = MeasureText(buttonText.c_str(), fontSize);

	float textX = buttonRect.x + (buttonRect.width - textWidth) / 2;
	float textY = buttonRect.y + (buttonRect.height - fontSize) / 2;

	if (CheckCollisionPointRec(GetMousePosition(), buttonRect))
	{
		mButtonColor = BLUE;

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			mButtonColor = GREEN;

			func();
		}
	}

	DrawRectangleRounded(shadowRect, 0.25f, 8, Color{ 30, 30, 30, 100 });
	DrawRectangleRounded(buttonRect, 0.25f, 8, mButtonColor);
	DrawText(buttonText.c_str(), textX, textY, fontSize, BLACK);
}

void MemoryGame::DrawTimer()
{
	runningTime = GetTime() - startTime;

	int timerGap = 75;

	int minutes = (int)runningTime / 60;
	int seconds = (int)runningTime % 60;

	std::string timerTxt = TextFormat("%02i:%02i", minutes, seconds);

	float timerSize = MeasureText(timerTxt.c_str(), 60);

	DrawText(timerTxt.c_str(), canvasWidth - timerSize - timerGap, 25, 60, BLACK);
}

void MemoryGame::RestartGame()
{
	tile1 = nullptr;
	tile2 = nullptr;

	SetupGame();
}