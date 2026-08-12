#pragma once
#include "raylib.h"
#include "Particle.h"
#include <vector>

class ParticleSystem
{
public:
	#define POOL_SIZE 1000

	std::vector<Particle> pool;

	void Main();
	void Start();
	void Update();
};