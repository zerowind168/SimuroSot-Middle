#include "StdAfx.h"
#include "PlatformOperator.h"

const double PI = 3.14159265357989;

CPlatformOperator::CPlatformOperator(void)
{
	m_hWnd = ::FindWindow("ImlWinCls", "WorldModel");
}


CPlatformOperator::~CPlatformOperator(void)
{
}


double CPlatformOperator::NAngle(double angle)
{
	while (angle > 180.0) 
	{
		angle -= 360.0;		
	}

	while (angle < -180.0)
	{
		angle += 360.0;
	}

	if (angle == -180.0)
	{
		angle = 180.0;
	}

	return angle;
}


double CPlatformOperator::Degree2Radian(double angle)
{
	return (angle * PI / 180);
}	//end Degree2Radian();


double CPlatformOperator::Radian2Degree(double radian)
{
	return (180 / PI * radian);
}	//end Degree2Radian();


HWND CPlatformOperator::GetServerWindow()
{
	HWND hWnd;
	
	return hWnd;
}

void CPlatformOperator::GetWindowReady( )
{
	if (!m_hWnd)
	{
		m_hWnd = ::FindWindow("ImlWinCls", "WorldModel");
	}

	if (!m_hWnd)	exit(1);

	if (::IsIconic(m_hWnd))
	{
		::ShowWindow(m_hWnd, SW_RESTORE);
	}
	::ShowWindow(m_hWnd, SW_SHOWNORMAL);
	::SetForegroundWindow(m_hWnd);
	::SetFocus(m_hWnd);
}


void CPlatformOperator::GetBPCPos(int id, int * px, int * py)
{
	static int x[] = {600, 546, 540, 412, 407};
	static int y[] = {276, 403, 158, 403, 157};

	*px = x[id] - 6;
	*py = y[id] - 6;
}


void CPlatformOperator::GetYPCPos(int id, int * px, int * py)
{
	static int x[] = {76, 136, 135, 264, 267};
	static int y[] = {276, 158, 404, 158, 404};

	*px = x[id] - 6;
	*py = y[id] - 6;
}


void CPlatformOperator::GetBPPos(int id, double * px, double * py)
{
	static double x[] = {212.5, 191.2, 189.2, 139.8, 138.8};
	static double y[] = {91.0, 42.0, 137.5, 42.6, 137.1};

	*px = x[id];
	*py = y[id];
}


void CPlatformOperator::GetYPPos(int id, double * px, double * py)
{
	static double x[] = {9.8, 33.3, 32.9, 82.9, 84.0};
	static double y[] = {91.3, 137.1, 42.2, 137.0, 42.5};

	*px = x[id];
	*py = y[id];
}


void CPlatformOperator::GetCP(double resourceX, double resourceY, double destinationX, double destinationY, int * px, int * py)
{
	const double dXRatio = 1.0 / 0.3880;   
	const double dYRatio = 1.0 / 0.3860;   	

	double diffX, diffY;
	diffX = destinationX - resourceX;
	diffY = destinationY - resourceY;

	*px = diffX * dXRatio;
	*py = -diffY * dYRatio;
}


void CPlatformOperator::SetBall(double x, double y)
{
	GetWindowReady( );
	CYRect rect;
	::GetWindowRect(m_hWnd, rect);
	CYPoint pos = rect.TopLeft();
	int nX = 328, nY = 270; 

	pos.Offset(nX, nY);
	SetCursorPos(pos.x, pos.y);
	int mX = 0, mY = 0;
	GetCP(110.0, 90.0, x, y, &mX, &mY);
	pos.Offset(mX, mY);
	mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_ABSOLUTE, 0, 0, 0, 0); 
	SleepEx(50, TRUE);
	mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_ABSOLUTE, 0, 0, 0, 0);
	SleepEx(100, TRUE);
	mouse_event(MOUSEEVENTF_MOVE, mX, mY, 0, 0);		
	SetCursorPos(pos.x, pos.y);
	SleepEx(100, TRUE);
	mouse_event(MOUSEEVENTF_LEFTUP|MOUSEEVENTF_ABSOLUTE, 0, 0, 0, 0);
	SleepEx(100, TRUE);
}


void CPlatformOperator::SetRobot(char team, int id, double x, double y, double rotation)
{
	GetWindowReady( );
	int nx,ny;
	if (team == 'B' || team == 'b')
	{		
		GetBPCPos(id, &nx, &ny);		
	}
	else
	{		
		GetYPCPos(id, &nx, &ny);		
	}

	CYRect rect;
	::GetWindowRect(m_hWnd, rect);
	CYPoint pos = rect.TopLeft();
	pos.Offset(nx, ny);
	SetCursorPos(pos.x, pos.y);		
	mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_ABSOLUTE, 0, 0, 0, 0); 
	SleepEx(50, TRUE);
	mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_ABSOLUTE, 0, 0, 0, 0);
	SleepEx(100, TRUE);
	int pX = 0, pY = 0;
	double dRobotX = 0, dRobotY = 0;
	if (team == 'B' || team == 'b')
	{		GetBPPos(id, &dRobotX, &dRobotY);		}
	else
	{		GetYPPos(id, &dRobotX, &dRobotY);	}

	GetCP(dRobotX, dRobotY, x, y, &pX, &pY);
	pos.Offset(pX, pY);
	mouse_event(MOUSEEVENTF_MOVE, pX, pY, 0, 0);		
	SetCursorPos(pos.x, pos.y);
	SleepEx(500, TRUE);
	mouse_event(MOUSEEVENTF_LEFTUP|MOUSEEVENTF_ABSOLUTE, 0, 0, 0, 0);
	SleepEx(500, TRUE);	
	rotation = NAngle(rotation);
	int theta = 0;

	if (team == 'B')
	{		
		theta = (id == 0) ? (-90-rotation) : (180.0 - rotation);	
	}
	else
	{		
		theta = (id == 0) ? (90-rotation) : (0.0 - rotation);		
	}

	NAngle(theta);     
	int n = theta * 50.0 / 3.0;   
	if (theta >= 0)
	{
		keybd_event(VK_RIGHT, MapVirtualKey(VK_RIGHT,0), 0, 0);
		SleepEx(n, TRUE);	
		keybd_event(VK_RIGHT, MapVirtualKey(VK_RIGHT,0), KEYEVENTF_KEYUP, 0);
	}
	else
	{
		keybd_event(VK_LEFT, MapVirtualKey(VK_LEFT,0), 0, 0);
		SleepEx(-n, TRUE);	
		keybd_event(VK_LEFT, MapVirtualKey(VK_LEFT,0), KEYEVENTF_KEYUP, 0);
	}
	SleepEx(500, TRUE);	
}


void CPlatformOperator::SetStrategy()
{
	GetWindowReady();
	CYRect rect;
	::GetWindowRect(m_hWnd, rect);
	CYPoint pos;
	pos.x = rect.left;
	pos.y = rect.top;	
	SetCursorPos(pos.x + 720, pos.y + 80);
	mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_ABSOLUTE,0,0,0,0);  
	SleepEx(40, TRUE);	
	mouse_event(MOUSEEVENTF_LEFTUP|MOUSEEVENTF_ABSOLUTE,0,0,0,0);
	SetCursorPos(pos.x + 720, pos.y + 80);
	SleepEx(40, TRUE);	
	mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_ABSOLUTE,0,0,0,0);  
	SleepEx(40, TRUE);	
	mouse_event(MOUSEEVENTF_LEFTUP|MOUSEEVENTF_ABSOLUTE,0,0,0,0);
	SleepEx(100, TRUE);
	SetCursorPos(pos.x + 770, pos.y + 105);
	SleepEx(40, TRUE);	
	mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_ABSOLUTE,0,0,0,0);  
	SleepEx(40, TRUE);	
	mouse_event(MOUSEEVENTF_LEFTUP|MOUSEEVENTF_ABSOLUTE,0,0,0,0);
	SleepEx(100, TRUE);
	SetCursorPos(pos.x + 770, pos.y + 166);
	SleepEx(40, TRUE);	
	mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_ABSOLUTE,0,0,0,0);  
	SleepEx(40, TRUE);	
	mouse_event(MOUSEEVENTF_LEFTUP|MOUSEEVENTF_ABSOLUTE,0,0,0,0);
	SleepEx(100, TRUE);
	SetCursorPos(pos.x + 712, pos.y + 220);
	SleepEx(40, TRUE);	
	mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_ABSOLUTE,0,0,0,0);  
	SleepEx(40, TRUE);	
	mouse_event(MOUSEEVENTF_LEFTUP|MOUSEEVENTF_ABSOLUTE,0,0,0,0);
	SleepEx(100, TRUE);
}


void CPlatformOperator::LeftClick( int x, int y )
{
	GetWindowReady();
	CYRect rect;
	::GetWindowRect(m_hWnd, rect);
	CYPoint pos;
	pos.x = rect.left;
	pos.y = rect.top;	

	SetCursorPos(pos.x + x, pos.y + y);
	mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_ABSOLUTE,0,0,0,0);  
	SleepEx(50, TRUE);	
	mouse_event(MOUSEEVENTF_LEFTUP|MOUSEEVENTF_ABSOLUTE,0,0,0,0);
	SetCursorPos(pos.x + x, pos.y + y);
	SleepEx(50, TRUE);	
	mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_ABSOLUTE,0,0,0,0);  
	SleepEx(50, TRUE);	
	mouse_event(MOUSEEVENTF_LEFTUP|MOUSEEVENTF_ABSOLUTE,0,0,0,0);
}


void CPlatformOperator::LeftClick( CYPoint pos )
{
	LeftClick(pos.x, pos.y);
}


void CPlatformOperator::SetStart()
{
	LeftClick(720, 298);
	SleepEx(1000, TRUE);
}

void CPlatformOperator::SetReplay()
{
	LeftClick(325, 605);
	SleepEx(1000, TRUE);
}

void CPlatformOperator::SetPause()
{
	LeftClick(405, 605);
	SleepEx(1000, TRUE);
}


void CPlatformOperator::SetStop()
{
	LeftClick(490, 605);
	SleepEx(2000, TRUE);
}


void CPlatformOperator::SetFreeBall()
{
	LeftClick(720, 110-6);
	SleepEx(1000, TRUE);
}


void CPlatformOperator::SetPlaceKick( char team )
{
	LeftClick(720, 135-6);
	SleepEx(1000, TRUE);
	if (team == 'B' || team == 'b')
		LeftClick(720, 269-6);
	else
		LeftClick(720, 242-6);
	SleepEx(1000, TRUE);
}


void CPlatformOperator::SetPenaltyKick( char team )
{
	LeftClick(720, 162-6);
	SleepEx(1000, TRUE);
	if (team == 'B' || team == 'b')
		LeftClick(720, 269-6);
	else
		LeftClick(720, 242-6);
	SleepEx(1000, TRUE);
}


void CPlatformOperator::SetGoalKick( char team )
{
	LeftClick(720, 216-6);
	SleepEx(1000, TRUE);
	if (team == 'B' || team == 'b')
		LeftClick(720, 269-6);
	else
		LeftClick(720, 242-6);
	SleepEx(1000, TRUE);
}


void CPlatformOperator::SetFreeKick( char team )
{
	LeftClick(720, 188-6);
	SleepEx(1000, TRUE);
	if (team == 'B' || team == 'b')
		LeftClick(720, 269-6);
	else
		LeftClick(720, 242-6);
	SleepEx(1000, TRUE);
}


void CPlatformOperator::SetNewgame( )
{
	LeftClick(720, 552-6);
	SleepEx(1000, TRUE);
}


void CPlatformOperator::CloseServer()
{
	::PostMessage(m_hWnd, WM_QUIT, NULL, NULL);
}


