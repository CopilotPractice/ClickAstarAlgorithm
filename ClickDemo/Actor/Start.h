#pragma once

#include "Actor/DrawableActor.h"


class DemoLevel;
class Start : public DrawableActor
{
public:
	Start(DemoLevel* refLevel);

	virtual void Update(float deltaTime) override;
private:
	DemoLevel* refLevel;
};