#pragma once
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <algorithm>

struct Particle
{
	Vector2 center = { 0,0 };
	float radius = 1;
	Color color = BLACK;
	float speed = 0;
	float angle = 0;
	float gravity = 10;
	bool active = false;

	void Update()
	{
		if (!this->active)
			return;

		center.x += cos(angle * DEG2RAD) * std::max(speed, 1.0f);
		center.y += sin(angle * DEG2RAD) * std::max(speed, 1.0f) + gravity;

		float alpha = color.a / 255.0f;

		alpha -= 0.03f;

		if (color.a >= 0)
			color.a = alpha * 255.0f;
		else
			active = false;

		radius += 0.1f;
		speed -= 0.5f;
	}

	void Draw()
	{
		if (!this->active)
			return;

		this->Update();

		DrawCircleV(center, radius, color);
	}

	Color RandomColor()
	{
		return CLITERAL(Color)
		{
			static_cast<unsigned char>(GetRandomValue(0, 255)),
				static_cast<unsigned char>(GetRandomValue(0, 255)),
				static_cast<unsigned char>(GetRandomValue(0, 255)),
				255
		};
	}

	void Activate(Vector2 cen)
	{
		this->center = cen;
		this->radius = GetRandomValue(10, 15);
		this->angle = GetRandomValue(0, 360);
		this->speed = GetRandomValue(1, 1);
		this->color = RandomColor();

		active = true;
	}
};