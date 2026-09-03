#include "SnakeGame.h"
#include "raymath.h"
#include <iostream>

/*
	Optional -> Game Pause (Press P)
	Optional -> Tail Count (Print tail num on each Tail)
	Optional -> Barriers

	Github + Video + Read me
*/

void SnakeGame::Main()
{
	Start();

	InitWindow(screenWidth, screenHeight, "Snake Game");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		Update();

		EndDrawing();
	}
}

void SnakeGame::Start()
{
	for (int i = 0; i < screenWidth / TILE_SIZE + 1; i++)
	{
		float x = borderGap.x / 2 + TILE_SIZE * i;
		float yTop = borderGap.y / 2;
		float yBottom = screenHeight - borderGap.y / 2;

		Vector2 start = Vector2{ x, yTop };
		Vector2 end = Vector2{ x, yBottom };

		Line line = Line(start, end);
		grid.push_back(line);
	}

	for (int i = 0; i < screenHeight / TILE_SIZE + 1; i++)
	{
		float y = borderGap.y / 2 + TILE_SIZE * i;
		float xLeft = borderGap.x / 2;
		float xRight = screenWidth - borderGap.x / 2;

		Vector2 start = Vector2{ xLeft, y };
		Vector2 end = Vector2{ xRight, y };

		Line line = Line(start, end);
		grid.push_back(line); (start, end, GRAY);
	}

	//Player head
	Piece head;
	head.color = DARKGREEN;
	head.position = Vector2{ borderGap.x / 2, borderGap.y / 2 };
	player.push_back(head);

	fruit.color = DARKPURPLE;
	fruit.RandomLoc(borderGap);
	
	// Extra
	powerUp.color = ORANGE;
}

void SnakeGame::Update()
{
	Interaction();

	if (currentFrame % 20 == 0)
	{
		for (int i = player.size() - 1; i > 0; i--)
			player[i].position = player[i - 1].position;

		player[0].position += speed;
	}

	if (player[0].position == fruit.position)
	{
		Piece tail;
		tail.color = GREEN;
		player.push_back(tail);

		for (int i = 0; i < player.size(); i++)
		{
			if (fruit.position == player[i].position)
			{
				fruit.RandomLoc(borderGap);
			}
		}
	}
	// Extra
	if (player[0].position == powerUp.position)
	{
		powerUpFrame = 0;
		powerUp.isActive = true;

		for (int i = 0; i < player.size() - 1; i++)
		{
			invencibleSize++;
			player.pop_back();
		}

		isInvencible = true;
		invencibleFrame = 0;
	}
	//
	// Extra
	if (isInvencible)
	{
		invencibleFrame++;
		
		if (invencibleFrame % 180 == 0)
		{
			for (int i = 0; i < invencibleSize; i++)
			{
				Piece tail;
				tail.color = GREEN;
				player.push_back(tail);
			}

			isInvencible = false;
			invencibleSize = 0;
			invencibleFrame = 0;
		}
	}
	//
	// Extra
	if (powerUpFrame % 300 == 0)
	{
		if (!powerUp.isActive)
		{
			powerUp.RandomLoc(borderGap);
			powerUp.isActive = true;
		}
		else
		{
			powerUp.isActive = false;
		}
	}
	//
	if (player.size() > 1)
	{
		for (int i = 1; i < player.size(); i++)
		{
			if (player[0].position == player[i].position)
			{
				gameOver = true;
			}
		}
	}

	currentFrame++;
	// Extra
	powerUpFrame++;
	//
	if (!gameOver)
		gameOver = player[0].Bumped(min, max);

	if (!gameOver)
	{
		for (Piece p : player)
			p.Draw();

		fruit.Draw();

		// Extra
		if (powerUp.isActive)
			powerUp.Draw();
		//
		for (Line l : grid)
			l.Draw();
	}
	else
	{
		int fontSize = 80;

		int textWidth = MeasureText("Game Over", fontSize);

		DrawText("Game Over", screenWidth / 2 - textWidth / 2, screenHeight / 2 - fontSize / 2, fontSize, BLACK);
	}
}

void SnakeGame::Interaction()
{
	if (gameOver)
		return;

	if (IsKeyReleased(KEY_LEFT) && speed.x == 0)
	{
		speed = Vector2{ -TILE_SIZE, 0 };
		currentFrame = 0;
	}

	if (IsKeyReleased(KEY_RIGHT) && speed.x == 0)
	{
		speed = Vector2{ TILE_SIZE, 0 };
		currentFrame = 0;
	}

	if (IsKeyReleased(KEY_UP) && speed.y == 0)
	{
		speed = Vector2{ 0, -TILE_SIZE };
		currentFrame = 0;
	}

	if (IsKeyReleased(KEY_DOWN) && speed.y == 0)
	{
		speed = Vector2{ 0, TILE_SIZE };
		currentFrame = 0;
	}
}
