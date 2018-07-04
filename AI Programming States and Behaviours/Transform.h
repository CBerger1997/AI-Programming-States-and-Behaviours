// \Transform class inherited by both the player and enemy class storing positions variables
// \author Callum Berger

#ifndef _Transform_
#define _Transform_

class Transform
{
public:
	Transform();
	~Transform();

	void SetXPos(int x);
	int GetXPos();

	void SetYPos(int y);
	int GetYPos();

	void SetInitialXPos(int x);
	int GetInitialXPos();

	void SetInitialYPos(int y);
	int GetInitialYPos();

private:
	int m_xPos;
	int m_yPos;
	int m_initialXPos;
	int m_initialYPos;
};

#endif //Defines _Transform_