// \Nodes class used to help create the grid system for the program
// \author Callum Berger

#ifndef _Nodes_
#define _Nodes_

#include <list>

class Nodes
{
public:
	Nodes();
	~Nodes() {};

	void SetNodeValues(int, int);
	int GetNodeValues(int);

	void SetNode_x(int, int);
	int GetNode_x(int);

	void SetNode_y(int, int);
	int GetNode_y(int);

	void SetClosedNodes(bool, int);
	bool GetClosedNodes(int);

	int GetTotalNodes();
	int GetGrid_x();
	int GetGrid_y();


private:

	int m_totalNodes;
	int m_gridx;
	int m_gridy;
	int *m_nodeValues;
	int *m_nodex;
	int *m_nodey;
	bool *m_closedNodes;

};

#endif //Defines _Nodes_