//  EnemyCode.cpp
//  Holds all function code for the enemy class

#include "Enemy.h"

//Constructor for the Enemy class
Enemy::Enemy()
{

	SetXPos(20);
	SetYPos(20);
	SetInitialXPos(20);
	SetInitialYPos(20);
	m_currentState = 1;

};

//Deconstructor for the Enemy class
Enemy::~Enemy()
{

};

//All set and get functions for the private variables within the Enemy class
void Enemy::SetEnemyState(int s)
{

	m_state = s;

}

int Enemy::GetEnemyState()
{

	return m_state;

}

void Enemy::SetEnemyDirection(int d)
{

	m_direction = d;

}

int Enemy::GetEnemyDirection()
{

	return m_direction;

}

void Enemy::SetState(int s)
{

	m_currentState = s;

}

int Enemy::GetState()
{

	return m_currentState;

}

//Function used to set the initial positions of the enemy object passed through as a parameter
Enemy Enemy::SetInitialPositions(Enemy e, int enemyNum)
{

	if (enemyNum == 0)

	{

		e.SetInitialXPos(20);
		e.SetInitialYPos(20);

	}

	else if (enemyNum == 1)

	{

		e.SetInitialXPos(900);
		e.SetInitialYPos(20);

	}

	else if (enemyNum == 2)

	{

		e.SetInitialXPos(20);
		e.SetInitialYPos(680);

	}

	else if (enemyNum == 3)

	{

		e.SetInitialXPos(900);
		e.SetInitialYPos(680);

	}

	return e;

}

//Function used to set the current poisitions of the enemy to the initial positions of the enemy object passed through as a parameter
Enemy Enemy::SetEnemyPositions(Enemy e, int enemyNum)

{

	if (enemyNum == 0)

	{

		e.SetXPos(e.GetInitialXPos());
		e.SetYPos(e.GetInitialYPos());

	}

	else if (enemyNum == 1)

	{

		e.SetXPos(e.GetInitialXPos());
		e.SetYPos(e.GetInitialYPos());

	}

	else if (enemyNum == 2)

	{

		e.SetXPos(e.GetInitialXPos());
		e.SetYPos(e.GetInitialYPos());

	}

	else if (enemyNum == 3)

	{

		e.SetXPos(e.GetInitialXPos());
		e.SetYPos(e.GetInitialYPos());

	}

	return e;

}