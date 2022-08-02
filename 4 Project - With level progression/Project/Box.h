#pragma once
#include "PlacableActor.h"
class Box : public PlacableActor 
{
public:
	Box(int x, int y);

	virtual ActorType GetType() override { return ActorType::Box; }
	virtual void Draw() override;
	bool CollideWith(PlacableActor* actor) { return true; }
	bool doesMove = true;
};