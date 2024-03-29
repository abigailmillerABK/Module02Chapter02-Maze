#pragma once
#include "GameState.h"
#include "Player.h"
#include "Level.h"

#include <thread>
#include <windows.h>
#include <vector>
#include <string>

class StateMachineExampleGame;

class GameplayState : public GameState
{
	StateMachineExampleGame* m_pOwner;
	
	Player m_player;
	Level* m_pLevel;

	bool m_beatLevel;
	int m_skipFrameCount;
	static constexpr int kFramesToSkip = 2;

	int m_currentLevel;

	std::vector<std::string> m_LevelNames;

public:
	GameplayState(StateMachineExampleGame* pOwner);
	~GameplayState();

	virtual void Enter() override;
	void Exit() override;
	virtual bool Update(bool processInput = true) override;
	void GetInput();
	void Collision();
	bool MoveActor(PlacableActor* actor, int x, int y);
	void LoseGame();
	virtual void Draw() override;

private:
	bool HandleCollision(PlacableActor* actor, int newX, int newY);
	bool Load();
	void DrawHUD(const HANDLE& console);
	std::thread input;
	int inputKey;
	bool shouldGetInput;
};
