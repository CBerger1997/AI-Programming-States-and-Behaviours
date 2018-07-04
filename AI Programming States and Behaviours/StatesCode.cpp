//  StatesCode.cpp
//  Holds all function code for the States class

#include "States.h"
#include <list>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

//Constructor for the States Class
States::States()
{
	m_xDestination = 0;
	m_yDestination = 0;
	m_fleeingCount = 0;
}

//Deconstructor for the States Class
States::~States()
{

}

//Function which chooses a random direction from availbale directions in which an Enemy can move
int States::ChooseDirection(Enemy e, BreadthFirstSystem grid)
{
	int moveDir = 0;
	bool enemyUp = false;
	bool enemyDown = false;
	bool enemyLeft = false;
	bool enemyRight = false;
	
	std::list<int>::iterator i;

	int startingNode;
	int count = 0;

	//int variable, sets m_EndingNode
	if (e.GetXPos() == 0 && e.GetXPos() == 0)
	{
		startingNode = 0;
	}
	else if (e.GetYPos() == 0)
	{
		startingNode = (e.GetXPos() / 20);
	}
	else
	{
		startingNode = ((e.GetXPos() / 20) + ((e.GetYPos() / 20) * grid.GetGrid_x()));
	};

	for (i = grid.GetAdjacentBegin(startingNode); i != grid.GetAdjacentEnd(startingNode); ++i)
	{
		//checks adjacent nodes to see if they are available for the direction of the Enemy Object
		if (grid.GetClosedNodes(*i) == false)
		{
			if (count == 0)
			{
				enemyUp = true;
			}
			else if (count == 1)
			{
				enemyRight = true;
			}
			else if (count == 2)
			{
				enemyDown = true;
			}
			else if (count == 3)
			{
				enemyLeft = true;
			}
		};
		count++;
	};

	bool dirfound = false;
	int enemyDir = 0;

	std::vector<int> randVector;

	for (int i = 1; i < 5; i++)
	{
		randVector.push_back(i);
	}

	srand(time(NULL));
	std::random_shuffle(randVector.begin(), randVector.end());

	for (std::vector<int>::iterator i = randVector.begin(); i != randVector.end(); ++i)
	{
		if ( *i == 1 && enemyUp == true && e.GetEnemyDirection() != 3)
		{
			enemyDir = 1;
			dirfound = true;
			break;
		}
		else if (*i == 2 && enemyRight == true && e.GetEnemyDirection() != 4)
		{
			enemyDir = 2;
			dirfound = true;
			break;
		}
		else if (*i == 3 && enemyDown == true && e.GetEnemyDirection() != 1)
		{
			enemyDir = 3;
			dirfound = true;
			break;
		}
		else if (*i == 4 && enemyLeft == true && e.GetEnemyDirection() != 2)
		{
			enemyDir = 4;
			dirfound = true;
			break;
		}
	}


	moveDir = enemyDir;

	return moveDir;
}

//Function which makes an Enemy move in the direciton specified by the ChooseDirection
Enemy States::MoveRoamingEnemy(Enemy e, BreadthFirstSystem grid, int direction)
{
	if (direction == 1)
	{
		e.SetYPos(e.GetYPos() - 20);
	}
	else if (direction == 2)
	{
		e.SetXPos(e.GetXPos() + 20);
	}
	else if (direction == 3)
	{
		e.SetYPos(e.GetYPos() + 20);
	}
	else if (direction == 4)
	{
		e.SetXPos(e.GetXPos() - 20);
	}

	return e;
}

//Function using a Breadth First Search in order to locate the Player
void States::EnemyToPlayerSearch(BreadthFirstSystem grid, Enemy e, Player p1)
{
	//List variables, creates queue and iterator
	std::list<int> openQueue;
	std::list<int>::iterator i;

	//Bool variables, checks for closed nodes and whether the end node has been found
	bool exit = false;

	int startingNode;
	int endingNode;

	//int variable, sets m_StartingNode
	if (e.GetXPos() == 0 && e.GetXPos() == 0)
	{
		startingNode = 0;
	}
	else if (e.GetYPos() == 0)
	{
		startingNode = (e.GetXPos() / 20);
	}
	else
	{
		startingNode = ((e.GetXPos() / 20) + ((e.GetYPos() / 20) * grid.GetGrid_x()));
	};

	//int variable, sets m_EndingNode
	if (p1.GetXPos() == 0 && p1.GetXPos() == 0)
	{
		endingNode = 0;
	}
	else if (p1.GetYPos() == 0)
	{
		endingNode = (p1.GetXPos() / 20);
	}
	else
	{
		endingNode = ((p1.GetXPos() / 20) + ((p1.GetYPos() / 20) * grid.GetGrid_x()));
	};


	//for loop, sets all nodes to Open and all m_Distance except start node to above the total node m_count
	for (int i = 0; i < grid.GetTotalNodes(); i++)
	{
		if (i == startingNode)
		{
			grid.SetDistance(i, 0);
		}
		else
		{
			grid.SetDistance(i, (grid.GetTotalNodes() + 1));
		};
	};

	//sets the start node to closed and adds the start node value to the end of BFSQueue
	grid.SetClosedNodes(true, startingNode);
	openQueue.push_back(startingNode);

	//While loop, loops while the m_OpenQueue is not empty
	while (openQueue.empty() == false)
	{
		int searchNode = startingNode;

		searchNode = openQueue.front();
		openQueue.pop_front();

		//Gets all adjacent vertices to StartNode
		for (i = grid.GetAdjacentBegin(searchNode); i != grid.GetAdjacentEnd(searchNode); ++i)
		{
			//marks adjacent node as closed if it is open, then adds node value to the back of queue
			if (grid.GetClosedNodes(*i) == false)
			{
				if (*i == endingNode)
				{
					grid.SetClosedNodes(false, *i);
				}
				else
				{
					grid.SetClosedNodes(true, *i);
				}
				openQueue.push_back(*i);
				grid.SetDistance(*i, (grid.GetDistance(searchNode) + 1));
			};
			//Checks node to see if it is the end node or not, breaks loop if end node is found
			if (searchNode == endingNode)
			{
				exit = true;
			};
		};
		if (exit == true)
		{
			break;
		};
	};
	if (exit == false)
	{
		std::cout << "Error, Player cannot be reached" << std::endl;
	};

	for (int i = 0; i < grid.GetTotalNodes(); i++)
	{
		if (grid.GetNodeValues(i) == 1)
		{
			grid.SetClosedNodes(true, i);
		}
		else if (grid.GetNodeValues(i) == 0)
		{
			grid.SetClosedNodes(false, i);
		}
	}
};

//Function used to find the shortest distance between the player and the enemy
int States::ShortestSearchPath(BreadthFirstSystem grid, Enemy e, Player p1)
{
	//variables used to calculate the shortest path between the start and end node
	int startingNode;
	int searchNode;
	int endNode;
	int closeDistance[4];
	int count = 0;
	int pathCount = 1;
	bool startNodeFound = false;
	int tile[4];
	std::list<int>::iterator i;

	//int variable, sets m_StartingNode
	if (e.GetXPos() == 0 && e.GetXPos() == 0)
	{
		startingNode = 0;
	}
	else if (e.GetYPos() == 0)
	{
		startingNode = (e.GetXPos() / 20);
	}
	else
	{
		startingNode = ((e.GetXPos() / 20) + ((e.GetYPos() / 20) * grid.GetGrid_x()));
	};

	//int variable, sets m_SearchNode
	if (p1.GetXPos() == 0 && p1.GetXPos() == 0)
	{
		searchNode = 0;
	}
	else if (p1.GetYPos() == 0)
	{
		searchNode = (p1.GetXPos() / 20);
	}
	else
	{
		searchNode = ((p1.GetXPos() / 20) + ((p1.GetYPos() / 20) * grid.GetGrid_x()));
	}

	endNode = searchNode;

	//while loop, finds the shortest path from the end node to the start node, breaking once the start node is found
	while (!startNodeFound)
	{
		//resets m_count to 0
		count = 0;

		//resets the Closedm_Distance array to 0 for all values
		for (int i = 0; i < 4; i++)
		{
			closeDistance[i] = 0;
		};

		//for loop, checks adjacent nodes to current m_SearchNode, storing their m_Distance and m_Tile number in the m_Closem_Distance and m_Tile arrays
		for (i = grid.GetAdjacentBegin(searchNode); i != grid.GetAdjacentEnd(searchNode); ++i)
		{
			closeDistance[count] = grid.GetDistance(*i);
			tile[count] = *i;
			count = count + 1;
			//checks to see whether the m_StartingNode has been found, breaking the for loop if it has
			if (*i == startingNode)
			{
				startNodeFound = true;
				break;
			};
		};

		//variable used to store the adjacent node with the shortest or joint shortest m_Distance
		int shortestDist;

		//sets the m_shortestDist variable equal to the first adjacent nodes m_Distance and sets the next m_SearchNode to the first adjacent node in case the first adjacent node has the shortest m_Distance
		shortestDist = closeDistance[0];
		searchNode = tile[0];

		//for loop, used to check which of the Closedm_Distance values is the smallest or joint smallest and then sets the smallest m_Distance node as the next m_SearchNode
		for (int i = 1; i < count; i++)
		{
			//if statement, checks to see if the next adjacent node has a shorter m_Distance than the current shortest m_Distance, replacing the current shortest m_Distance and m_SearchNode if true
			if (closeDistance[i] < shortestDist)
			{
				shortestDist = closeDistance[i];
				searchNode = tile[i];
			}


		};
		//Stores the Node of each shortest m_Distance in the m_path variable in the BreadthFirstSystem class, creating the shortest path and printing it
		
		grid.Setpath(0, endNode);

		if (searchNode != startingNode && searchNode != endNode)
		{
			grid.Setpath(pathCount, searchNode);
			pathCount++;
		};
	};

	return pathCount;
};

//Function used to move the enemy closer to the player
Enemy States::ChasePlayer(BreadthFirstSystem grid, Enemy e, int distance)
{
	int nextNode;
	int nextNodeX;
	int nextNodeY;

	nextNode = grid.Getpath(distance - 1);

	nextNodeX = nextNode % grid.GetGrid_x();

	nextNodeY = ((nextNode - nextNodeX) / grid.GetGrid_x()) * 20;

	nextNodeX *= 20;

	e.SetXPos(nextNodeX);
	e.SetYPos(nextNodeY);

	return e;
}

//Function used to reset the FleeingCount variable
void States::ResetFleeingCount()
{
	m_fleeingCount = 0;
}

//Function used to increment the FleeingCount variable by 1
void States::IncrementFleeingCount()
{
	m_fleeingCount++;
}

//Function used to the get the value of the FleeingCount variable
int States::GetFleeingcount()
{
	return m_fleeingCount;
}