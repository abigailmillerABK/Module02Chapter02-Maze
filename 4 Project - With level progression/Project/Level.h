#pragma once
#include <string>
#include <vector>

class PlacableActor;

class Level
{
	char* m_pLevelData;
	int m_height;
	int m_width;

	

public:
	Level();
	~Level();

	std::vector<PlacableActor*> m_pActors;

	bool Load(std::string levelName, int* playerX, int* playerY);
	void Draw();
	void clearSpace(int x, int y);
	PlacableActor* GetCollider(int x, int y);
	void UpdateActor(PlacableActor* actor);

	bool IsSpace(int x, int y);
	bool IsWall(int x, int y);

	int GetHeight() { return m_height; }
	int GetWidth() { return m_width;  }

	static constexpr char WAL = (char)219;

private:
	bool ConvertLevel(int* playerX, int* playerY);
	int GetIndexFromCoordinates(int x, int y);

};