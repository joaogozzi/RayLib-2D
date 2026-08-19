#pragma once
#include "raylib.h"
#include <vector>

class SnakeGame
{
public:
#define TILE_SIZE 33

	static const int screenWidth = 800;
	static const int screenHeight = 600;

	Vector2 borderGap = Vector2{ screenWidth % TILE_SIZE, screenHeight % TILE_SIZE };
	Vector2 min = Vector2{ borderGap.x / 2, borderGap.y / 2 };
	Vector2 max = Vector2{ screenWidth - borderGap.x / 2, screenHeight - borderGap.y / 2 };

	struct Line
	{
		Line(Vector2 s, Vector2 e)
		{
			start = s;
			end = e;
		}

		Vector2 start;
		Vector2 end;

		void Draw()
		{
			DrawLineV(start, end, GRAY);
		}
	};

	std::vector<Line> grid;

	struct Piece
	{
		Vector2 position;
		Vector2 size = Vector2{ TILE_SIZE, TILE_SIZE };
		Color color;
		bool isActive = true;

		void Draw()
		{
			DrawRectangleV(position, size, color);
		}

		bool Bumped(Vector2 min, Vector2 max)
		{
			if (position.x < min.x || position.x >= max.x || position.y >= max.y || position.y < min.y)
				return true;

			return false;
		}

		void RandomLoc(Vector2 borderGap)
		{
			float x = GetRandomValue(0, screenWidth / TILE_SIZE - 1) * TILE_SIZE + borderGap.x / 2;
			float y = GetRandomValue(0, screenHeight / TILE_SIZE - 1) * TILE_SIZE + borderGap.y / 2;

			position = Vector2{ x, y };
		}
	};

	std::vector<Piece> player;
	Piece fruit;
	Piece powerUp;
	Vector2 speed = Vector2{ TILE_SIZE, 0 };
	bool isInvencible = false;

	int currentFrame = 0;
	int powerUpFrame = 0;
	int invencibleFrame = 0;

	int invencibleSize = 0;

	bool gameOver = false;

	void Main();
	void Start();
	void Update();
	void Interaction();
};