#include "Structure.h"

void Structure::Main()
{
	Start();

	InitWindow(600, 600, "Unity-Style Raylib Struct");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		Update();

		EndDrawing();
	}
}

void Structure::Start()
{

}

void Structure::Update()
{

}
