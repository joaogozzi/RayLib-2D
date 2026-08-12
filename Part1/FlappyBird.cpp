#include "FlappyBird.h"
#include <string>

void FlappyBird::Main()
{
	Start();

	InitWindow(screenWidth, screenHeight, "Flappy Bird");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		Update();

		EndDrawing();
	}
}

void FlappyBird::Start()
{
	player.position = Vector2{ 80, (float)screenHeight / 2 - player.radius };

	for (int i = 0; i < 10; i++)
	{
		Column col = Column(200 + 250 * i);
		columns.push_back(col);
	}
}

void FlappyBird::Update()
{
	for (int i = 0; i < columns.size(); i++)
	{
		if (gameOver)
			break;

		columns[i].Update();
		columns[i].Draw();

		gameOver = columns[i].CheckCollisionWithPlayer(player);

		if (columns[i].PlayerCrossed(player) && !columns[i].scored)
		{
			columns[i].scored = true;
			score++;
		}
	}

	DrawText(std::to_string(score).c_str(), 20, 20, 20, BLACK);

	auto smallest = std::find_if(columns.begin(), columns.end(), [](Column& col) {
		return col.topRect.x + col.topRect.width < 0;
		});

	if (smallest != columns.end())
	{
		auto largest = std::max_element(columns.begin(), columns.end(), [](Column& a, Column& b) {
			return a.topRect.x < b.topRect.x;
			});

		smallest->topRect.x = largest->topRect.x + 250;
		smallest->bottomRect.x = largest->bottomRect.x + 250;
		smallest->scored = false;
	}

	player.Update();
	player.Draw();
}