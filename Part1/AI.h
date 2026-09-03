#pragma once
#include <raylib.h>
#include <vector>
#include "Node.h"

class AI
{
public:
#define ROWS 20
#define COLS 40
#define NODE_SIZE 25

	struct DijkstraPath
	{
		std::vector<Node*> path;
		int cost;
	};

	std::vector<std::vector<Node>> grid;
	std::vector<Node*> searchNodes;
	std::vector<Node*> path;
	Node* start;
	Node* end;

	int searchIndex = 0;
	int pathIndex = 0;

	float timer = 0.0f;
	float drawDelay = 0.03f;

	bool drawingSearch = true;
	bool drawingPath = false;

	void Main();
	void Start();
	void Update();

	std::vector<Node*> GetNeighbors(Node* node);
	void BFS(Node* start, Node* goal);
	void DFS(Node* start, Node* goal);
	void DJK(Node* start, Node* goal);
	void ASTAR(Node* start, Node* goal);
	void UpdateAnimation(float deltaTime);
	void CreateSlope(float radius);
};