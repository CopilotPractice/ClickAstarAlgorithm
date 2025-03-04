#pragma once

#include "Actor/DrawableActor.h"

class Wall : public DrawableActor
{
public:
	Wall(int posX, int posY, Color color);

	virtual void Update(float deltaTime) override;

};