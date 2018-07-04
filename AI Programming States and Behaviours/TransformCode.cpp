//  TransformCode.cpp
//  Holds all function code for the Transform class

#include "Transform.h"

//Constructor for the Transform class
Transform::Transform()
{

	m_xPos = 0;
	m_yPos = 0;
	m_initialXPos = 0;
	m_initialYPos = 0;

}

//Deconstructor for the Transform class
Transform::~Transform()
{

}

//All set and get functions for the private variables within the Transform class

void Transform::SetXPos(int x)
{

	m_xPos = x;

}

int Transform::GetXPos()
{

	return m_xPos;

}

void Transform::SetYPos(int y)
{

	m_yPos = y;

}

int Transform::GetYPos()
{

	return m_yPos;

}

void Transform::SetInitialXPos(int x)
{

	m_initialXPos = x;

}

int Transform::GetInitialXPos()
{

	return m_initialXPos;

}

void Transform::SetInitialYPos(int y)
{

	m_initialYPos = y;

}

int Transform::GetInitialYPos()
{

	return m_initialYPos;

}