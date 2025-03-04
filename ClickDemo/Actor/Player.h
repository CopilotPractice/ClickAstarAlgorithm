#pragma once

#include "Actor/DrawableActor.h"

class DemoLevel;
class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	//Player();
	Player(DemoLevel* refLevel);

	virtual void Update(float deltaTime) override;

	//virtual void SetPosition(Node* next) override;
	//virtual void SetPosition(const Vector2& newPosition) override;

private:
	Vector2 endPos;
	DemoLevel* refLevel;
};