#include "DemoLevel.h"
#include "Actor/Player.h"
#include "Actor/Start.h"
#include "Algorithm/AStar.h"
#include "Algorithm/Node.h"
#include "Actor/Wall.h"
#include "Engine/Engine.h"

#include<string>
#include <Windows.h>
#include "Engine/Timer.h"

void DemoLevel::createWall()
{
	for (int i = 1;i < Engine::Get().ScreenSize().y-1;++i)
	{
		AddActor(new Wall(0, i, Color::Blue)); // 왼쪽 벽
		AddActor(new Wall(Engine::Get().ScreenSize().x-1, i, Color::Blue)); // 오른쪽 벽
	}

	for (int i = 0;i < Engine::Get().ScreenSize().x;++i)
	{
		AddActor(new Wall(i, 0, Color::Blue)); //위쪽 벽
		AddActor(new Wall(i, Engine::Get().ScreenSize().y - 1, Color::Blue)); // 아랫쪽 벽
	}
}

DemoLevel::DemoLevel()
{
	player = new Player(this);
	AddActor(player);
	AddActor(new Start(this));

	createWall();
}


void DemoLevel::GoThroughPath(float deltaTime)
{
	static float elapsedTime = 0.0f;
	static float moveTime = 0.15f;

	elapsedTime += deltaTime;
	if (elapsedTime < moveTime)
	{
		return;
	}

	elapsedTime = 0.0f;

	if (!ways.empty())
	{
		Vector2 next = ways.front();
		ways.pop();

		player->SetPosition(next);
	}
}

void DemoLevel::ShowClosedPath(float deltaTime)
{
	static float elapsedTime = 0.0f;
	static float moveTime = 0.01f;

	elapsedTime += deltaTime;
	if (elapsedTime < moveTime)
	{
		return;
	}

	elapsedTime = 0.0f;

	if (!closedWays.empty())
	{
		Vector2 next = closedWays.front();
		closedWays.pop();

		showClosedWays.push_back(next);
	}
}

void DemoLevel::ClearDatas()
{
	ways = std::queue<Vector2>();
	closedWays = std::queue<Vector2>();
	showClosedWays.clear();
	closedList.clear();

}




void DemoLevel::DrawPath()
{
	ways = std::queue<Vector2>();
	closedWays = std::queue<Vector2>();
	
	showClosedWays.clear();
	closedList.clear();

	startVector = Vector2(startXY.x, startXY.y);
	startNode = new Node(startVector);

	endVector = Vector2(endXY.x, endXY.y);
	endNode = new Node(endVector);

	printCheck = -1;
	path = aStar.FindPath(startNode, endNode, this, wallsPos);
	
	SafeDelete(endNode);

	for (Node* data : path)
	{
		printCheck = 1;
		ways.push(data->GetPosition());
	}

	if (!ways.empty())
	{
		ways.pop();
	}	

	for (Node* data : closedList)
	{
		if (data->GetPosition() == startVector || data->GetPosition() == endVector || data->GetPosition() == Vector2(0, 0))
		{
			continue;
		}

		bool flag = false;
		for (Node* p : path)
		{
			if (p->GetPosition() == data->GetPosition())
			{				
				flag = true;
				break;
			}
		}

		if (flag == false)
		{
			closedWays.push(data->GetPosition());
		}
	}
}



void DemoLevel::Draw()
{
	Super::Draw();

	char* buffer[256] = {};

	for (Node* data : closedList)
	{
		if (data->GetPosition() == startVector || data->GetPosition() == endVector || data->GetPosition() == Vector2(0, 0))
		{
			continue;
		}

		bool flag = false;
		for (Node* p : path)
		{
			if (p->GetPosition() == data->GetPosition())
			{
				flag = true;
				if (p->GetPosition() != player->Position())
				{
					Engine::Get().Draw(data->GetPosition(), "@", Color::Sky);
				}
				break;
			}
		}

		if (flag)
		{
			continue;
		}

	}
	
	for (auto s : showClosedWays)
	{
		Engine::Get().Draw(s, "@", Color::Gray);
	}

	
	if (printCheck == 0)
	{
		Engine::Get().Draw(Vector2(0, Engine::Get().ScreenSize().y - 1), "연산 처리 전");
	}

	if (printCheck == 1)
	{
		Engine::Get().Draw(Vector2(0, Engine::Get().ScreenSize().y - 1), "A* 연산 성공");
	}

	if (printCheck == -1)
	{
		Engine::Get().Draw(Vector2(0, Engine::Get().ScreenSize().y - 1), "A* 연산 실패");
	}
}


void DemoLevel::CreateObstacle()
{
	int x = Engine::Get().MousePosition().x;
	int y = Engine::Get().MousePosition().y;

	if (Engine::Get().GetKeyDown(VK_RETURN))
	{
		if (!(Engine::Get().MousePosition().x < 1 || x > Engine::Get().ScreenSize().x - 2
			|| Engine::Get().MousePosition().y < 1 || y > Engine::Get().ScreenSize().y - 2))
		{
			if (wallsPos[x][y] == 1)
			{
				for (auto& data : actors)
				{
					if (data->Position().x == x && data->Position().y == y)
					{
						data->Destroy();
						wallsPos[x][y] = 0;
					}
				}
			}
			else
			{
				Wall* wall = new Wall(x, y, Color::Red);
				AddActor(wall);
				WallPos wallpos = WallPos();
				wallpos.x = x;
				wallpos.y = y;
				wallpos.wall = wall;

				vWall.push_back(&wallpos);
				wallsPos[x][y] = 1;
			}
		}
	}
}

void DemoLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);
	
	GoThroughPath(deltaTime);

	ShowClosedPath(deltaTime);

	CreateObstacle();
}

