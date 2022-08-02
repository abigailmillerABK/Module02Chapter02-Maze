#include <iostream>
#include <windows.h>

#include "Key.h"
#include "Player.h"
#include "AudioManager.h"

void Key::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);

	std::cout << "+";
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}

bool Key::CollideWith(PlacableActor* actor) {
	if (actor->GetType() == ActorType::Player) {
		Player* player = dynamic_cast<Player*>(actor);
		player->PickupKey(this);
		Remove();
		AudioManager::GetInstance()->PlayKeyPickupSound();
		return true;
	}
	
}
