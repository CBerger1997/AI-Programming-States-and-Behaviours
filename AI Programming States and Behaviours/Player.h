// \Player class used to act as the moveable character for the user
// \author Callum Berger

#ifndef _Player_
#define _Player_

#include "Transform.h"
#include "BFS.h"

class Player : public Transform
{
public:
	Player();
	~Player();

	bool PlayerLocalCollisionCheck(BreadthFirstSystem, Player, int);

	Player SetPlayerPosition(Player);

	void SetLives(int);
	int GetLives();

	void SetScore(int);
	int GetScore();

private:

	int m_lives;
	int m_score;
};

#endif //Defines _Player_