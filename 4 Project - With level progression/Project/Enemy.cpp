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

	if (actor->GetType() == ActorType::Player) {
		AudioManager::GetInstance()->PlayLoseLivesSound();
		Remove();
		Player* player = dynamic_cast<Player*>(actor);
		player->DecrementLives();
		return true;
	}
}

void Enemy::Update()
{
	//m_currentMovementX = UpdateDirection(m_currentMovementX, m_directionX, m_movementInX);
	//m_currentMovementY = UpdateDirection(m_currentMovementY, m_directionY, m_movementInY);
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
	current += direction;

	if (std::abs(current) > movement)
	{
		current = movement * direction;
		direction *= -1;
	}

	return current;
}

void Enemy::ChangeDirection() {
	m_currentMovementX = m_movementInX;
	m_currentMovementY = m_movementInY;
}

