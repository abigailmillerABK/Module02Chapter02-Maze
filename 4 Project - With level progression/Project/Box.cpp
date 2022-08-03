#include <iostream>
#include <windows.h>
#include "Box.h"
#include "AudioManager.h"
#include "Enemy.h"

Box::Box(int x, int y)
	: PlacableActor(x,y)
{
	doesMove = true;
}

bool Box::CollideWith(PlacableActor* actor) {
	AudioManager::GetInstance()->PlayLoseLivesSound();
	Remove();
	if (actor->GetType() == ActorType::Enemy) {
		Enemy* enemy = dynamic_cast<Enemy*>(actor);
		enemy->ChangeDirection();
		return false;
	}
	return true;
}

void Box::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);

	std::cout << 'B';
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}
