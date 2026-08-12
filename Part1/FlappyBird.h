#pragma once
#include "raylib.h"
#include <vector>

class FlappyBird
{
public:
	static const int screenWidth = 800;
	static const int screenHeight = 450;

	struct Player
	{
		Vector2 position;
		int radius = 20;
		Color color = BLACK;

		void Draw()
		{
			DrawCircleV(position, radius, color);
		}

		void Update()
		{
			if (IsKeyDown(KEY_SPACE))
			{
				position.y -= 5;
			}
			else
			{
				position.y += 1;
			}
		}
	};

	struct Column
	{
		Rectangle topRect;
		Rectangle bottomRect;

		bool scored = false;

		Column(float x)
		{
			float topHeight = GetRandomValue(20, 300);
			float gap = GetRandomValue(100, 200);
			float y1 = 0;
			float y2 = topHeight + gap;
			float bottomHeight = screenHeight - y2;

			topRect = Rectangle{ x, y1, 80, topHeight };
			bottomRect = Rectangle{ x, y2, 80, bottomHeight };
		}

		void Draw()
		{
			DrawRectangleRec(topRect, GREEN);
			DrawRectangleRec(bottomRect, GREEN);
		}

		void Update()
		{
			topRect.x -= 1;
			bottomRect.x -= 1;
		}

		bool CheckCollisionWithPlayer(Player player)
		{
			return CheckCollisionCircleRec(player.position, player.radius, topRect) ||
				CheckCollisionCircleRec(player.position, player.radius, bottomRect);
		}

		bool PlayerCrossed(Player player)
		{
			if (topRect.x < player.position.x + player.radius)
				return true;

			return false;
		}
	};

	Player player = { 0 };
	std::vector<Column> columns;
	bool gameOver = false;
	int score = 0;

	void Main();
	void Start();
	void Update();
};