#include "Start.h"
#include "Engine/Engine.h"
#include "Level/DemoLevel.h"



Start::Start(DemoLevel* refLevel)
	: DrawableActor("s"), refLevel(refLevel)
{
	color = Color::Red;

}


void Start::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_LBUTTON))
	{
		if (!(Engine::Get().MousePosition().x < 0 || Engine::Get().MousePosition().x > Engine::Get().ScreenSize().x
			|| Engine::Get().MousePosition().y < 0 || Engine::Get().MousePosition().y > Engine::Get().ScreenSize().y))
		{
			position = Engine::Get().MousePosition();
			refLevel->SetStart(position);
			refLevel->ClearDatas();
			refLevel->printCheck = 0;

			
		}
		
	}
}

