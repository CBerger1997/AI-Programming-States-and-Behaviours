//  PlayerCode.cpp
//  Holds all function code for the Player class

#include "Player.h"

//Constructor for the Player class
Player::Player()
{

	SetXPos(460);
	SetYPos(400);
	SetInitialXPos(460);
	SetInitialYPos(400);
	m_lives = 3;
	m_score = 0;

}

//Deconstructor for the Player class
Player::~Player()
{

}

//Function which searches all adjacent nodes to the player to check whether it can move in the desired direction passed through as a parameter
bool Player::PlayerLocalCollisionCheck(BreadthFirstSystem grid, Player p1, int direction)
{

	std::list<int>::iterator i;

	int startingNode;
	int count = 1;
	bool move = true;

	//int variable, sets m_EndingNode
	if (p1.GetXPos() == 0 && p1.GetXPos() == 0)

	{

		startingNode = 0;

	}
	else if (p1.GetYPos() == 0)

	{

		startingNode = (p1.GetXPos() / 20);

	}

	else

	{

		startingNode = ((p1.GetXPos() / 20) + ((p1.GetYPos() / 20) * grid.GetGrid_x()));

	};

	for (i = grid.GetAdjacentBegin(startingNode); i != grid.GetAdjacentEnd(startingNode); ++i)
	
	{
	
		//marks adjacent node as closed if it is open, then adds node value to the back of queue
		
		if (grid.GetClosedNodes(*i) == true && count == direction)
		
		{
			
			if (direction == 1)
			
			{
			
				move = false;
			
			}
			
			else if (direction == 2)
			
			{
			
				move = false;
			
			}
			
			else if (direction == 3)
			
			{
			
				move = false;
			
			}
			
			else if (direction == 4)
			
			{
			
				move = false;
			
			}
		
		};
		
		count++;
	
	};

	return move;

}

//Function used to set the Players position to it's initial start position
Player Player::SetPlayerPosition(Player p)
{

	p.SetXPos(p.GetInitialXPos());
	p.SetYPos(p.GetInitialYPos());

	return p;

}

//All set and get functions for the private variables within the Nodes class
void Player::SetLives(int l)
{

	m_lives = l;

};

int Player::GetLives()
{

	return m_lives;

};

void Player::SetScore(int s)
{

	m_score = s;

};

int Player::GetScore()
{

	return m_score;

};