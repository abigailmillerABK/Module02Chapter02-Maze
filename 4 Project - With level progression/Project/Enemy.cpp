#include "Enemy.h"
#include <iostream>
#include "AudioManager.h"
#include "StateMachineExampleGame.h"
#include "Player.h"

Enemy::Enemy(int x, int y, int deltaX, int deltaY)
	: PlacableActor(x, y)
	, m_currentMovementX(0)
	, m_currentMovementY(0)
	, m_directionX(0)
	, m_directionY(0)
	, m_movementInX(deltaX)
	, m_movementInY(deltaY)
{
	InitDirection();
	doesMove = true;
}

void Enemy::InitDirection()
{
	if (m_movementInX != 0)
	{
		m_directionX = 1;
	}
	if (m_movementInY != 0)
	{
		m_directionY = 1;
	}
}

void Enemy::Draw()
{
	std::cout << (char)153;
}

bool Enemy::CollideWith(PlacableActor* actor) {
	AudioManager::GetInstance()->PlayLoseLivesSound();
	Remove();
	if (actor->GetType() == ActorType::Player) {
		Player* player = dynamic_cast<Player*>(actor);
		player->DecrementLives();
		return true;
	}
	else {
	//switch directions
		m_directionX *= -1;
		m_directionY *= -1;
		return false;
	}
}

void Enemy::Update()
{
	m_currentMovementX = UpdateDirection(m_currentMovementX, m_directionX, m_movementInX);
	m_currentMovementY = UpdateDirection(m_currentMovementY, m_directionY, m_movementInY);
	this->SetPosition(GetNextX(), GetNextY());
}
int Enemy::GetNextX() {
	if (m_movementInX != 0)
	{
		UpdateDirection(m_currentMovementX, m_directionX, m_movementInX);
	}
	return (m_pPosition->x + m_directionX);
}

int Enemy::GetNextY() {
	if (m_movementInY != 0)
	{
		UpdateDirection(m_currentMovementY, m_directionY, m_movementInY);
	}
	return (m_pPosition->y + m_directionY);
}

int Enemy::UpdateDirection(int& current, int& direction, int& movement)
{
	int curPosit = current + direction;
	//current += direction;
	if (std::abs(curPosit) > movement)
	{
		curPosit = movement * direction;
		direction *= -1;
	}
	return curPosit;
}

void Enemy::ChangeDirection() {
	m_directionX *= -1;
	m_directionY *= -1;
}

