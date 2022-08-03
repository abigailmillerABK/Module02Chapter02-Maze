#include <iostream>
#include "Money.h"
#include "AudioManager.h"
#include "Player.h"

Money::Money(int x, int y, int worth)
	: PlacableActor(x, y)
	, m_worth(worth)
{
	doesMove = false;
}

void Money::Draw()
{
	std::cout << "$";
}

bool Money::CollideWith(PlacableActor* actor) {
	if (actor->GetType() == ActorType::Player) {
		AudioManager::GetInstance()->PlayMoneySound();
		Remove();
		Player* player = dynamic_cast<Player*>(actor);
		player->AddMoney(GetWorth());
		return true;
	}
}
