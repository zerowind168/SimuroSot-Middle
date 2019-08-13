#pragma once


class CYPoint :
	public tagPOINT
{
	//
public:
	CYPoint()
	{
		x = y = 0;
	}

	CYPoint(int initX, int initY)
	{
		x = initX;
		y = initY;
	}

	CYPoint(POINT initPt)
	{
		*(POINT*)this = initPt;
	}


	void Offset(int xOffset, int yOffset)
	{
		x += xOffset;
		y += yOffset;
	}
	void Offset(POINT point)
	{
		x += point.x;
		y += point.y;
	}
	void SetPoint(int X, int Y)
	{
		x = X;
		y = Y;
	}
};

class CYRect :
	public tagRECT
{
public:
	CYRect()
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}

	CYRect(int l, int t, int r, int b)
	{
		left = l;
		top = t;
		right = r;
		bottom = b;
	}

	CYRect(const RECT& srcRect) 
	{
		::CopyRect(this, &srcRect);
	}

	CYRect(LPCRECT lpSrcRect) 
	{
		::CopyRect(this, lpSrcRect);
	}

	CYRect(POINT point, SIZE size) 
	{
		right = (left = point.x) + size.cx;
		bottom = (top = point.y) + size.cy;
	}

	CYRect(POINT topLeft, POINT bottomRight) 
	{
		left = topLeft.x;
		top = topLeft.y;
		right = bottomRight.x;
		bottom = bottomRight.y;
	}

	const CYPoint& CYRect::TopLeft() const  
	{
		return *((CYPoint*)this);
	}

	operator LPRECT() 
	{
		return this;
	}
};

class CPlatformOperator
{
public:
	CPlatformOperator(void);
	~CPlatformOperator(void);
	
	static double NAngle(double angle);
	static double Degree2Radian(double angle);
	static double Radian2Degree(double radian);
	HWND GetServerWindow();
	void GetWindowReady();
	void GetBPCPos(int id, int * px, int * py);
	void GetYPCPos(int id, int * px, int * py);
	void GetBPPos(int id, double * px, double * py);
	void GetYPPos(int id, double * px, double * py);
	void GetCP(double resourceX, double resourceY, double destinationX, double destinationY, int * px, int * py);	
	void SetBall(double x, double y);
	void SetRobot(char team, int id, double x, double y, double rotation);
	void LeftClick(int x, int y);
	void LeftClick(CYPoint pos);
	void SetStrategy();
	void SetStart();
	void SetReplay();
	void SetPause();
	void SetStop();
	void SetFreeBall();
	void SetPlaceKick(char team);	
	void SetPenaltyKick(char team);
	void SetGoalKick(char team);
	void SetFreeKick(char team);
	void SetNewgame();
	void CloseServer();

private:
	HWND m_hWnd;
};

