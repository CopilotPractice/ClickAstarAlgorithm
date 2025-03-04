#include "Player.h"
#include "Engine/Engine.h"
#include "Level/DemoLevel.h"

//Player::Player()
//	: DrawableActor("e")
//{
//	color = Color::Green;
//	position = Vector2(5, 5);
//	endPos = position;
//}

Player::Player(DemoLevel* refLevel)
	: DrawableActor("e"), refLevel(refLevel)
{
	color = Color::Green;
	position = Vector2(0, 0);
	//endPos = position;
}

void Player::Update(float deltaTime)
{
	DrawableActor::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	if (Engine::Get().GetKeyDown(VK_RBUTTON))
	{
		if (!(Engine::Get().MousePosition().x < 0 || Engine::Get().MousePosition().x > Engine::Get().ScreenSize().x
			|| Engine::Get().MousePosition().y < 0 || Engine::Get().MousePosition().y > Engine::Get().ScreenSize().y))
		{
		position = Engine::Get().MousePosition();
		refLevel->SetEnd(position);
		refLevel->DrawPath();
		}
	}
}
