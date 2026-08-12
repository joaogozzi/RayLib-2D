#include "Game2048.h"
#include <random>
#include <iostream>

void Game2048::Main()
{
	Start();

	InitWindow(screenWidth, screenHeight, "2048");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		Update();


		EndDrawing();
	}
}

void Game2048::Start()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cells[i][j].rect.x = board.rect.x + 10 + (200 * i);
			cells[i][j].rect.y = board.rect.y + 10 + (200 * j);
		}
	}

	int x = 0;
	int y = 0;

	for (int i = 0; i < 3; i++)
	{
		x = RandomNum(0, 3);
		y = RandomNum(0, 3);

		while (cells[x][y].value != 0)
		{
			x = RandomNum(0, 3);
			y = RandomNum(0, 3);
		}

		cells[x][y].SpawnCell();
	}
}

void Game2048::Update()
{
	board.Draw();

	if (IsKeyPressed(KEY_RIGHT))
	{
		
	}

	if (IsKeyPressed(KEY_LEFT))
	{

	}

	if (IsKeyPressed(KEY_UP))
	{

	}

	if (IsKeyPressed(KEY_DOWN))
	{

	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cells[i][j].Draw();
		}
	}
}

int Game2048::RandomNum(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::uniform_int_distribution<> dis(min, max);

	return dis(gen);
}