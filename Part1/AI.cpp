#include "AI.h"
#include <queue>
#include <time.h>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <raymath.h>

Node* GetFreeSlot(std::vector<std::vector<Node>>& grid)
{
	int randRow;
	int randCol;

	do
	{
		randRow = GetRandomValue(0, grid.size() - 1);
		randCol = GetRandomValue(0, grid[0].size() - 1);
	} while (grid[randRow][randCol].blocked || grid[randRow][randCol].isEnd);

	return &grid[randRow][randCol];
}

void AI::Main()
{
	Start();

	int width = COLS * NODE_SIZE;
	int height = ROWS * NODE_SIZE;

	InitWindow(width, height, "AI");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		Update();

		EndDrawing();
	}
}

void AI::Start()
{
	SetRandomSeed(time(0));
	grid.clear();

	for (int row = 0; row < ROWS; row++)
	{
		std::vector<Node> rowNodes;
		float y = NODE_SIZE * row;

		for (int col = 0; col < COLS; col++)
		{
			float x = NODE_SIZE * col;
			Node node = Node(row, col, { x, y }, { NODE_SIZE, NODE_SIZE }, DARKGRAY);
			rowNodes.push_back(node);
		}

		grid.push_back(rowNodes);
	}

	int twentyPercent = grid.size() * grid[0].size() * 0.2;
	for (int i = 0; i < twentyPercent; i++)
	{
		Node* node = GetFreeSlot(grid);

		node->blocked = true;
		node->fillColor = GRAY;
	}

	CreateSlope(4.0f);
	CreateSlope(5.0f);
	CreateSlope(3.0f);

	start = GetFreeSlot(grid);
	start->blocked = true;
	start->fillColor = BLUE;
	start->txt = "S";

	end = GetFreeSlot(grid);
	end->isEnd = true;
	end->fillColor = GREEN;
	end->txt = "E";

	drawingSearch = true;
	drawingPath = false;

	searchIndex = 0;
	pathIndex = 0;

	ASTAR(start, end);
}

void AI::Update()
{
	float deltaTime = GetFrameTime();

	UpdateAnimation(deltaTime);

	for (int row = 0; row < grid.size(); row++)
	{
		for (int col = 0; col < grid[row].size(); col++)
		{
			grid[row][col].Draw();
		}
	}

	if (IsKeyPressed(KEY_SPACE))
	{
		Start();
	}
}

std::vector<Node*> AI::GetNeighbors(Node* node)
{
	std::vector<Node*> neighbors;

	auto isWithinGrid = [&](int row, int col) -> bool
		{
			return row >= 0 && col >= 0 && row < ROWS && col < COLS;
		};

	//Above
	if (isWithinGrid(node->row - 1, node->col))
		neighbors.push_back(&grid[node->row - 1][node->col]);

	//Below
	if (isWithinGrid(node->row + 1, node->col))
		neighbors.push_back(&grid[node->row + 1][node->col]);

	//Left
	if (isWithinGrid(node->row, node->col - 1))
		neighbors.push_back(&grid[node->row][node->col - 1]);

	//Right
	if (isWithinGrid(node->row, node->col + 1))
		neighbors.push_back(&grid[node->row][node->col + 1]);

	return neighbors;
}

void AI::BFS(Node* start, Node* goal)
{
	path.clear();
	searchNodes.clear();
	std::queue<Node*> queue;

	queue.push(start);
	start->visited = true;

	while (!queue.empty())
	{
		Node* current = queue.front();
		queue.pop();

		if (current == goal)
		{
			while (current != start)
			{
				path.push_back(current);
				current = current->parent;
			}

			std::reverse(path.begin(), path.end());
			return;
		}

		for (Node* neighbor : GetNeighbors(current))
		{
			if (neighbor->blocked || neighbor->visited)
				continue;

			neighbor->visited = true;
			neighbor->parent = current;

			queue.push(neighbor);
			searchNodes.push_back(neighbor);
		}
	}

	std::cout << "No viable BFS path\n";
}

void AI::DFS(Node* start, Node* goal)
{
	path.clear();
	searchNodes.clear();

	std::stack<Node*> stack;

	stack.push(start);
	start->visited = true;

	while (!stack.empty())
	{
		Node* current = stack.top();
		stack.pop();

		if (current == goal)
		{
			while (current != start)
			{
				path.push_back(current);
				current = current->parent;
			}

			std::reverse(path.begin(), path.end());
			return;
		}

		for (Node* neighbor : GetNeighbors(current))
		{
			if (neighbor->blocked || neighbor->visited)
				continue;

			neighbor->visited = true;
			neighbor->parent = current;

			stack.push(neighbor);
			searchNodes.push_back(neighbor);
		}
	}

	std::cout << "No viable DFS path\n";
}

void AI::DJK(Node* start, Node* goal)
{
	path.clear();
	searchNodes.clear();

	auto Compare = [](Node* a, Node* b)
		{
			return a->gCost > b->gCost;
		};

	std::priority_queue<Node*, std::vector<Node*>, decltype(Compare)> openSet(Compare);

	/*struct Compare
	{
		bool operator()(Node* a, Node* b) const
		{
			return a->gCost > b->gCost;
		}
	};

	std::priority_queue<Node*, std::vector<Node*>, Compare> queue;*/

	openSet.push(start);
	start->visited = true;
	start->gCost = 0;

	while (!openSet.empty())
	{
		Node* current = openSet.top();
		openSet.pop();

		if (current == goal)
		{
			while (current != start)
			{
				path.push_back(current);
				current = current->parent;
			}

			std::reverse(path.begin(), path.end());
			return;
		}

		for (Node* neighbor : GetNeighbors(current))
		{
			if (neighbor->blocked || neighbor->visited)
				continue;

			float tentativeCost = current->gCost + 1;

			if (tentativeCost < neighbor->gCost)
			{
				neighbor->gCost = tentativeCost;
				neighbor->visited = true;
				neighbor->parent = current;

				openSet.push(neighbor);
				searchNodes.push_back(neighbor);
			}
		}
	}

	std::cout << "No viable DJK path\n";
}

void AI::ASTAR(Node* start, Node* goal)
{
	path.clear();
	searchNodes.clear();

	auto Heuristic = [](Node* a, Node* b)
		{
			return static_cast<float>(abs(a->row - b->row) + abs(a->col - b->col));
		};

	auto Compare = [](Node* a, Node* b)
		{
			return a->fCost > b->fCost || (a->fCost == b->fCost && a->hCost > b->hCost);
		};

	std::priority_queue<Node*, std::vector<Node*>, decltype(Compare)	> openSet(Compare);

	start->gCost = 0.0f;
	start->hCost = Heuristic(start, goal);
	start->fCost = start->gCost + start->hCost;

	openSet.push(start);

	while (!openSet.empty())
	{
		Node* current = openSet.top();
		openSet.pop();

		if (current->visited)
			continue;

		current->visited = true;

		if (current == goal)
		{
			while (current != nullptr)
			{
				path.push_back(current);

				if (current == start)
					break;

				current = current->parent;
			}

			std::reverse(path.begin(), path.end());
			return;
		}

		for (Node* neighbor : GetNeighbors(current))
		{
			if (neighbor->blocked || neighbor->visited)
				continue;

			float movementCost = 1.0f + neighbor->slopeValue;

			float tentativeCost = current->gCost + movementCost;

			if (tentativeCost < neighbor->gCost)
			{
				neighbor->parent = current;
				neighbor->gCost = tentativeCost;
				neighbor->hCost = Heuristic(neighbor, goal);
				neighbor->fCost = neighbor->gCost + neighbor->hCost;

				openSet.push(neighbor);

				searchNodes.push_back(neighbor);
			}
		}
	}

	std::cout << "No viable A* path\n";
}

void AI::UpdateAnimation(float deltaTime)
{
	timer += deltaTime;

	if (timer < drawDelay)
		return;

	timer = 0.0f;

	// Draw Search
	if (drawingSearch)
	{
		if (searchIndex < searchNodes.size())
		{
			Node* node = searchNodes[searchIndex];

			if (node != start && node != end && !node->blocked)
			{
				node->fillColor = PURPLE;
			}

			searchIndex++;
		}
		else
		{
			drawingSearch = false;
			drawingPath = true;

			pathIndex = 0;
		}
	}

	// Draw Path
	else if (drawingPath)
	{
		if (pathIndex < path.size())
		{
			Node* node = path[pathIndex];

			if (node != start && node != end)
			{
				node->fillColor = YELLOW;
			}

			pathIndex++;
		}
		else
		{
			drawingPath = false;
		}
	}
}

void AI::CreateSlope(float radius)
{
	int centerRow;
	int centerCol;

	do
	{
		centerRow = GetRandomValue(0, ROWS - 1);
		centerCol = GetRandomValue(0, COLS - 1);

	} while (grid[centerRow][centerCol].blocked);

	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			Node& node = grid[row][col];

			if (node.blocked || &node == start || &node == end)
				continue;

			float distX = col - centerCol;
			float distY = row - centerRow;

			float distance = sqrtf(distX * distX + distY * distY);

			if (distance > radius)
				continue;

			float normalizedDistance = distance / radius;
			float slope = 1.0f - normalizedDistance * normalizedDistance;

			slope = Clamp(slope, 0.0f, 1.0f);

			node.AddSlope(slope);
		}
	}
}
