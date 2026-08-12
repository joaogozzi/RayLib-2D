#include "ParticlesSystem.h"

void ParticleSystem::Main()
{
	Start();

	InitWindow(720, 360, "Particle System");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		Update();


		EndDrawing();
	}
}

void ParticleSystem::Start()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		pool.push_back(Particle());
	}
}

void ParticleSystem::Update()
{
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		int rate = GetRandomValue(5, 20);

		for (int i = 0; i < rate; i++)
		{
			for (int j = 0; j < POOL_SIZE; j++)
			{
				if (!pool[j].active)
				{
					pool[j].Activate(GetMousePosition());
					break;
				}
			}
		}
	}


	for (int i = 0; i < POOL_SIZE; i++)
	{
		pool[i].Draw();
	}
}
