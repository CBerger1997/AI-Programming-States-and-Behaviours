//  NodesCode.cpp
//  Holds all function code for the Nodes class

#include "Nodes.h"

//Constructor for the Nodes class
Nodes::Nodes()
{

	m_gridx = 47;
	m_gridy = 36;
	m_totalNodes = m_gridx * m_gridy;
	m_closedNodes = new bool[m_totalNodes];
	m_nodeValues = new int[m_totalNodes];
	m_nodex = new int[m_totalNodes];
	m_nodey = new int[m_totalNodes];

};

//All set and get functions for the private variables within the Nodes class
void Nodes::SetNodeValues(int n, int arrayn)
{

	m_nodeValues[arrayn] = n;

};

int Nodes::GetNodeValues(int arrayn)
{

	return m_nodeValues[arrayn];

};

void Nodes::SetNode_x(int x, int arrayn)
{

	m_nodex[arrayn] = x;

};

int Nodes::GetNode_x(int arrayn)
{

	return m_nodex[arrayn];

};

void Nodes::SetNode_y(int y, int arrayn)
{

	m_nodey[arrayn] = y;

};

int Nodes::GetNode_y(int arrayn)
{

	return m_nodey[arrayn];

};

void Nodes::SetClosedNodes(bool c, int arrayn)
{

	m_closedNodes[arrayn] = c;

};

bool Nodes::GetClosedNodes(int arrayn)
{

	return m_closedNodes[arrayn];

};

int Nodes::GetTotalNodes()
{

	return m_totalNodes;

}

int Nodes::GetGrid_x()
{

	return m_gridx;

}

int Nodes::GetGrid_y()
{

	return m_gridy;

}