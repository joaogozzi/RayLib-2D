#pragma once
#include <raylib.h>
#include <string>
#include <float.h>

struct Node
{
	int row;
	int col;

	Vector2 position;
	Vector2 size;

	Color outlinerColor;
	Color fillColor = BLANK;
	Color slopeColor = BLANK;

	std::string txt = "";

	bool blocked = false;
	bool visited = false;
	bool isEnd = false;
	bool hasSlope = false;

	Node* parent = nullptr;

	float gCost = FLT_MAX;
	float hCost = FLT_MAX;
	float fCost = FLT_MAX;

	float slopeValue = 0.0f;

	Node(int r, int c, Vector2 pos, Vector2 sze, Color color)
	{
		col = c;
		row = r;
		position = pos;
		size = sze;
		outlinerColor = color;
	}

	void AddSlope(float value)
	{
		hasSlope = true;

		slopeValue = value;
		slopeColor = Fade(RED, slopeValue * 0.9f);
	}

	void Draw()
	{
		DrawRectangleV(position, size, RAYWHITE);

		if (fillColor.a > 0)
			DrawRectangleV(position, size, fillColor);

		if (slopeValue > 0.0f)
			DrawRectangleV(position, size, slopeColor);

		DrawRectangleLines(position.x, position.y, size.x, size.y, outlinerColor);

		int fontSize = 20;
		int textWidth = MeasureText(txt.c_str(), fontSize);
		float txtX = position.x + size.x / 2 - textWidth / 2;
		float txtY = position.y + size.y / 2 - fontSize / 2;

		DrawText(txt.c_str(), txtX, txtY, fontSize, BLACK);
	}
};