#pragma once

#include "Level/Level.h"
#include "Math/Vector2.h"
#include <vector>
#include "Algorithm/Node.h"
#include "Algorithm/AStar.h"
#include <queue>
#include "Actor/Player.h"
#include "Actor/Start.h"
#include "Actor/Wall.h"

class WallPos
{
public:
	int x;
	int y;
	Wall* wall;
};

class DemoLevel : public Level
{
	// RTTI Á¤ÀÇ.
	RTTI_DECLARATIONS(DemoLevel, Level)

public:
	DemoLevel();
	void DrawPath();
	virtual void Draw() override;
	void CreateObstacle();
	virtual void Update(float deltaTime) override;

	void GoThroughPath(float deltaTime);
	void ShowClosedPath(float deltaTime);

	void ClearDatas();
	

	void SetEnd(Vector2 end) { this->endXY = end; }
	void SetStart(Vector2 start) { this->startXY = start; }

	std::vector<Node*> FindPath(Node* startNode, Node* goalNode, DemoLevel* refLevel, int (*wallsPos)[100]);

	void createWall();

public:
	std::vector<Node*> closedList;
	int printCheck = 0;

private:
	Vector2 endXY;
	Vector2 startXY;

	AStar aStar;

	std::vector<Node*> path;
	std::queue<Vector2> ways;
	std::queue<Vector2> closedWays;
	std::vector<Vector2> showClosedWays;


	Vector2 startVector;
	Node* startNode;

	Vector2 endVector;
	Node* endNode;


	int wallX;
	int wallY;
	int wallAccount;

	float deltatime;

	Player* player;

	Start* start;

	int wallsPos[100][100];
	std::vector<WallPos*> vWall;


	
};