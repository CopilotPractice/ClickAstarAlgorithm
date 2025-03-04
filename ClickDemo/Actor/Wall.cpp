#include "Wall.h"

Wall::Wall(int x, int y, Color inputColor)
	: DrawableActor("#")
{
	Vector2 pos = { x, y };
	color = inputColor;
	position = pos;
}

void Wall::Update(float deltaTime)
{
	Super::Update(deltaTime);

	
}