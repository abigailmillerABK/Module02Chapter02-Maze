#pragma once
#include "PlacableActor.h"
class Key : public PlacableActor
{
public:
	Key(int x, int y, ActorColor color)
		: PlacableActor(x, y, color)
	{
		doesMove = false;
	}

	virtual ActorType GetType() override { return ActorType::Key; }
	virtual void Draw() override;
	bool CollideWith(PlacableActor* actor) override;
};

