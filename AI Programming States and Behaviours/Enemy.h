// \Enemy class used to create the AI for the program
// \author Callum Berger

#ifndef _Enemy_
#define _Enemy_

#include "Transform.h"

class Enemy : public Transform
{
public:
	Enemy();
	~Enemy();

	void SetEnemyState(int);
	int GetEnemyState();

	void SetEnemyDirection(int);
	int GetEnemyDirection();

	void SetState(int);
	int GetState();

	Enemy SetEnemyPositions(Enemy, int);
	Enemy SetInitialPositions(Enemy, int);

private:
	int m_state;
	int m_direction;
	int m_currentState;
};

#endif //Defines _Enemy_
