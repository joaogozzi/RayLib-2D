#include "raylib.h"
#include "raymath.h"
#include "ParticlesSystem.h"
#include "FlappyBird.h"
#include "Game2048.h"
#include "MemoryGame.h"
#include "SnakeGame.h"
#include <string>
#include <random>
#include <vector>
#include <iostream>

void DrawingTemplate()
{
	InitWindow(500, 500, "Game");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(GRAY);

		EndDrawing();
	}

	CloseWindow();
}

#pragma region Class 1

int RandomNum(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::uniform_int_distribution<> dis(min, max);

	return dis(gen);
}

void BasicDrawing()
{
	InitWindow(500, 500, "Game");
	SetTargetFPS(60);

	int r = 500 / 8;

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(GRAY);

		DrawCircle(r, r, r, RED);
		DrawCircle(r * 3, r, r, GREEN);
		DrawCircle(r * 5, r, r, BLUE);
		DrawCircle(r * 7, r, r, BLACK);

		int posX = 20;
		int posY = 500 / 2 - 100 / 2;
		int w = 500 - 40;
		int h = 100;

		DrawRectangle(posX, posY, w, h, YELLOW);

		DrawPoly(Vector2{ 250, 390 }, 5, 110, 90, RED);

		EndDrawing();
	}

	CloseWindow();
}

void DrawButton(std::string text, int fontSize)
{
	InitWindow(500, 500, "Game");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(GRAY);

		int textWidth = MeasureText(text.c_str(), fontSize);

		int buttonWidth = textWidth + 40;
		int buttonHeight = fontSize + 20;

		int butX = 250 - buttonWidth / 2;
		int butY = 250 - buttonHeight / 2;

		int txtX = 250 - textWidth / 2;
		int txtY = 250 - fontSize / 2;

		Rectangle rect = Rectangle{ (float)butX, (float)butY, (float)buttonWidth, (float)buttonHeight };
		DrawRectangleRounded(rect, 0.5, 8, ORANGE);

		DrawText(text.c_str(), txtX, txtY, fontSize, WHITE);

		EndDrawing();
	}

	CloseWindow();
}

void MoveCircle()
{
	int w = 500;
	int h = 500;

	int centerX = w / 2;
	int centerY = h / 2;

	InitWindow(w, h, "Move Circle");
	SetTargetFPS(60);

	int dir = 1;
	int speed = 5;

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(GRAY);

		DrawCircle(centerX, centerY, 50, RED);

		if (centerY + 50 > h || centerY < 50)
			dir *= -1;

		centerY += dir * speed;

		EndDrawing();
	}

	CloseWindow();
}

void BounceBall()
{
	int w = 700;
	int h = 500;

	int r1 = 70;
	int r2 = 50;

	int radSum = r1 + r2;
	int radSumSqr = radSum * radSum;

	int ball1PosX = RandomNum(r1, w - r1);
	int ball1PosY = RandomNum(r1, h - r1);

	int ball2PosX = RandomNum(r2, w - r2);
	int ball2PosY = RandomNum(r2, h - r2);

	int ball1DirX = 1;
	int ball1DirY = 1;

	int ball2DirX = -1;
	int ball2DirY = -1;

	int speed = 5;

	InitWindow(w, h, "Bounce Balls");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(GRAY);

		DrawCircle(ball1PosX, ball1PosY, r1, RED);
		DrawCircle(ball2PosX, ball2PosY, r2, BLUE);

		// Ball 1
		if (ball1PosX + r1 > w || ball1PosX < r1)
			ball1DirX *= -1;

		if (ball1PosY + r1 > h || ball1PosY < r1)
			ball1DirY *= -1;

		// Ball 2
		if (ball2PosX + r2 > w || ball2PosX < r2)
			ball2DirX *= -1;

		if (ball2PosY + r2 > h || ball2PosY < r2)
			ball2DirY *= -1;

		// -----------

		int distX = ball2PosX - ball1PosX;
		int distY = ball2PosY - ball1PosY;

		int distSqr = (distX * distX) + (distY * distY);

		if (distSqr <= radSumSqr)
		{
			ball1DirX *= -1;
			ball1DirY *= -1;

			ball2DirX *= -1;
			ball2DirY *= -1;
		}

		ball1PosX += ball1DirX * speed;
		ball1PosY += ball1DirY * speed;

		ball2PosX += ball2DirX * speed;
		ball2PosY += ball2DirY * speed;

		EndDrawing();
	}

	CloseWindow();
}

#pragma endregion

#pragma region Class 2

void MultiplyColors()
{
	InitWindow(800, 800, "Game");
	SetTargetFPS(60);

	BlendMode blend = BLEND_MULTIPLIED;

	int mouseX;
	int mouseY;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		BeginBlendMode(blend);

		mouseX = GetMouseX();
		mouseY = GetMouseY();

		DrawCircle(400, GetMouseY(), 200, MAGENTA);
		DrawCircle(mouseX, 800 - mouseY, 200, YELLOW);
		DrawCircle(800 - mouseX, 800 - mouseY, 200, CYAN);

		EndBlendMode();

		EndDrawing();
	}

	CloseWindow();
}

void BoucingBall()
{
	InitWindow(360, 720, "Bouncing Ball");
	SetTargetFPS(60);

	float gravity = 9.8f;
	float speed = 1;
	float y = 50;
	float deltaTime = 0;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(GRAY);

		DrawCircle(180, y, 16, WHITE);

		deltaTime = GetTime();

		y += (gravity * (deltaTime * deltaTime)) / 2;

		if (y + 16 > 720)
		{
			y = 720 - 16;
			gravity *= -1;
		}

		EndDrawing();
	}

	CloseWindow();
}

void DrawTriangleFunc()
{
	InitWindow(360, 720, "Triangle");
	SetTargetFPS(60);

	Vector2 top = Vector2{ 180, 50 };
	Vector2 left = Vector2{ 50, 720 - 50 };
	Vector2 right = Vector2{ 360 - 50, 720 - 50 };

	Vector2 mousePos;

	bool attachTop = false;
	bool attachLeft = false;
	bool  attachRight = false;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(GRAY);

		DrawTriangle(top, left, right, GREEN);

		DrawCircleV(top, 20, WHITE);
		DrawCircleV(left, 20, WHITE);
		DrawCircleV(right, 20, WHITE);

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			mousePos = GetMousePosition();

			float topDist = Vector2Distance(mousePos, top);
			float leftDist = Vector2Distance(mousePos, left);
			float rightDist = Vector2Distance(mousePos, right);

			if (topDist < 20)
			{
				attachTop = true;
			}
			else if (leftDist < 20)
			{
				attachLeft = true;
			}
			else if (rightDist < 20)
			{
				attachRight = true;
			}
		}

		if (attachTop)
		{
			top = mousePos;
		}
		else if (attachLeft)
		{
			left = mousePos;
		}
		else if (attachRight)
		{
			right = mousePos;
		}

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			attachTop = false;
			attachLeft = false;
			attachRight = false;
		}

		EndDrawing();
	}

	CloseWindow();
}

void DrawPentagonWithTriangles()
{
	InitWindow(720, 1280, "Pentagon");
	SetTargetFPS(60);

	Vector2 center = Vector2{ 720 / 2, 1280 / 2 };
	int sides = 6;
	float r = 200;

	std::vector<Vector2> corners;
	float angle = 0;
	float x = 0;
	float y = 0;

	for (int i = 0; i < sides; i++)
	{
		angle = 360 / sides * i;
		x = center.x + cos(angle * DEG2RAD) * r;
		y = center.y + sin(angle * DEG2RAD) * r;

		corners.push_back(Vector2{ x, y });
	}

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(GRAY);

		DrawPoly(center, sides, r, 0, GREEN);

		for (int i = 0; i < corners.size() - 1; i++)
		{
			DrawTriangleLines(center, corners[i + 1], corners[i], WHITE);
		}

		DrawTriangleLines(center, corners[0], corners[corners.size() - 1], WHITE);

		for (Vector2 any : corners)
		{
			DrawCircleV(any, 20, BLACK);
		}

		//DrawTriangle()

		EndDrawing();
	}

	CloseWindow();
}

void FinalExercise()
{
	InitWindow(1280, 720, "Game");
	SetTargetFPS(60);

	Vector2 rectPos = Vector2{ 1000, 200 };
	Vector2 rectSize = Vector2{ 200, 200 };

	Vector2 trianglePosT = Vector2{ 200, 400 };
	Vector2 trianglePosL = Vector2{ 100, 600 };
	Vector2 trianglePosR = Vector2{ 300, 600 };

	Vector2 centerTriangle = Vector2{ 200, 500 };

	Vector2 hexagonPos = Vector2{ 100, 300 };

	Vector2 circlePos = Vector2{ 1000, 600 };

	Vector2 mousePos;

	bool attachSquare = false;
	bool attachCircle = false;
	bool attachPoly = false;
	bool attachTriangle = false;

	bool squareDone = false;
	bool circleDone = false;
	bool polyDone = false;
	bool triangleDone = false;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(GRAY);

		DrawRectangleV(Vector2{ 300, 150 }, Vector2{ 205, 205 }, BLACK);
		DrawTriangle(Vector2{ 700, 145 }, Vector2{ 595, 350 }, Vector2{ 805, 350 }, BLACK);
		DrawPoly(Vector2{ 400, 550 }, 6, 105, 0, BLACK);
		DrawCircleV(Vector2{ 800, 550 }, 105, BLACK);

		if (!squareDone)
			DrawRectangleV(rectPos, rectSize, RED);

		if (!triangleDone)
			DrawTriangle(trianglePosT, trianglePosL, trianglePosR, RED);

		if (!polyDone)
			DrawPoly(hexagonPos, 6, 100, 0, RED);

		if (!circleDone)
			DrawCircleV(circlePos, 100, RED);

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			mousePos = GetMousePosition();

			float squareDist = Vector2Distance(mousePos, rectPos);
			float polyDist = Vector2Distance(mousePos, hexagonPos);
			float circleDist = Vector2Distance(mousePos, circlePos);
			float triangleDist = Vector2Distance(mousePos, centerTriangle);

			if (polyDist < 100 && !polyDone)
			{
				attachPoly = true;
			}
			else if (circleDist < 100 && !circleDone)
			{
				attachCircle = true;
			}
			else if (squareDist < 200 && !squareDone)
			{
				attachSquare = true;
			}
			else if (triangleDist < 100 && !triangleDone)
			{
				attachTriangle = true;
			}
		}

		if (attachPoly)
		{
			hexagonPos = mousePos;
		}
		else if (attachCircle)
		{
			circlePos = mousePos;
		}
		else if (attachSquare)
		{
			rectPos.x = mousePos.x - 100;
			rectPos.y = mousePos.y - 100;
		}
		else if (attachTriangle)
		{
			centerTriangle = mousePos;

			trianglePosT.x = centerTriangle.x;
			trianglePosT.y = centerTriangle.y - 100;

			trianglePosL.x = centerTriangle.x - 100;
			trianglePosL.y = centerTriangle.y + 100;

			trianglePosR.x = centerTriangle.x + 100;
			trianglePosR.y = centerTriangle.y + 100;
		}

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			attachCircle = false;
			attachPoly = false;
			attachSquare = false;
			attachTriangle = false;

			float squareDist = Vector2Distance(rectPos, Vector2{ 300, 150 });
			float polyDist = Vector2Distance(hexagonPos, Vector2{ 400, 550 });
			float circleDist = Vector2Distance(circlePos, Vector2{ 800, 550 });
			float triangleDist = Vector2Distance(centerTriangle, Vector2{ 700, 250 });

			if (squareDist < 10)
				squareDone = true;

			if (circleDist < 100)
				circleDone = true;

			if (polyDist < 100)
				polyDone = true;

			if (triangleDist < 10)
				triangleDone = true;
		}

		if (squareDone)
			DrawRectangleV(rectPos, rectSize, GREEN);

		if (circleDone)
			DrawCircleV(circlePos, 100, GREEN);

		if (polyDone)
			DrawPoly(hexagonPos, 6, 100, 0, GREEN);

		if (triangleDone)
			DrawTriangle(trianglePosT, trianglePosL, trianglePosR, GREEN);

		EndDrawing();
	}

	CloseWindow();
}

#pragma endregion

#pragma region Class 3

void CollisionFunc()
{
	InitWindow(500, 500, "Collision Test");
	SetTargetFPS(60);

	Rectangle boxA = { 50, 100, 300, 50 };
	int gravity = 1;

	Rectangle boxB = { 50, 300, 300, 50 };
	bool collision = false;

	while (!WindowShouldClose())
	{
		boxA.y += gravity;

		collision = CheckCollisionRecs(boxA, boxB);

		if (collision)
			DrawText("Collided", 100, 100, 30, BLUE);

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			collision = CheckCollisionPointRec(GetMousePosition(), boxB);

			if (collision)
				DrawText("Collided", 100, 100, 30, BLUE);
		}

		BeginDrawing();
		ClearBackground(GRAY);

		DrawRectangleRec(boxA, RED);
		DrawRectangleRec(boxB, GREEN);

		EndDrawing();
	}

	CloseWindow();
}

void UiButtonFunc()
{
	InitWindow(500, 500, "UI Button");
	SetTargetFPS(60);

	Rectangle buttonRect = { 100, 100, 300, 54 };
	Rectangle shadowRect = buttonRect;

	shadowRect.y += 5;

	Color curColor = GRAY;
	Color passiveColor = GRAY;
	Color hoverColor = BLUE;
	Color clickColor = GREEN;
	Color shadowColor = Color{ 30, 30, 30, 100 };

	Vector2 mouse = { 0, 0 };

	while (!WindowShouldClose())
	{
		mouse = GetMousePosition();

		BeginDrawing();
		ClearBackground(WHITE);

		curColor = passiveColor;

		if (CheckCollisionPointRec(GetMousePosition(), buttonRect))
		{
			curColor = hoverColor;

			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
				curColor = clickColor;
		}

		DrawRectangleRounded(shadowRect, 0.25f, 8, shadowColor);
		DrawRectangleRounded(buttonRect, 0.25f, 8, curColor);

		EndDrawing();
	}

	CloseWindow();
}

void LoadImgFunc()
{
	InitWindow(500, 500, "Load Image");
	SetTargetFPS(60);

	Image img = LoadImage("Resource Files/Dog.png");

	ImageResize(&img, 200, 200);
	ImageCrop(&img, Rectangle{ 150, 150, 50, 50 });

	Texture2D tex = LoadTextureFromImage(img);

	UnloadImage(img);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		DrawTexture(tex, 150, 150, WHITE);

		EndDrawing();
	}

	CloseWindow();
}

#pragma endregion

int main()
{
	SnakeGame game;
	game.Main();

	return 0;
}