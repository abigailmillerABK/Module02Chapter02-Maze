#include <iostream>
#include <windows.h>
#include "Door.h"
#include "AudioManager.h"
#include "Player.h"

Door::Door(int x, int y, ActorColor color, ActorColor closedColor)
	: PlacableActor(x, y, color)
	, m_isOpen(false)
	, m_closedColor(closedColor)
{
	doesMove = false;
}

void Door::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_isOpen)
	{
		SetConsoleTextAttribute(console, (int)m_color);
	}
	else
	{
		SetConsoleTextAttribute(console, (int)m_closedColor);
	}
	std::cout << "|";
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}

bool Door::CollideWith(PlacableActor* actor){
	if (actor->GetType() == ActorType::Player) {
		Player* player = dynamic_cast<Player*>(actor);
		if (player->HasKey(GetColor()))
		{
			Open();
			Remove();
			player->UseKey();
			AudioManager::GetInstance()->PlayDoorOpenSound();
			return true;
		}
		else
		{
			AudioManager::GetInstance()->PlayDoorClosedSound();
			return false;
		}
	}
	
}
