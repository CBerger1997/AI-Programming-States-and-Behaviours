// \States class used to create the behaviour for the enemy objects
// \author Callum Berger

#ifndef _States_
#define _States_

#include "BFS.h"
#include "Enemy.h"
#include "Player.h"

class States
{
public:
	States();
	~States();

	int ChooseDirection(Enemy, BreadthFirstSystem);
	Enemy MoveRoamingEnemy(Enemy, BreadthFirstSystem, int);

	void EnemyToPlayerSearch(BreadthFirstSystem, Enemy, Player);
	int ShortestSearchPath(BreadthFirstSystem, Enemy, Player);
	Enemy ChasePlayer(BreadthFirstSystem, Enemy, int);

	void ResetFleeingCount();
	void IncrementFleeingCount();
	int GetFleeingcount();

private:
	int m_xDestination;
	int m_yDestination;
	int m_fleeingCount;
};

#endif //Defines _States_