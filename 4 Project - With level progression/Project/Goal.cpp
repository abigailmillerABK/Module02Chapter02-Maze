#include <iostream>
#include "Goal.h"

Goal::Goal(int x, int y)
	: PlacableActor(x, y)
{
	doesMove = false;
}

void Goal::Draw()
{
	std::cout << "X";
}
