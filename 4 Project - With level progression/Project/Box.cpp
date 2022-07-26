#include <iostream>
#include <windows.h>
#include "Box.h"

Box::Box(int x, int y)
	: PlacableActor(x,y)
{
}

void Box::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);

	std::cout << 'B';
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}
