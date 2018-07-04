//  BFSCode.cpp
//  Holds all function code for the BFS class

#include "BFS.h"

//Constructor for the BFS class
BreadthFirstSystem::BreadthFirstSystem()
{

	int Total = (GetGrid_x() * GetGrid_y());

	m_adjacent = new std::list<int>[Total];
	m_path = new int[Total];
	m_distance = new int[Total];

};

//All set and get functions for the private variables within the BFS class
void BreadthFirstSystem::Setpath(int arrayn, int p)
{

	m_path[arrayn] = p;

};

int BreadthFirstSystem::Getpath(int arrayn)
{

	return m_path[arrayn];

};

void BreadthFirstSystem::SetDistance(int arrayn, int d)
{

	m_distance[arrayn] = d;

};

int BreadthFirstSystem::GetDistance(int arrayn)
{

	return m_distance[arrayn];

};

void BreadthFirstSystem::SetAdjacent(int arrayn, int a)
{

	m_adjacent[arrayn].push_back(a);

};

std::list<int>::iterator BreadthFirstSystem::GetAdjacentBegin(int arrayn)
{

	std::list<int>::iterator i;

	i = m_adjacent[arrayn].begin();

	return i;

};

std::list<int>::iterator BreadthFirstSystem::GetAdjacentEnd(int arrayn)
{

	std::list<int>::iterator i;

	i = m_adjacent[arrayn].end();

	return i;

};

//function used to set the edges between nodes
void BreadthFirstSystem::NodeEdge(int a, int b)
{

	m_adjacent[a].push_back(b);

};