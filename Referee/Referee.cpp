/*! @file
********************************************************************************
<PRE>
Module			 : Implementation of class Team for referee.
File			 : Referee.cpp
Relevent File(s) : Referee.h
Function(s)      : Automatic referee for FIRA MiroSot/SimuroSot.
Author(s)        : Le Li, Linquan Yang
Version          : 0.1
--------------------------------------------------------------------------------
Remarks           : -
--------------------------------------------------------------------------------
Modifications : 
Date          Version           Modifier				  Content
2018/03/06      0.1             Le Li, Dr.YANG             Create
2018/05/31      0.1             Le Li, Dr.YANG             Modify
</PRE>
******************************************************************************** 

* Copyright(c) 2018-, Linquan Yang, All rights reserved. 
* Contact:	yanglinquan@126.com
* China University of Geosciences.
*******************************************************************************/

#include "stdafx.h"
#include "Referee.h"
#include <math.h>



double Deg2Rad(double x)
{
	return (x * PI / 180.0);
}

double sinDeg(double x)
{
	return (sin(Deg2Rad(x)));
}

double cosDeg(double x)
{
	return (cos(Deg2Rad(x)));
}

void GetVertex(Robot r, Vector3D vertex[])
{
	// Vector3D vertex[4]; 
	double x = r.pos.x;
	double y = r.pos.y;
	double rotation = r.rotation;

	vertex[0].x = x + 5.7 * cosDeg(rotation - 45);
	vertex[0].y = y - 5.7 * sinDeg(rotation - 45);
	vertex[1].x = x + 5.7 * cosDeg(rotation - 135);
	vertex[1].y = y - 5.7 * sinDeg(rotation - 135);
	vertex[2].x = x + 5.7 * cosDeg(rotation + 135);
	vertex[2].y = y - 5.7 * sinDeg(rotation + 135);
	vertex[3].x = x + 5.7 * cosDeg(rotation + 45);
	vertex[3].y = y - 5.7 * sinDeg(rotation + 45);
}

double getLength(Vector3D a, Vector3D b)   
{
	double disx = a.x - b.x;
	double disy = a.y - b.y;
	double num = (disx * disx) + (disy * disy);   
	return sqrt(num);
}

bool Judge_Collision(Robot x, Robot y)
{
	RefRobot a, b;
	a.pos = x.pos;
	b.pos = y.pos;
	a.rotation = x.rotation;
	b.rotation = y.rotation;
	GetVertex(x, a.vertex);
	GetVertex(y, b.vertex);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ((getLength(a.vertex[i], b.vertex[j]) + getLength(a.vertex[i + 1], b.vertex[j])) < (getLength(a.vertex[i], a.vertex[i + 1]) + 0.15))
			{
				return true;
			}
			if (i == 0)
			{
				if ((getLength(a.vertex[0], b.vertex[j]) + getLength(a.vertex[3], b.vertex[j])) < (getLength(a.vertex[0], a.vertex[3]) + 0.15))
				{
					return true;
				}
			}
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if ((getLength(b.vertex[i], a.vertex[j]) + getLength(b.vertex[i + 1], a.vertex[j])) < (getLength(b.vertex[i], b.vertex[i + 1]) + 0.15))
				{
					return true;
				}
				if (i == 0)
				{
					if ((getLength(b.vertex[0], a.vertex[j]) + getLength(b.vertex[3], a.vertex[j])) < (getLength(b.vertex[0], b.vertex[3]) + 0.15))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

REFEREE_API void CheckPosxianbai(Robot Posxianbai[], PlayMode gameState)
{

}

REFEREE_API void CheckPoshoubai(Robot Poshoubai[], PlayMode gameState)
{

}

REFEREE_API void CheckPosBall(Vector3D &Posball, PlayMode gameState)
{
	if (gameState == 11)
	{
		if (Posball.x < 0 || Posball.x >= 15 || Posball.y < 65 || Posball.y > 115)
		{
			Posball.x = 14;
			Posball.y = 90;
		}
	}
	else
	{
		if (Posball.x > 220 || Posball.x <= 205 || Posball.y < 65 || Posball.y > 115)
		{
			Posball.x = 206;
			Posball.y = 90;
		}
	}
}

REFEREE_API void BaiQiu(Vector3D &Posball, PlayMode gameState)
{   
	switch (gameState){
	case PM_FreeBall_LeftTop:
		Posball.x = 55;
		Posball.y = 150;
		break;
	case PM_FreeBall_LeftBot:
		Posball.x = 55;
		Posball.y = 30;
		break;
	case PM_FreeBall_RightTop:
		Posball.x = 165;
		Posball.y = 150;
		break;
	case PM_FreeBall_RightBot:
		Posball.x = 165;
		Posball.y = 30;
		break;
	case PM_PlaceKick_Yellow:
		Posball.x = 110;
		Posball.y = 90;
		break;
	case PM_PlaceKick_Blue:
		Posball.x = 110;
		Posball.y = 90;
		break;
	case PM_PenaltyKick_Yellow:
		Posball.x = 182.5;
		Posball.y = 90;
		break;
	case PM_PenaltyKick_Blue:
		Posball.x = 37.5;
		Posball.y = 90;
		break;
	case PM_FreeKick_Yellow:
		Posball.x = 182.5;
		Posball.y = 90;
		break;
	case PM_FreeKick_Blue:
		Posball.x = 37.5;
		Posball.y = 90;
		break;
	}
}


bool Team::Set_PLACE_KICK(int PLACE_KICK)
{
	if (PLACE_KICK == 6 && duiwu == 1)
	{
		return true;
	}
	else if (PLACE_KICK == 6 && duiwu == 2)
	{
		return false;
	}
	else if (PLACE_KICK == 5 && duiwu == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Team::Set_GOAL_KICK(int GOAL_KICK1)
{
	if (GOAL_KICK1 == 12 && duiwu == 1)
	{
		return true;
	}
	else if (GOAL_KICK1 == 12 && duiwu == 2)
	{
		return false;
	}
	else if (GOAL_KICK1 == 11 && duiwu == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Team::Set_PENALTY_KICK(int PENALTY_KICK)
{
	if (PENALTY_KICK == 7 && duiwu == 1)
	{
		return true;
	}
	else if (PENALTY_KICK == 7 && duiwu == 2)
	{
		return false;
	}
	else if (PENALTY_KICK == 8 && duiwu == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Team::Set_FREE_BALL(int FREE_BALL)
{
	if (FREE_BALL == 12 && duiwu == 1)
	{
		return true;
	}
	else if (FREE_BALL == 12 && duiwu == 2)
	{
		return false;
	}
	else if (FREE_BALL == 11 && duiwu == 2)
	{
		return true;
	}
	else if (FREE_BALL == 11 && duiwu == 1)
	{
		return false;
	}
	else if (FREE_BALL == 1 && duiwu == 1)
	{
		return false;
	}
	else if (FREE_BALL == 1 && duiwu == 2)
	{
		return true;
	}
	else if (FREE_BALL == 2 && duiwu == 1)
	{
		return false;
	}
	else if (FREE_BALL == 2 && duiwu == 2)
	{
		return true;
	}
	else if (FREE_BALL == 3 && duiwu == 1)
	{
		return true;
	}
	else if (FREE_BALL == 3 && duiwu == 2)
	{
		return false;
	}
	else if (FREE_BALL == 4 && duiwu == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Team::Judge_duiwu(Environment *pEnv)
{
	if (pEnv->home[0].pos.x >= -15 && pEnv->home[0].pos.x <= 80)  
		duiwu = YELLOW_TEAM;
	else
		duiwu = BLUE_TEAM;
}

int Team::Judge_PENALTY_KICK(Environment *pEnv)
{
	int num1 = 0;    
	int num2 = 0;    
	int zong = 0;    
	int nCycles = 10;
	if (pEnv->currentBall.pos.x >= 0 && pEnv->currentBall.pos.x <= 80 && pEnv->currentBall.pos.y >= 30 && pEnv->currentBall.pos.y <= 150)
	{
		if (duiwu == 2)     
		{
			for (int i = 1; i < 5; i++)
			{
				if ((pEnv->home[i].pos.x >= -15 && pEnv->home[i].pos.x <= 0 && pEnv->home[i].pos.y >= 70 && pEnv->home[i].pos.y <= 110) || (pEnv->home[i].pos.x >= 0 && pEnv->home[i].pos.x <= 15 && pEnv->home[i].pos.y >= 65 && pEnv->home[i].pos.y <= 115))
				{
					num1 = num1 + 1;
					if (num1 == 1)
					{
						if (recordrobot == 0 || recordrobot == i)
						{
							recordrobot = i;
							recordtime1 = recordtime1 + 1;
						}
						else
						{
							recordrobot = i;
							recordtime1 = 1;
						}
					}
					else
					{
						recordrobot = 0;
						recordtime1 = 0;
						recordtime2 = 0;
						statespace.gameState = PM_PenaltyKick_Blue;
						return 8;
					}
				}
				if (((pEnv->home[i].pos.x >= 0 && pEnv->home[i].pos.x <= 15) && ((pEnv->home[i].pos.y >= 50 && pEnv->home[i].pos.y <= 65) || (pEnv->home[i].pos.y >= 115 && pEnv->home[i].pos.y <= 130))) || (pEnv->home[i].pos.x >= 15 && pEnv->home[i].pos.x <= 35 && pEnv->home[i].pos.y >= 50 && pEnv->home[i].pos.y <= 130))
				{
					num2 = num2 + 1;
					zong = zong + i;
				}
			}
			if (recordtime1 > nCycles)
			{
				recordrobot = 0;
				recordtime1 = 0;
				recordtime2 = 0;
				statespace.gameState = PM_PenaltyKick_Blue;
				return 8;
			}
			zong = zong + recordrobot;
			int num = num1 + num2;
			if (num > 3)
			{
				recordzong = 0;
				recordtime1 = 0;
				recordtime2 = 0;
				statespace.gameState = PM_PenaltyKick_Blue;
				return 8;
			}
			else if (num == 3)
			{
				if (recordzong == 0 || recordzong == zong)
				{
					recordzong = zong;
					recordtime2 = recordtime2 + 1;
				}
				else
				{
					recordzong = zong;
					recordtime2 = 1;
					statespace.gameState = PM_PlayOn;
					return 0;
				}
			}
			else
			{
				recordzong = 0;
				recordtime2 = 0;
				statespace.gameState = PM_PlayOn;
				return 0;
			}
			if (recordtime2 > nCycles)
			{
				recordzong = 0;
				recordtime1 = 0;
				recordtime2 = 0;
				statespace.gameState = PM_PenaltyKick_Blue;
				return 8;
			}
			else
			{
				statespace.gameState = PM_PlayOn;
				return 0;
			}
		}
		else
		{
			for (int i = 1; i < 5; i++)
			{
				if ((pEnv->opponent[i].pos.x >= -15 && pEnv->opponent[i].pos.x <= 0 && pEnv->opponent[i].pos.y >= 70 && pEnv->opponent[i].pos.y <= 110) || (pEnv->opponent[i].pos.x >= 0 && pEnv->opponent[i].pos.x <= 15 && pEnv->opponent[i].pos.y >= 65 && pEnv->opponent[i].pos.y <= 115))
				{
					num1 = num1 + 1;
					if (num1 == 1)
					{
						if (op_recordrobot == 0 || op_recordrobot == i)
						{
							op_recordrobot = i;
							op_recordtime1 = op_recordtime1 + 1;
						}
						else
						{
							op_recordrobot = i;
							op_recordtime1 = 1;
						}
					}
					else
					{
						op_recordrobot = 0;
						op_recordtime1 = 0;
						op_recordtime2 = 0;
						statespace.gameState = PM_PenaltyKick_Blue;
						return 8;
					}
				}
				if (((pEnv->opponent[i].pos.x >= 0 && pEnv->opponent[i].pos.x <= 15) && ((pEnv->opponent[i].pos.y >= 50 && pEnv->opponent[i].pos.y <= 65) || (pEnv->opponent[i].pos.y >= 115 && pEnv->opponent[i].pos.y <= 130))) || (pEnv->opponent[i].pos.x >= 15 && pEnv->opponent[i].pos.x <= 35 && pEnv->opponent[i].pos.y >= 50 && pEnv->opponent[i].pos.y <= 130))
				{
					num2 = num2 + 1;
					zong = zong + i;
				}
			}
			if (op_recordtime1 > nCycles)
			{
				op_recordrobot = 0;
				op_recordtime1 = 0;
				op_recordtime2 = 0;
				statespace.gameState = PM_PenaltyKick_Blue;
				return 8;
			}
			zong = zong + op_recordrobot;
			int num = num1 + num2;
			if (num > 3)
			{
				op_recordzong = 0;
				op_recordtime1 = 0;
				op_recordtime2 = 0;
				statespace.gameState = PM_PenaltyKick_Blue;
				return 8;
			}
			else if (num == 3)
			{
				if (op_recordzong == 0 || op_recordzong == zong)
				{
					op_recordzong = zong;
					op_recordtime2 = op_recordtime2 + 1;
				}
				else
				{
					op_recordzong = zong;
					op_recordtime2 = 1;
					statespace.gameState = PM_PlayOn;
					return 0;
				}
			}
			else
			{
				op_recordzong = 0;
				op_recordtime2 = 0;
				statespace.gameState = PM_PlayOn;
				return 0;
			}
			if (op_recordtime2 > nCycles)
			{
				op_recordzong = 0;
				op_recordtime1 = 0;
				op_recordtime2 = 0;
				statespace.gameState = PM_PenaltyKick_Blue;
				return 8;
			}
			else
			{
				statespace.gameState = PM_PlayOn;
				return 0;
			}

		}
	}
	else if (pEnv->currentBall.pos.x >= 140 && pEnv->currentBall.pos.x <= 220 && pEnv->currentBall.pos.y >= 30 && pEnv->currentBall.pos.y <= 150)
	{
		if (duiwu == 1)     
		{
			for (int i = 1; i < 5; i++)
			{
				if ((pEnv->home[i].pos.x >= 220 && pEnv->home[i].pos.x <= 235 && pEnv->home[i].pos.y >= 70 && pEnv->home[i].pos.y <= 110) || (pEnv->home[i].pos.x >= 205 && pEnv->home[i].pos.x <= 220 && pEnv->home[i].pos.y >= 65 && pEnv->home[i].pos.y <= 115))
				{
					num1 = num1 + 1;
					if (num1 == 1)
					{
						if (recordrobot == 0 || recordrobot == i)
						{
							recordrobot = i;
							recordtime1 = recordtime1 + 1;
						}
						else
						{
							recordrobot = i;
							recordtime1 = 1;
						}
					}
					else
					{
						recordrobot = 0;
						recordtime1 = 0;
						recordtime2 = 0;
						statespace.gameState = PM_PenaltyKick_Yellow;
						return 7;
					}

				}
				if (((pEnv->home[i].pos.x >= 205 && pEnv->home[i].pos.x <= 220) && ((pEnv->home[i].pos.y >= 50 && pEnv->home[i].pos.y <= 65) || (pEnv->home[i].pos.y >= 115 && pEnv->home[i].pos.y <= 130))) || (pEnv->home[i].pos.x >= 185 && pEnv->home[i].pos.x <= 205 && pEnv->home[i].pos.y >= 50 && pEnv->home[i].pos.y <= 130))
				{
					num2 = num2 + 1;
					zong = zong + i;
				}
			}
			if (recordtime1 > nCycles)
			{
				recordrobot = 0;
				recordtime1 = 0;
				recordtime2 = 0;
				statespace.gameState = PM_PenaltyKick_Yellow;
				return 7;
			}
			zong = zong + recordrobot;
			int num = num1 + num2;
			if (num > 3)
			{
				recordzong = 0;
				recordtime1 = 0;
				recordtime2 = 0;
				statespace.gameState = PM_PenaltyKick_Yellow;
				return 7;
			}
			else if (num == 3)
			{
				if (recordzong == 0 || recordzong == zong)
				{
					recordzong = zong;
					recordtime2 = recordtime2 + 1;
				}
				else
				{
					recordzong = zong;
					recordtime2 = 1;
					statespace.gameState = PM_PlayOn;
					return 0;
				}
			}
			else
			{
				recordzong = 0;
				recordtime2 = 0;
				statespace.gameState = PM_PlayOn;
				return 0;
			}
			if (recordtime2 > nCycles)
			{
				recordzong = 0;
				recordtime1 = 0;
				recordtime2 = 0;
				statespace.gameState = PM_PenaltyKick_Yellow;
				return 7;
			}
			else
			{
				statespace.gameState = PM_PlayOn;
				return 0;
			}
		}
		else
		{
			for (int i = 1; i < 5; i++)
			{
				if ((pEnv->opponent[i].pos.x >= 220 && pEnv->opponent[i].pos.x <= 235 && pEnv->opponent[i].pos.y >= 70 && pEnv->opponent[i].pos.y <= 110) || (pEnv->opponent[i].pos.x >= 205 && pEnv->opponent[i].pos.x <= 220 && pEnv->opponent[i].pos.y >= 65 && pEnv->opponent[i].pos.y <= 115))
				{
					num1 = num1 + 1;
					if (num1 == 1)
					{
						if (op_recordrobot == 0 || op_recordrobot == i)
						{
							op_recordrobot = i;
							op_recordtime1 = op_recordtime1 + 1;
						}
						else
						{
							op_recordrobot = i;
							op_recordtime1 = 1;
						}
					}
					else
					{
						op_recordrobot = 0;
						op_recordtime1 = 0;
						op_recordtime2 = 0;
						statespace.gameState = PM_PenaltyKick_Yellow;
						return 7;
					}

				}
				if (((pEnv->opponent[i].pos.x >= 205 && pEnv->opponent[i].pos.x <= 220) && ((pEnv->opponent[i].pos.y >= 50 && pEnv->opponent[i].pos.y <= 65) || (pEnv->opponent[i].pos.y >= 115 && pEnv->opponent[i].pos.y <= 130))) || (pEnv->opponent[i].pos.x >= 185 && pEnv->opponent[i].pos.x <= 205 && pEnv->opponent[i].pos.y >= 50 && pEnv->opponent[i].pos.y <= 130))
				{
					num2 = num2 + 1;
					zong = zong + i;
				}
			}
			if (op_recordtime1 > nCycles)
			{
				op_recordrobot = 0;
				op_recordtime1 = 0;
				op_recordtime2 = 0;
				statespace.gameState = PM_PenaltyKick_Yellow;
				return 7;
			}
			zong = zong + op_recordrobot;
			int num = num1 + num2;
			if (num > 3)
			{
				op_recordzong = 0;
				op_recordtime1 = 0;
				op_recordtime2 = 0;
				statespace.gameState = PM_PenaltyKick_Yellow;
				return 7;
			}
			else if (num == 3)
			{
				if (op_recordzong == 0 || op_recordzong == zong)
				{
					op_recordzong = zong;
					op_recordtime2 = op_recordtime2 + 1;
				}
				else
				{
					op_recordzong = zong;
					op_recordtime2 = 1;
					statespace.gameState = PM_PlayOn;
					return 0;
				}
			}
			else
			{
				op_recordzong = 0;
				op_recordtime2 = 0;
				statespace.gameState = PM_PlayOn;
				return 0;
			}
			if (op_recordtime2 > nCycles)
			{
				op_recordzong = 0;
				op_recordtime1 = 0;
				op_recordtime2 = 0;
				statespace.gameState = PM_PenaltyKick_Yellow;
				return 7;
			}
			else
			{
				statespace.gameState = PM_PlayOn;
				return 0;
			}
		}
	}
	else
	{
		recordzong = 0;
		recordtime1 = 0;
		recordtime2 = 0;
		op_recordzong = 0;
		op_recordtime1 = 0;
		op_recordtime2 = 0;
		statespace.gameState = PM_PlayOn;
		return 0;
	}
}

int Team::Judge_GOAL_KICK1(Environment *pEnv)                              
{
	if (pEnv->currentBall.pos.x >= 140 && pEnv->currentBall.pos.x <= 220 && pEnv->currentBall.pos.y >= 30 && pEnv->currentBall.pos.y <= 150)
	{
		if (duiwu == 2)
		{
			if (statespace.opponent[0].pos.x < 205 || statespace.opponent[0].pos.y < 65 || statespace.opponent[0].pos.y > 115)
			{
				statespace.gameState = PM_PlayOn;
				return 0;
			}
			for (int i = 0; i < 5; i++)
			{
				if (Judge_Collision(statespace.home[i], statespace.opponent[0]))
				{
					statespace.gameState = PM_GoalKick_Blue;
					return 12;
				}
			}
			statespace.gameState = PM_PlayOn;
			return 0;
		}
		else
		{
			if (statespace.home[0].pos.x < 205 || statespace.home[0].pos.y < 65 || statespace.home[0].pos.y > 115)
			{
				statespace.gameState = PM_PlayOn;
				return 0;
			}
			for (int i = 0; i < 5; i++)
			{
				if (Judge_Collision(statespace.home[0], statespace.opponent[i]))
				{
					statespace.gameState = PM_GoalKick_Blue;
					return 12;
				}
			}
			statespace.gameState = PM_PlayOn;
			return 0;
		}

	}
	else if (pEnv->currentBall.pos.x >= 0 && pEnv->currentBall.pos.x <= 80 && pEnv->currentBall.pos.y >= 30 && pEnv->currentBall.pos.y <= 150)
	{
		if (duiwu == 1)
		{
			if (statespace.opponent[0].pos.x > 15 || statespace.opponent[0].pos.y < 65 || statespace.opponent[0].pos.y > 115)
			{
				statespace.gameState = PM_PlayOn;
				return 0;
			}
			for (int i = 0; i < 5; i++)
			{
				if (Judge_Collision(statespace.home[i], statespace.opponent[0]))
				{
					statespace.gameState = PM_GoalKick_Yellow;
					return 11;
				}
			}
			statespace.gameState = PM_PlayOn;
			return 0;
		}
		else
		{
			if (statespace.home[0].pos.x > 15 || statespace.home[0].pos.y < 65 || statespace.home[0].pos.y > 115)
			{
				statespace.gameState = PM_PlayOn;
				return 0;
			}
			for (int i = 0; i < 5; i++)
			{
				if (Judge_Collision(statespace.home[0], statespace.opponent[i]))
				{
					statespace.gameState = PM_GoalKick_Yellow;
					return 11;
				}
			}
			statespace.gameState = PM_PlayOn;
			return 0;
		}
	}
	else
	{
		statespace.gameState = PM_PlayOn;
		return 0;
	}
}


int Team::Judge_GOAL_KICK2(Environment *pEnv)
{
	int num3 = 0;     
	int num4 = 0;    
	int zong4 = 0;    
	int robot3 = 0;   
	int nCycles = 10;

	if (pEnv->currentBall.pos.x >= 140 && pEnv->currentBall.pos.x <= 220 && pEnv->currentBall.pos.y >= 30 && pEnv->currentBall.pos.y <= 150)
	{
		if (duiwu == 2)
		{
			for (int i = 0; i < 5; i++)
			{
				if ((pEnv->home[i].pos.x >= 220 && pEnv->home[i].pos.x <= 235 && pEnv->home[i].pos.y >= 70 && pEnv->home[i].pos.y <= 110) || (pEnv->home[i].pos.x >= 205 && pEnv->home[i].pos.x <= 220 && pEnv->home[i].pos.y >= 65 && pEnv->home[i].pos.y <= 115))
				{
					num3 = num3 + 1;
					if (num3 == 1)
					{
						robot3 = i;
					}
					else if (num3 == 2)
					{
						if (recordrobot3 == 0)
						{
							recordrobot3 = robot3;
							recordrobot4 = i;
							recordtime3 = 1;
						}
						else if (recordrobot3 == robot3)
						{
							if (recordrobot4 == i)
							{
								recordtime3 = recordtime3 + 1;
							}
							else
							{
								recordrobot4 = i;
								recordtime3 = 1;
							}
						}
						else
						{
							recordrobot3 = robot3;
							recordrobot4 = i;
							recordtime3 = 1;
						}
					}
					else
					{
						recordrobot3 = 0;
						recordrobot4 = 0;
						recordtime3 = 0;
						recordtime4 = 0;
						recordzong4 = 0;
						statespace.gameState = PM_GoalKick_Blue;
						return 12;
					}
				}

				if (((pEnv->home[i].pos.x >= 205 && pEnv->home[i].pos.x <= 220) && ((pEnv->home[i].pos.y >= 50 && pEnv->home[i].pos.y <= 65) || (pEnv->home[i].pos.y >= 115 && pEnv->home[i].pos.y <= 130))) || (pEnv->home[i].pos.x >= 185 && pEnv->home[i].pos.x <= 205 && pEnv->home[i].pos.y >= 50 && pEnv->home[i].pos.y <= 130))
				{
					num4 = num4 + 1;
					zong4 = zong4 + i;
				}
			}
			if (recordtime3 > nCycles)
			{
				recordrobot3 = 0;
				recordrobot4 = 0;
				recordzong4 = 0;
				recordtime3 = 0;
				recordtime4 = 0;
				statespace.gameState = PM_GoalKick_Blue;
				return 12;
			}
			zong4 = zong4 + robot3 + recordrobot4;
			int num = num3 + num4;
			if (num > 4)
			{
				recordrobot3 = 0;
				recordrobot4 = 0;
				recordzong4 = 0;
				recordtime3 = 0;
				recordtime4 = 0;
				statespace.gameState = PM_GoalKick_Blue;
				return 12;
			}
			else if (num == 4)
			{
				if (recordzong4 == 0 || recordzong4 == zong4)
				{
					recordzong4 = zong4;
					recordtime4 = recordtime4 + 1;
				}
				else
				{
					recordzong4 = zong4;
					recordtime4 = 1;
					statespace.gameState = PM_PlayOn;
					return 0;
				}
			}
			else
			{
				recordzong4 = 0;
				recordtime4 = 0;
				statespace.gameState = PM_PlayOn;
				return 0;
			}
			if (recordtime4 > nCycles)
			{
				recordrobot3 = 0;
				recordrobot4 = 0;
				recordzong4 = 0;
				recordtime3 = 0;
				recordtime4 = 0;
				statespace.gameState = PM_GoalKick_Blue;
				return 12;
			}
			else
			{
				statespace.gameState = PM_PlayOn;
				return 0;
			}
		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				if ((pEnv->opponent[i].pos.x >= 220 && pEnv->opponent[i].pos.x <= 235 && pEnv->opponent[i].pos.y >= 70 && pEnv->opponent[i].pos.y <= 110) || (pEnv->opponent[i].pos.x >= 205 && pEnv->opponent[i].pos.x <= 220 && pEnv->opponent[i].pos.y >= 65 && pEnv->opponent[i].pos.y <= 115))
				{
					num3 = num3 + 1;
					if (num3 == 1)
					{
						robot3 = i;
					}
					else if (num3 == 2)
					{
						if (op_recordrobot3 == 0)
						{
							op_recordrobot3 = robot3;
							op_recordrobot4 = i;
							op_recordtime3 = 1;
						}
						else if (op_recordrobot3 == robot3)
						{
							if (op_recordrobot4 == i)
							{
								op_recordtime3 = op_recordtime3 + 1;
							}
							else
							{
								op_recordrobot4 = i;
								op_recordtime3 = 1;
							}
						}
						else
						{
							op_recordrobot3 = robot3;
							op_recordrobot4 = i;
							op_recordtime3 = 1;
						}
					}
					else
					{
						op_recordrobot3 = 0;
						op_recordrobot4 = 0;
						op_recordtime3 = 0;
						op_recordtime4 = 0;
						op_recordzong4 = 0;
						statespace.gameState = PM_GoalKick_Blue;
						return 12;
					}
				}

				if (((pEnv->opponent[i].pos.x >= 205 && pEnv->opponent[i].pos.x <= 220) && ((pEnv->opponent[i].pos.y >= 50 && pEnv->opponent[i].pos.y <= 65) || (pEnv->opponent[i].pos.y >= 115 && pEnv->opponent[i].pos.y <= 130))) || (pEnv->opponent[i].pos.x >= 185 && pEnv->opponent[i].pos.x <= 205 && pEnv->opponent[i].pos.y >= 50 && pEnv->opponent[i].pos.y <= 130))
				{
					num4 = num4 + 1;
					zong4 = zong4 + i;
				}
			}
			if (op_recordtime3 > nCycles)
			{
				op_recordrobot3 = 0;
				op_recordrobot4 = 0;
				op_recordzong4 = 0;
				op_recordtime3 = 0;
				op_recordtime4 = 0;
				statespace.gameState = PM_GoalKick_Blue;
				return 12;
			}
			zong4 = zong4 + robot3 + op_recordrobot4;
			int num = num3 + num4;
			if (num > 4)
			{
				op_recordrobot3 = 0;
				op_recordrobot4 = 0;
				op_recordzong4 = 0;
				op_recordtime3 = 0;
				op_recordtime4 = 0;
				statespace.gameState = PM_GoalKick_Blue;
				return 12;
			}
			else if (num == 4)
			{
				if (op_recordzong4 == 0 || op_recordzong4 == zong4)
				{
					op_recordzong4 = zong4;
					op_recordtime4 = op_recordtime4 + 1;
				}
				else
				{
					op_recordzong4 = zong4;
					op_recordtime4 = 1;
					statespace.gameState = PM_PlayOn;
					return 0;
				}
			}
			else
			{
				op_recordzong4 = 0;
				op_recordtime4 = 0;
				statespace.gameState = PM_PlayOn;
				return 0;
			}
			if (op_recordtime4 > nCycles)
			{
				op_recordrobot3 = 0;
				op_recordrobot4 = 0;
				op_recordzong4 = 0;
				op_recordtime3 = 0;
				op_recordtime4 = 0;
				statespace.gameState = PM_GoalKick_Blue;
				return 12;
			}
			else
			{
				statespace.gameState = PM_PlayOn;
				return 0;
			}
		}
	}
	else if (pEnv->currentBall.pos.x >= 0 && pEnv->currentBall.pos.x <= 80 && pEnv->currentBall.pos.y >= 30 && pEnv->currentBall.pos.y <= 150)
	{
		if (duiwu == 1)
		{
			for (int i = 0; i < 5; i++)
			{
				if ((pEnv->home[i].pos.x >= -15 && pEnv->home[i].pos.x <= 0 && pEnv->home[i].pos.y >= 70 && pEnv->home[i].pos.y <= 110) || (pEnv->home[i].pos.x >= 0 && pEnv->home[i].pos.x <= 15 && pEnv->home[i].pos.y >= 65 && pEnv->home[i].pos.y <= 115))
				{
					num3 = num3 + 1;
					if (num3 == 1)
					{
						robot3 = i;
					}
					else if (num3 == 2)
					{
						if (recordrobot3 == 0)
						{
							recordrobot3 = robot3;
							recordrobot4 = i;
							recordtime3 = 1;
						}
						else if (recordrobot3 == robot3)
						{

							if (recordrobot4 == i)
							{
								recordtime3 = recordtime3 + 1;
							}
							else
							{
								recordrobot4 = i;
								recordtime3 = 1;
							}
						}
						else
						{
							recordrobot3 = robot3;
							recordrobot4 = i;
							recordtime3 = 1;
						}
					}
					else
					{
						recordrobot3 = 0;
						recordrobot4 = 0;
						recordtime3 = 0;
						recordtime4 = 0;
						recordzong4 = 0;
						statespace.gameState = PM_GoalKick_Yellow;
						return 11;
					}
				}

				if (((pEnv->home[i].pos.x >= 0 && pEnv->home[i].pos.x <= 15) && ((pEnv->home[i].pos.y >= 50 && pEnv->home[i].pos.y <= 65) || (pEnv->home[i].pos.y >= 115 && pEnv->home[i].pos.y <= 130))) || (pEnv->home[i].pos.x >= 15 && pEnv->home[i].pos.x <= 35 && pEnv->home[i].pos.y >= 50 && pEnv->home[i].pos.y <= 130))
				{
					num4 = num4 + 1;
					zong4 = zong4 + i;
				}
			}
			if (recordtime3 > nCycles)
			{
				recordrobot3 = 0;
				recordrobot4 = 0;
				recordzong4 = 0;
				recordtime3 = 0;
				recordtime4 = 0;
				statespace.gameState = PM_GoalKick_Yellow;
				return 11;
			}
			zong4 = zong4 + robot3 + recordrobot4;
			int num = num3 + num4;
			if (num > 4)
			{
				recordrobot3 = 0;
				recordrobot4 = 0;
				recordzong4 = 0;
				recordtime3 = 0;
				recordtime4 = 0;
				statespace.gameState = PM_GoalKick_Yellow;
				return 11;
			}
			else if (num == 4)
			{
				if (recordzong4 == 0 || recordzong4 == zong4)
				{
					recordzong4 = zong4;
					recordtime4 = recordtime4 + 1;
				}
				else
				{
					recordzong4 = zong4;
					recordtime4 = 1;
					statespace.gameState = PM_PlayOn;
					return 0;
				}
			}
			else
			{
				recordzong4 = 0;
				recordtime4 = 0;
				statespace.gameState = PM_PlayOn;
				return 0;
			}
			if (recordtime4 > nCycles)
			{
				recordrobot3 = 0;
				recordrobot4 = 0;
				recordzong4 = 0;
				recordtime3 = 0;
				recordtime4 = 0;
				statespace.gameState = PM_GoalKick_Yellow;
				return 11;
			}
			else
			{
				statespace.gameState = PM_PlayOn;
				return 0;
			}
		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				if ((pEnv->opponent[i].pos.x >= -15 && pEnv->opponent[i].pos.x <= 0 && pEnv->opponent[i].pos.y >= 70 && pEnv->opponent[i].pos.y <= 110) || (pEnv->opponent[i].pos.x >= 0 && pEnv->opponent[i].pos.x <= 15 && pEnv->opponent[i].pos.y >= 65 && pEnv->opponent[i].pos.y <= 115))
				{
					num3 = num3 + 1;
					if (num3 == 1)
					{
						robot3 = i;
					}
					else if (num3 == 2)
					{
						if (op_recordrobot3 == 0)
						{
							op_recordrobot3 = robot3;
							op_recordrobot4 = i;
							op_recordtime3 = 1;
						}
						else if (op_recordrobot3 == robot3)
						{

							if (op_recordrobot4 == i)
							{
								op_recordtime3 = op_recordtime3 + 1;
							}
							else
							{
								op_recordrobot4 = i;
								op_recordtime3 = 1;
							}
						}
						else
						{
							op_recordrobot3 = robot3;
							op_recordrobot4 = i;
							op_recordtime3 = 1;
						}
					}
					else
					{
						op_recordrobot3 = 0;
						op_recordrobot4 = 0;
						op_recordtime3 = 0;
						op_recordtime4 = 0;
						op_recordzong4 = 0;
						statespace.gameState = PM_GoalKick_Yellow;
						return 11;
					}
				}

				if (((pEnv->opponent[i].pos.x >= 0 && pEnv->opponent[i].pos.x <= 15) && ((pEnv->opponent[i].pos.y >= 50 && pEnv->opponent[i].pos.y <= 65) || (pEnv->opponent[i].pos.y >= 115 && pEnv->opponent[i].pos.y <= 130))) || (pEnv->opponent[i].pos.x >= 15 && pEnv->opponent[i].pos.x <= 35 && pEnv->opponent[i].pos.y >= 50 && pEnv->opponent[i].pos.y <= 130))
				{
					num4 = num4 + 1;
					zong4 = zong4 + i;
				}
			}
			if (op_recordtime3 > nCycles)
			{
				op_recordrobot3 = 0;
				op_recordrobot4 = 0;
				op_recordzong4 = 0;
				op_recordtime3 = 0;
				op_recordtime4 = 0;
				statespace.gameState = PM_GoalKick_Yellow;
				return 11;
			}
			zong4 = zong4 + robot3 + op_recordrobot4;
			int num = num3 + num4;
			if (num > 4)
			{
				op_recordrobot3 = 0;
				op_recordrobot4 = 0;
				op_recordzong4 = 0;
				op_recordtime3 = 0;
				op_recordtime4 = 0;
				statespace.gameState = PM_GoalKick_Yellow;
				return 11;
			}
			else if (num == 4)
			{
				if (op_recordzong4 == 0 || op_recordzong4 == zong4)
				{
					op_recordzong4 = zong4;
					op_recordtime4 = op_recordtime4 + 1;
				}
				else
				{
					op_recordzong4 = zong4;
					op_recordtime4 = 1;
					statespace.gameState = PM_PlayOn;
					return 0;
				}
			}
			else
			{
				op_recordzong4 = 0;
				op_recordtime4 = 0;
				statespace.gameState = PM_PlayOn;
				return 0;
			}
			if (op_recordtime4 > nCycles)
			{
				op_recordrobot3 = 0;
				op_recordrobot4 = 0;
				op_recordzong4 = 0;
				op_recordtime3 = 0;
				op_recordtime4 = 0;
				statespace.gameState = PM_GoalKick_Yellow;
				return 11;
			}
			else
			{
				statespace.gameState = PM_PlayOn;
				return 0;
			}
		}
	}
	else
	{
		recordrobot3 = 0;
		recordrobot4 = 0;
		recordzong4 = 0;
		recordtime3 = 0;
		recordtime4 = 0;
		op_recordrobot3 = 0;
		op_recordrobot4 = 0;
		op_recordzong4 = 0;
		op_recordtime3 = 0;
		op_recordtime4 = 0;
		statespace.gameState = PM_PlayOn;
		return 0;
	}
}

int Team::Judge_PLACE_KICK(Environment *pEnv)
{
	statespace.currentBall = pEnv->currentBall;
	for (int i = 0; i < 5; i++)
	{
		statespace.home[i].pos = pEnv->home[i].pos;
		statespace.opponent[i].pos = pEnv->opponent[i].pos;
		statespace.home[i].rotation = pEnv->home[i].rotation;
		statespace.opponent[i].rotation = pEnv->opponent[i].rotation;
	}
	if (pEnv->currentBall.pos.x <= -2.5)
	{
		statespace.gameState = PM_PlaceKick_Yellow;
		return 5;
	}
	else if (pEnv->currentBall.pos.x >= 222.5)
	{
		statespace.gameState = PM_PlaceKick_Blue;
		return 6;
	}
	else
	{
		statespace.gameState = PM_PlayOn;
		return 0;
	}
}

int Team::Judge_FREE_BALL(Environment *pEnv)
{
	int robot;
	bool tuiqiu1 = false;         
	bool tuiqiu2 = false;         
	bool tuiqiu3 = false;         
	bool facetoface = false;      
	int nSlowCycles = 100;
	int nFaceCycles = 50;
	if (pEnv->currentBall.pos.x <= 8 && pEnv->currentBall.pos.y <= 70)
	{
		if (duiwu == 2)
		{
			for (int i = 0; i < 5; i++)
			{
				if (pEnv->home[i].pos.y < pEnv->currentBall.pos.y && pEnv->home[i].pos.x <= 8 && pEnv->home[i].pos.y <= 70)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						tuiqiu3 = true;
					}
				}
				if (pEnv->home[i].pos.y > pEnv->currentBall.pos.y && pEnv->home[i].pos.x <= 8 && pEnv->home[i].pos.y <= 70)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu1 = true;
						break;
					}
				}
			}
			if (tuiqiu1)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->home[i].pos.x <= 8 && pEnv->home[i].pos.y <= 70)
						{
							if (Judge_Collision(statespace.home[i], statespace.home[robot]))
							{
								statespace.gameState = PM_FreeBall_LeftBot;
								Foul_pushball += 1;
								return 2;
							}
						}
					}
				}
			}
			if (tuiqiu1 || tuiqiu3)
			{
				for (int i = 0; i < 5; i++)
				{
					if (pEnv->opponent[i].pos.x <= 8 && pEnv->opponent[i].pos.y <= 70)
					{
						if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
						{
							facetoface = true;
							pushball += 1;
							if (pushball >= nFaceCycles)
							{
								statespace.gameState = PM_FreeBall_LeftBot;
								pushball = 0;
								return 2;
							}
						}
					}
				}
				if (facetoface == false)
				{
					pushball = 0;
				}
			}
			else
			{
				pushball = 0;
			}

			for (int i = 0; i < 5; i++)
			{
				if (pEnv->opponent[i].pos.y < pEnv->currentBall.pos.y && pEnv->opponent[i].pos.x <= 8 && pEnv->opponent[i].pos.y <= 70)
				{
					if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu2 = true;
						break;
					}
				}
			}
			if (tuiqiu2)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->opponent[i].pos.x <= 8 && pEnv->opponent[i].pos.y <= 70)
						{
							if (Judge_Collision(statespace.opponent[i], statespace.opponent[robot]))
							{
								statespace.gameState = PM_FreeBall_RightBot;
								return 4;
							}
						}
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				if (pEnv->home[i].pos.y > pEnv->currentBall.pos.y && pEnv->home[i].pos.x <= 8 && pEnv->home[i].pos.y <= 70)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						tuiqiu3 = true;
					}
				}
				if (pEnv->home[i].pos.y < pEnv->currentBall.pos.y && pEnv->home[i].pos.x <= 8 && pEnv->home[i].pos.y <= 70)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu1 = true;
						break;
					}
				}
			}
			if (tuiqiu1)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->home[i].pos.x <= 8 && pEnv->home[i].pos.y <= 70)
						{
							if (Judge_Collision(statespace.home[i], statespace.home[robot]))
							{
								statespace.gameState = PM_FreeBall_RightBot;
								Foul_pushball += 1;
								return 4;
							}
						}
					}
				}
			}
			if (tuiqiu1 || tuiqiu3)
			{
				for (int i = 0; i < 5; i++)
				{
					if (pEnv->opponent[i].pos.x <= 8 && pEnv->opponent[i].pos.y <= 70)
					{
						if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
						{
							facetoface = true;
							pushball += 1;
							if (pushball >= nFaceCycles)
							{
								statespace.gameState = PM_FreeBall_LeftBot;
								pushball = 0;
								return 2;
							}
						}
					}
				}
				if (facetoface == false)
				{
					pushball = 0;
				}
			}
			else
			{
				pushball = 0;
			}


			for (int i = 0; i < 5; i++)
			{
				if (pEnv->opponent[i].pos.y > pEnv->currentBall.pos.y && pEnv->opponent[i].pos.x <= 8 && pEnv->opponent[i].pos.y <= 70)
				{
					if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu2 = true;
						break;
					}
				}
			}
			if (tuiqiu2)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->opponent[i].pos.x <= 8 && pEnv->opponent[i].pos.y <= 70)
						{
							if (Judge_Collision(statespace.opponent[i], statespace.opponent[robot]))
							{
								statespace.gameState = PM_FreeBall_LeftBot;
								return 2;
							}
						}
					}
				}
			}
		}
	}


	if (pEnv->currentBall.pos.x <= 8 && pEnv->currentBall.pos.y >= 110)
	{
		if (duiwu == 2)
		{
			for (int i = 0; i < 5; i++)
			{
				if (pEnv->home[i].pos.y > pEnv->currentBall.pos.y && pEnv->home[i].pos.x <= 8 && pEnv->home[i].pos.y >= 110)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						tuiqiu3 = true;
					}
				}
				if (pEnv->home[i].pos.y < pEnv->currentBall.pos.y && pEnv->home[i].pos.x <= 8 && pEnv->home[i].pos.y >= 110)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu1 = true;
						break;
					}
				}
			}
			if (tuiqiu1)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->home[i].pos.x <= 8 && pEnv->home[i].pos.y >= 110)
						{
							if (Judge_Collision(statespace.home[i], statespace.home[robot]))
							{
								statespace.gameState = PM_FreeBall_LeftTop;
								Foul_pushball += 1;
								return 1;
							}
						}
					}
				}
			}
			if (tuiqiu1 || tuiqiu3)
			{
				for (int i = 0; i < 5; i++)
				{
					if (pEnv->opponent[i].pos.x <= 8 && pEnv->opponent[i].pos.y >= 110)
					{
						if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
						{
							facetoface = true;
							pushball += 1;
							if (pushball >= nFaceCycles)
							{
								statespace.gameState = PM_FreeBall_LeftTop;
								pushball = 0;
								return 1;
							}
						}
					}
				}
				if (facetoface == false)
				{
					pushball = 0;
				}
			}
			else
			{
				pushball = 0;
			}


			for (int i = 0; i < 5; i++)
			{
				if (pEnv->opponent[i].pos.y > pEnv->currentBall.pos.y && pEnv->opponent[i].pos.x <= 8 && pEnv->opponent[i].pos.y >= 110)
				{
					if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu2 = true;
						break;
					}
				}
			}
			if (tuiqiu2)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->opponent[i].pos.x <= 8 && pEnv->opponent[i].pos.y >= 110)
						{
							if (Judge_Collision(statespace.opponent[i], statespace.opponent[robot]))
							{
								statespace.gameState = PM_FreeBall_RightTop;
								return 3;
							}
						}
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				if (pEnv->home[i].pos.y < pEnv->currentBall.pos.y && pEnv->home[i].pos.x <= 8 && pEnv->home[i].pos.y <= 110)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						tuiqiu3 = true;
					}
				}
				if (pEnv->home[i].pos.y > pEnv->currentBall.pos.y && pEnv->home[i].pos.x <= 8 && pEnv->home[i].pos.y <= 110)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu1 = true;
						break;
					}
				}
			}
			if (tuiqiu1)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->home[i].pos.x <= 8 && pEnv->home[i].pos.y >= 110)
						{
							if (Judge_Collision(statespace.home[i], statespace.home[robot]))
							{
								statespace.gameState = PM_FreeBall_RightTop;
								Foul_pushball += 1;
								return 3;
							}
						}
					}
				}
			}
			if (tuiqiu1 || tuiqiu3)
			{
				for (int i = 0; i < 5; i++)
				{
					if (pEnv->opponent[i].pos.x <= 8 && pEnv->opponent[i].pos.y >= 110)
					{
						if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
						{
							facetoface = true;
							pushball += 1;
							if (pushball >= nFaceCycles)
							{
								statespace.gameState = PM_FreeBall_LeftTop;
								pushball = 0;
								return 1;
							}
						}
					}
				}
				if (facetoface == false)
				{
					pushball = 0;
				}
			}
			else
			{
				pushball = 0;
			}

			for (int i = 0; i < 5; i++)
			{
				if (pEnv->opponent[i].pos.y < pEnv->currentBall.pos.y && pEnv->opponent[i].pos.x <= 8 && pEnv->opponent[i].pos.y >= 110)
				{
					if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu2 = true;
						break;
					}
				}
			}
			if (tuiqiu2)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->opponent[i].pos.x <= 8 && pEnv->opponent[i].pos.y >= 110)
						{
							if (Judge_Collision(statespace.opponent[i], statespace.opponent[robot]))
							{
								statespace.gameState = PM_FreeBall_LeftTop;
								return 1;
							}
						}
					}
				}
			}
		}
	}

	if (pEnv->currentBall.pos.y >= 172)
	{
		if (duiwu == 2)
		{
			for (int i = 0; i < 5; i++)
			{
				if (pEnv->home[i].pos.x > pEnv->currentBall.pos.x && pEnv->home[i].pos.y >= 172)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						tuiqiu3 = true;
					}
				}
				if (pEnv->home[i].pos.x < pEnv->currentBall.pos.x && pEnv->home[i].pos.y >= 172)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu1 = true;
						break;
					}
				}
			}
			if (tuiqiu1)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->home[i].pos.y >= 172)
						{
							if (Judge_Collision(statespace.home[i], statespace.home[robot]))
							{
								statespace.gameState = PM_FreeBall_LeftTop;
								Foul_pushball += 1;
								return 1;
							}
						}
					}
				}
			}
			if (tuiqiu1 || tuiqiu3)
			{
				for (int i = 0; i < 5; i++)
				{
					if (pEnv->opponent[i].pos.y >= 172)
					{
						if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
						{
							facetoface = true;
							pushball += 1;
							if (pushball >= nFaceCycles)
							{
								if (pEnv->currentBall.pos.x <= 110)
								{
									statespace.gameState = PM_FreeBall_LeftTop;
									pushball = 0;
									return 1;
								}
								else
								{
									statespace.gameState = PM_FreeBall_RightTop;
									pushball = 0;
									return 3;
								}
							}
						}
					}
				}
				if (facetoface == false)
				{
					pushball = 0;
				}
			}
			else
			{
				pushball = 0;
			}


			for (int i = 0; i < 5; i++)
			{
				if (pEnv->opponent[i].pos.x > pEnv->currentBall.pos.x  && pEnv->opponent[i].pos.y >= 172)
				{
					if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu2 = true;
						break;
					}
				}
			}
			if (tuiqiu2)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->opponent[i].pos.y >= 172)
						{
							if (Judge_Collision(statespace.opponent[i], statespace.opponent[robot]))
							{
								statespace.gameState = PM_FreeBall_RightTop;
								return 3;
							}
						}
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				if (pEnv->home[i].pos.x < pEnv->currentBall.pos.x &&  pEnv->home[i].pos.y >= 172)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						tuiqiu3 = true;
					}
				}
				if (pEnv->home[i].pos.x > pEnv->currentBall.pos.x &&  pEnv->home[i].pos.y >= 172)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu1 = true;
						break;
					}
				}
			}
			if (tuiqiu1)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->home[i].pos.y >= 172)
						{
							if (Judge_Collision(statespace.home[i], statespace.home[robot]))
							{
								statespace.gameState = PM_FreeBall_RightTop;
								Foul_pushball += 1;
								return 3;
							}
						}
					}
				}
			}
			if (tuiqiu1 || tuiqiu3)
			{
				for (int i = 0; i < 5; i++)
				{
					if (pEnv->opponent[i].pos.y >= 172)
					{
						if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
						{
							facetoface = true;
							pushball += 1;
							if (pushball >= nFaceCycles)
							{
								if (pEnv->currentBall.pos.x <= 110)
								{
									statespace.gameState = PM_FreeBall_LeftTop;
									pushball = 0;
									return 1;
								}
								else
								{
									statespace.gameState = PM_FreeBall_RightTop;
									pushball = 0;
									return 3;
								}
							}
						}
					}
				}
				if (facetoface == false)
				{
					pushball = 0;
				}
			}
			else
			{
				pushball = 0;
			}

			for (int i = 0; i < 5; i++)
			{
				if (pEnv->opponent[i].pos.x < pEnv->currentBall.pos.x  && pEnv->opponent[i].pos.y >= 172)
				{
					if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu2 = true;
						break;
					}
				}
			}
			if (tuiqiu2)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->opponent[i].pos.y >= 172)
						{
							if (Judge_Collision(statespace.opponent[i], statespace.opponent[robot]))
							{
								statespace.gameState = PM_FreeBall_LeftTop;
								return 1;
							}
						}
					}
				}
			}
		}
	}

	if (pEnv->currentBall.pos.y <= 8)
	{
		if (duiwu == 2)
		{
			for (int i = 0; i < 5; i++)
			{
				if (pEnv->home[i].pos.x > pEnv->currentBall.pos.x && pEnv->home[i].pos.y <= 8)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						tuiqiu3 = true;
					}
				}
				if (pEnv->home[i].pos.x < pEnv->currentBall.pos.x && pEnv->home[i].pos.y <= 8)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu1 = true;
						break;
					}
				}
			}
			if (tuiqiu1)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->home[i].pos.y <= 8)
						{
							if (Judge_Collision(statespace.home[i], statespace.home[robot]))
							{
								statespace.gameState = PM_FreeBall_LeftBot;
								Foul_pushball += 1;
								return 2;
							}
						}
					}
				}
			}
			if (tuiqiu1 || tuiqiu3)
			{
				for (int i = 0; i < 5; i++)
				{
					if (pEnv->opponent[i].pos.y <= 8)
					{
						if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
						{
							facetoface = true;
							pushball += 1;
							if (pushball >= nFaceCycles)
							{
								if (pEnv->currentBall.pos.x <= 110)
								{
									statespace.gameState = PM_FreeBall_LeftBot;
									pushball = 0;
									return 2;
								}
								else
								{
									statespace.gameState = PM_FreeBall_RightBot;
									pushball = 0;
									return 4;
								}
							}
						}
					}
				}
				if (facetoface == false)
				{
					pushball = 0;
				}
			}
			else
			{
				pushball = 0;
			}

			for (int i = 0; i < 5; i++)
			{
				if (pEnv->opponent[i].pos.x > pEnv->currentBall.pos.x  && pEnv->opponent[i].pos.y <= 8)
				{
					if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu2 = true;
						break;
					}
				}
			}
			if (tuiqiu2)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->opponent[i].pos.y <= 8)
						{
							if (Judge_Collision(statespace.opponent[i], statespace.opponent[robot]))
							{
								statespace.gameState = PM_FreeBall_RightBot;
								return 4;
							}
						}
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				if (pEnv->home[i].pos.x < pEnv->currentBall.pos.x &&  pEnv->home[i].pos.y <= 8)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						tuiqiu3 = true;
					}
				}
				if (pEnv->home[i].pos.x > pEnv->currentBall.pos.x &&  pEnv->home[i].pos.y <= 8)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu1 = true;
						break;
					}
				}
			}
			if (tuiqiu1)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->home[i].pos.y <= 8)
						{
							if (Judge_Collision(statespace.home[i], statespace.home[robot]))
							{
								statespace.gameState = PM_FreeBall_LeftBot;
								Foul_pushball += 1;
								return 2;
							}
						}
					}
				}
			}
			if (tuiqiu1 || tuiqiu3)
			{
				for (int i = 0; i < 5; i++)
				{
					if (pEnv->opponent[i].pos.y <= 8)
					{
						if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
						{
							facetoface = true;
							pushball += 1;
							if (pushball >= nFaceCycles)
							{
								if (pEnv->currentBall.pos.x <= 110)
								{
									statespace.gameState = PM_FreeBall_LeftBot;
									pushball = 0;
									return 2;
								}
								else
								{
									statespace.gameState = PM_FreeBall_RightBot;
									pushball = 0;
									return 4;
								}
							}
						}
					}
				}
				if (facetoface == false)
				{
					pushball = 0;
				}
			}
			else
			{
				pushball = 0;
			}


			for (int i = 0; i < 5; i++)
			{
				if (pEnv->opponent[i].pos.x < pEnv->currentBall.pos.x  && pEnv->opponent[i].pos.y <= 8)
				{
					if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu2 = true;
						break;
					}
				}
			}
			if (tuiqiu2)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->opponent[i].pos.y <= 8)
						{
							if (Judge_Collision(statespace.opponent[i], statespace.opponent[robot]))
							{
								statespace.gameState = PM_FreeBall_LeftBot;
								return 2;
							}
						}
					}
				}
			}
		}
	}

	if (pEnv->currentBall.pos.x >= 212 && pEnv->currentBall.pos.y <= 70)
	{
		if (duiwu == 2)
		{
			for (int i = 0; i < 5; i++)
			{
				if (pEnv->home[i].pos.y > pEnv->currentBall.pos.y && pEnv->home[i].pos.x >= 212 && pEnv->home[i].pos.y <= 70)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						tuiqiu3 = true;
					}
				}
				if (pEnv->home[i].pos.y < pEnv->currentBall.pos.y && pEnv->home[i].pos.x >= 212 && pEnv->home[i].pos.y <= 70)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu1 = true;
						break;
					}
				}
			}
			if (tuiqiu1)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->home[i].pos.x >= 212 && pEnv->home[i].pos.y <= 70)
						{
							if (Judge_Collision(statespace.home[i], statespace.home[robot]))
							{
								statespace.gameState = PM_FreeBall_LeftBot;
								Foul_pushball += 1;
								return 2;
							}
						}
					}
				}
			}
			if (tuiqiu1 || tuiqiu3)
			{
				for (int i = 0; i < 5; i++)
				{
					if (pEnv->opponent[i].pos.x >= 212 && pEnv->opponent[i].pos.y <= 70)
					{
						if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
						{
							facetoface = true;
							pushball += 1;
							if (pushball >= nFaceCycles)
							{
								statespace.gameState = PM_FreeBall_RightBot;
								pushball = 0;
								return 4;
							}
						}
					}
				}
				if (facetoface == false)
				{
					pushball = 0;
				}
			}
			else
			{
				pushball = 0;
			}

			for (int i = 0; i < 5; i++)
			{
				if (pEnv->opponent[i].pos.y > pEnv->currentBall.pos.y && pEnv->opponent[i].pos.x <= 8 && pEnv->opponent[i].pos.y <= 70)
				{
					if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu2 = true;
						break;
					}
				}
			}
			if (tuiqiu2)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->opponent[i].pos.x >= 212 && pEnv->opponent[i].pos.y <= 70)
						{
							if (Judge_Collision(statespace.opponent[i], statespace.opponent[robot]))
							{
								statespace.gameState = PM_FreeBall_RightBot;
								return 4;
							}
						}
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				if (pEnv->home[i].pos.y < pEnv->currentBall.pos.y && pEnv->home[i].pos.x >= 212 && pEnv->home[i].pos.y <= 70)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						tuiqiu3 = true;
					}
				}
				if (pEnv->home[i].pos.y > pEnv->currentBall.pos.y && pEnv->home[i].pos.x >= 212 && pEnv->home[i].pos.y <= 70)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu1 = true;
						break;
					}
				}
			}
			if (tuiqiu1)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->home[i].pos.x >= 212 && pEnv->home[i].pos.y <= 70)
						{
							if (Judge_Collision(statespace.home[i], statespace.home[robot]))
							{
								statespace.gameState = PM_FreeBall_RightBot;
								Foul_pushball += 1;
								return 4;
							}
						}
					}
				}
			}
			if (tuiqiu1 || tuiqiu3)
			{
				for (int i = 0; i < 5; i++)
				{
					if (pEnv->opponent[i].pos.x >= 212 && pEnv->opponent[i].pos.y <= 70)
					{
						facetoface = true;
						if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
						{
							pushball += 1;
							if (pushball >= nFaceCycles)
							{
								statespace.gameState = PM_FreeBall_RightBot;
								pushball = 0;
								return 4;
							}
						}
					}
				}
				if (facetoface == false)
				{
					pushball = 0;
				}
			}
			else
			{
				pushball = 0;
			}


			for (int i = 0; i < 5; i++)
			{
				if (pEnv->opponent[i].pos.y < pEnv->currentBall.pos.y && pEnv->opponent[i].pos.x >= 212 && pEnv->opponent[i].pos.y <= 70)
				{
					if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu2 = true;
						break;
					}
				}
			}
			if (tuiqiu2)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->opponent[i].pos.x >= 212 && pEnv->opponent[i].pos.y <= 70)
						{
							if (Judge_Collision(statespace.opponent[i], statespace.opponent[robot]))
							{
								statespace.gameState = PM_FreeBall_LeftBot;
								return 2;
							}
						}
					}
				}
			}
		}
	}

	if (pEnv->currentBall.pos.x >= 212 && pEnv->currentBall.pos.y >= 110)
	{
		if (duiwu == 2)
		{
			for (int i = 0; i < 5; i++)
			{
				if (pEnv->home[i].pos.y < pEnv->currentBall.pos.y && pEnv->home[i].pos.x >= 212 && pEnv->home[i].pos.y >= 110)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						tuiqiu3 = true;
					}
				}
				if (pEnv->home[i].pos.y > pEnv->currentBall.pos.y && pEnv->home[i].pos.x >= 212 && pEnv->home[i].pos.y >= 110)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu1 = true;
						break;
					}
				}
			}
			if (tuiqiu1)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->home[i].pos.x >= 212 && pEnv->home[i].pos.y >= 110)
						{
							if (Judge_Collision(statespace.home[i], statespace.home[robot]))
							{
								statespace.gameState = PM_FreeBall_LeftTop;
								Foul_pushball += 1;
								return 1;
							}
						}
					}
				}
			}
			if (tuiqiu1 || tuiqiu3)
			{
				for (int i = 0; i < 5; i++)
				{
					if (pEnv->opponent[i].pos.x >= 212 && pEnv->opponent[i].pos.y >= 110)
					{
						if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
						{
							facetoface = true;
							pushball += 1;
							if (pushball >= nFaceCycles)
							{
								statespace.gameState = PM_FreeBall_RightTop;
								pushball = 0;
								return 3;
							}
						}
					}
				}
				if (facetoface == false)
				{
					pushball = 0;
				}
			}
			else
			{
				pushball = 0;
			}

			for (int i = 0; i < 5; i++)
			{
				if (pEnv->opponent[i].pos.y < pEnv->currentBall.pos.y && pEnv->opponent[i].pos.x >= 212 && pEnv->opponent[i].pos.y >= 110)
				{
					if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu2 = true;
						break;
					}
				}
			}
			if (tuiqiu2)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->opponent[i].pos.x >= 212 && pEnv->opponent[i].pos.y >= 110)
						{
							if (Judge_Collision(statespace.opponent[i], statespace.opponent[robot]))
							{
								statespace.gameState = PM_FreeBall_RightTop;
								return 3;
							}
						}
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				if (pEnv->home[i].pos.y > pEnv->currentBall.pos.y && pEnv->home[i].pos.x >= 212 && pEnv->home[i].pos.y <= 110)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						tuiqiu3 = true;
					}
				}
				if (pEnv->home[i].pos.y < pEnv->currentBall.pos.y && pEnv->home[i].pos.x >= 212 && pEnv->home[i].pos.y <= 110)
				{
					if (getLength(pEnv->home[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu1 = true;
						break;
					}
				}
			}
			if (tuiqiu1)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->home[i].pos.x >= 212 && pEnv->home[i].pos.y >= 110)
						{
							if (Judge_Collision(statespace.home[i], statespace.home[robot]))
							{
								statespace.gameState = PM_FreeBall_RightTop;
								Foul_pushball += 1;
								return 3;
							}
						}
					}
				}
			}
			if (tuiqiu1 || tuiqiu3)
			{
				for (int i = 0; i < 5; i++)
				{
					if (pEnv->opponent[i].pos.x >= 212 && pEnv->opponent[i].pos.y >= 110)
					{
						if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
						{
							facetoface = true;
							pushball += 1;
							if (pushball >= nFaceCycles)
							{
								statespace.gameState = PM_FreeBall_RightTop;
								pushball = 0;
								return 3;
							}
						}
					}
				}
				if (facetoface == false)
				{
					pushball = 0;
				}
			}
			else
			{
				pushball = 0;
			}

			for (int i = 0; i < 5; i++)
			{
				if (pEnv->opponent[i].pos.y > pEnv->currentBall.pos.y && pEnv->opponent[i].pos.x >= 212 && pEnv->opponent[i].pos.y >= 110)
				{
					if (getLength(pEnv->opponent[i].pos, pEnv->currentBall.pos) < 6.69)
					{
						robot = i;
						tuiqiu2 = true;
						break;
					}
				}
			}
			if (tuiqiu2)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i == robot)
					{
						continue;
					}
					else
					{
						if (pEnv->opponent[i].pos.x >= 212 && pEnv->opponent[i].pos.y >= 110)
						{
							if (Judge_Collision(statespace.opponent[i], statespace.opponent[robot]))
							{
								statespace.gameState = PM_FreeBall_LeftTop;
								return 1;
							}
						}
					}
				}
			}
		}
	}

	if (getLength(pEnv->currentBall.pos, pEnv->lastBall.pos) > 0.5)
	{
		ballslow = 0;
		statespace.gameState = PM_PlayOn;
		return 0;
	}
	else
	{
		ballslow = ballslow + 1;
		if (ballslow >= nSlowCycles)
		{
			if (pEnv->currentBall.pos.x <= 15 && (pEnv->currentBall.pos.y >= 65 && pEnv->currentBall.pos.y <= 115))
			{
				ballslow = 0;
				statespace.gameState = PM_GoalKick_Yellow;
				return 11;
			}
			else if (pEnv->currentBall.pos.x >= 205 && (pEnv->currentBall.pos.y >= 65 && pEnv->currentBall.pos.y <= 115))
			{
				ballslow = 0;
				statespace.gameState = PM_GoalKick_Blue;
				return 12;
			}
			else
			{
				if (pEnv->currentBall.pos.x <= 110 && pEnv->currentBall.pos.y >= 90)
				{
					ballslow = 0;
					statespace.gameState = PM_FreeBall_LeftTop;
					return 1;
				}
				if (pEnv->currentBall.pos.x <= 110 && pEnv->currentBall.pos.y < 90)
				{
					ballslow = 0;
					statespace.gameState = PM_FreeBall_LeftBot;
					return 2;
				}
				if (pEnv->currentBall.pos.x > 110 && pEnv->currentBall.pos.y >= 90)
				{
					ballslow = 0;
					statespace.gameState = PM_FreeBall_RightTop;
					return 3;
				}
				if (pEnv->currentBall.pos.x > 110 && pEnv->currentBall.pos.y < 90)
				{
					ballslow = 0;
					statespace.gameState = PM_FreeBall_RightBot;
					return 4;
				}
			}
		}
	}
	return 0;
}


int Team::Judge_FREE_KICK(Environment *pEnv)
{
	return 0;
}
