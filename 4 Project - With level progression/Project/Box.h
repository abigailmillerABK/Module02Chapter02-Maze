#pragma once
#include "PlacableActor.h"
class Box : public PlacableActor 
{
public:
	Box(int x, int y);

	bool CollideWith(PlacableActor* actor);

	virtual ActorType GetType() override { return ActorType::Box; }
	virtual void Draw() override;
};