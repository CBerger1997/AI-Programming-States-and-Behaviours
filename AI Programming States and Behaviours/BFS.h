// \Class used to create grid system inheriting from the Node Class
// \author Callum Berger

#ifndef _BreadthFirstSystem_
#define _BreadthFirstSystem_

#include <iostream>
#include <list>
#include "Nodes.h"

class BreadthFirstSystem : public Nodes

{

public:

	BreadthFirstSystem();
	~BreadthFirstSystem() {};

	void NodeEdge(int, int);

	void Setpath(int, int);
	int Getpath(int);

	void SetDistance(int, int);
	int GetDistance(int);

	void SetAdjacent(int, int);
	std::list<int>::iterator GetAdjacentBegin(int);
	std::list<int>::iterator GetAdjacentEnd(int);

private:

	std::list<int> *m_adjacent;
	int *m_path;
	int *m_distance;

};

#endif //Defines _BreadthFirstSystem_