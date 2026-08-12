#pragma once
#include <raylib.h>
#include <vector>
#include <functional>
#include <string>
#include "MemoryTile.h"

class MemoryGame
{
public:
#define GAP 16
#define WAIT_TIME 0.5
	const static int canvasWidth = 1100;
	const static int gameWidthHeight = 800;
	int gridSize = 4;

	std::vector<MemoryTile> tiles;

	double restartTime = 0.0;
	bool restarting = false;

	bool gameFinished = false;
	bool compareMode = false;
	float timeOfSecondClick = WAIT_TIME;
	float startTime = 0.0f;
	float runningTime = 0.0f;

	MemoryTile* tile1 = nullptr;
	MemoryTile* tile2 = nullptr;

	void Main();
	void Start();
	void Update();

	void SetupGame();

	void DrawUI();
	void DrawButton(const std::string& buttonText, Rectangle buttonRect, const std::function<void()>& func);
	void DrawTimer();

	void RestartGame();
};