#include "GameplayState.h"

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <assert.h>

#include "Box.h"
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Money.h"
#include "Goal.h"
#include "AudioManager.h"
#include "Utility.h"
#include "StateMachineExampleGame.h"
#include <list>

using namespace std;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kEscapeKey = 27;

GameplayState::GameplayState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
	, m_beatLevel(false)
	, m_skipFrameCount(0)
	, m_currentLevel(0)
	, m_pLevel(nullptr)
{
	m_LevelNames.push_back("Level1.txt");
	m_LevelNames.push_back("Level2.txt");
	m_LevelNames.push_back("Level3.txt");
}

GameplayState::~GameplayState()
{
	delete m_pLevel;
	m_pLevel = nullptr;
}

bool GameplayState::Load()
{
	if (m_pLevel)
	{
		delete m_pLevel;
		m_pLevel = nullptr;
	}

	m_pLevel = new Level();
	
	return m_pLevel->Load(m_LevelNames.at(m_currentLevel), m_player.GetXPositionPointer(), m_player.GetYPositionPointer());

}

void GameplayState::Enter()
{
	Load();
}

bool GameplayState::Update(bool processInput)
{
	if (processInput && !m_beatLevel)
	{
		int input = _getch();
		int arrowInput = 0;
		int newPlayerX = m_player.GetXPosition();
		int newPlayerY = m_player.GetYPosition();

		// One of the arrow keys were pressed
		if (input == kArrowInput)
		{
			arrowInput = _getch();
		}

		if ((input == kArrowInput && arrowInput == kLeftArrow) ||
			(char)input == 'A' || (char)input == 'a')
		{
			newPlayerX--;
		}
		else if ((input == kArrowInput && arrowInput == kRightArrow) ||
			(char)input == 'D' || (char)input == 'd')
		{
			newPlayerX++;
		}
		else if ((input == kArrowInput && arrowInput == kUpArrow) ||
			(char)input == 'W' || (char)input == 'w')
		{
			newPlayerY--;
		}
		else if ((input == kArrowInput && arrowInput == kDownArrow) ||
			(char)input == 'S' || (char)input == 's')
		{
			newPlayerY++;
		}
		else if (input == kEscapeKey)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
		}
		else if ((char)input == 'Z' || (char)input == 'z')
		{
			m_player.DropKey();
		}

		// If position never changed
		if (newPlayerX == m_player.GetXPosition() && newPlayerY == m_player.GetYPosition())
		{
			//return false;
		}
		else
		{
			HandleCollision(&m_player, newPlayerX, newPlayerY);
			for (PlacableActor* thisActor : m_pLevel->m_pActors) {
				if (thisActor->GetType() == ActorType::Enemy) {
					Enemy* enemy = dynamic_cast<Enemy*>(thisActor);
					if (HandleCollision(enemy, enemy->GetNextX(), enemy->GetNextY())) {
						//m_pLevel->UpdateActor(enemy);
					}
					else {
						//enemy->ChangeDirection();
					}
				}
				else {
					m_pLevel->UpdateActor(thisActor);
				}
			}
			
		}
	}
	if (m_beatLevel)
	{
		++m_skipFrameCount;
		if (m_skipFrameCount > kFramesToSkip)
		{
			m_beatLevel = false;
			m_skipFrameCount = 0;
			++m_currentLevel;
			if (m_currentLevel == m_LevelNames.size())
			{
				Utility::WriteHighScore(m_player.GetMoney());

				AudioManager::GetInstance()->PlayWinSound();
				
				m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Win);
			}
			else
			{
				// On to the next level
				Load();
			}

		}
	}

	return false;
}

bool GameplayState::MoveActor(PlacableActor* actor, int x, int y) {
	m_pLevel->clearSpace(x, y);
	actor->SetPosition(x, y);
	return true;
}

void GameplayState::LoseGame() {
	AudioManager::GetInstance()->PlayLoseSound();
	m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Lose);
}

bool GameplayState::HandleCollision(PlacableActor* actor, int newX, int newY)
{
	PlacableActor* collidedActor = m_pLevel->GetCollider(newX, newY);
	if (collidedActor != nullptr && collidedActor->IsActive())
	{
		switch (collidedActor->GetType())
		{
		case ActorType::Enemy:
		{
			Enemy* collidedEnemy = dynamic_cast<Enemy*>(collidedActor);
			assert(collidedEnemy);
			if (collidedEnemy->CollideWith(actor)) {
				if (m_player.GetLives() < 0)
				{
					LoseGame();
				}
				return MoveActor(actor, newX, newY);
			}
			return false;
			break;
		}
		case ActorType::Money:
		{
			Money* collidedMoney = dynamic_cast<Money*>(collidedActor);
			assert(collidedMoney);
			if (collidedMoney->CollideWith(actor)) {
				return MoveActor(actor, newX, newY);
			}
			break;
		}
		case ActorType::Key:
		{
			Key* collidedKey = dynamic_cast<Key*>(collidedActor);
			assert(collidedKey);
			if (!m_player.HasKey())
			{
				if (collidedKey->CollideWith(actor)) {
					return MoveActor(actor, newX, newY);
				}
			}
			break;
		}
		case ActorType::Door:
		{
			Door* collidedDoor = dynamic_cast<Door*>(collidedActor);
			assert(collidedDoor);
			if (!collidedDoor->IsOpen())
			{
				if (collidedDoor->CollideWith(actor)) {
					return MoveActor(actor, newX, newY);
				}
				else {
					return false;
				}
			}
			else
			{
				return MoveActor(actor, newX, newY);
			}
			break;
		}
		case ActorType::Box:
		{
			Box* collidedBox = dynamic_cast<Box*>(collidedActor);
			assert(collidedBox);
			collidedBox->CollideWith(actor);
			int difX = newX - m_player.GetXPosition();
			int difY = newY - m_player.GetYPosition();
			int newBoxX = collidedBox->GetXPosition() + difX;
			int newBoxY = collidedBox->GetYPosition() + difY;
			//collidedActor = m_pLevel->UpdateActors(newBoxX, newBoxY);
			if (HandleCollision(collidedBox, newBoxX, newBoxY)) { //If there is an empty space
				MoveActor(collidedBox, newBoxX, newBoxY);
				return MoveActor(actor, newX, newY);
			}
			else if (collidedActor != nullptr && collidedActor->IsActive()) {
				return false;
			}
			break;
		}
		case ActorType::Goal:
		{
			Goal* collidedGoal = dynamic_cast<Goal*>(collidedActor);
			assert(collidedGoal);
			collidedGoal->Remove();
			m_beatLevel = true;
			return MoveActor(actor, newX, newY);
			break;
		}
		default:
			break;
		}
	}
	else if (m_pLevel->IsSpace(newX, newY)) // no collision
	{
		return MoveActor(actor, newX, newY);
	}
	else if (m_pLevel->IsWall(newX, newY))
	{
		return false;
	}
}

void GameplayState::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	m_pLevel->Draw();

	// Set cursor position for player 
	COORD actorCursorPosition;
	actorCursorPosition.X = m_player.GetXPosition();
	actorCursorPosition.Y = m_player.GetYPosition();
	SetConsoleCursorPosition(console, actorCursorPosition);
	m_player.Draw();

	// Set the cursor to the end of the level
	COORD currentCursorPosition;
	currentCursorPosition.X = 0;
	currentCursorPosition.Y = m_pLevel->GetHeight();
	SetConsoleCursorPosition(console, currentCursorPosition);

	DrawHUD(console);
}

void GameplayState::DrawHUD(const HANDLE& console)
{
	cout << endl;

	// Top Border
	for (int i = 0; i < m_pLevel->GetWidth(); ++i)
	{
		cout << Level::WAL;
	}
	cout << endl;

	// Left Side border
	cout << Level::WAL;

	cout << " wasd-move " << Level::WAL << " z-drop key " << Level::WAL;

	cout << " $:" << m_player.GetMoney() << " " << Level::WAL;
	cout << " lives:" << m_player.GetLives() << " " << Level::WAL;
	cout << " key:";
	if (m_player.HasKey())
	{
		m_player.GetKey()->Draw();
	}
	else
	{
		cout << " ";
	}

	// RightSide border
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);

	COORD pos;
	pos.X = m_pLevel->GetWidth() - 1;
	pos.Y = csbi.dwCursorPosition.Y;
	SetConsoleCursorPosition(console, pos);

	cout << Level::WAL;
	cout << endl;

	// Bottom Border
	for (int i = 0; i < m_pLevel->GetWidth(); ++i)
	{
		cout << Level::WAL;
	}
	cout << endl;
}