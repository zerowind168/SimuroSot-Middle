/*! @file
********************************************************************************
<PRE>
Module			 : Basic structures and class Team for referee.
File			 : Referee.h
Relevent File(s) : Referee.cpp
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

*******************************************************************************/

#include "stdafx.h"

const double PI = 3.14159265357989;

#pragma comment(lib,"Referee.lib")

enum TeamColor { BLUE_TEAM = 1, YELLOW_TEAM };


enum PlayMode {
	PM_PlayOn = 0,           //  
	PM_FreeBall_LeftTop,     //   1
	PM_FreeBall_LeftBot,     //   2 
	PM_FreeBall_RightTop,    //   3
	PM_FreeBall_RightBot,    //   4
	PM_PlaceKick_Yellow,     //   5
	PM_PlaceKick_Blue,       //   6
	PM_PenaltyKick_Yellow,   //   7
	PM_PenaltyKick_Blue,     //   8
	PM_FreeKick_Yellow,      //   9
	PM_FreeKick_Blue,        //   10
	PM_GoalKick_Yellow,      //   11
	PM_GoalKick_Blue         //   12
};


struct RefRobot
{
	Vector3D pos;
	double rotation;
	Vector3D vertex[4];
};


struct StateSpace
{
	Robot home[PLAYERS_PER_SIDE];
	Robot opponent[PLAYERS_PER_SIDE];
	Ball currentBall;
	PlayMode gameState;
	int pastTime;
	int pushball;          
	bool bNew;
	int nNewCount;

	StateSpace()
	{
		pastTime = 0;
		bNew = false;
		nNewCount = 0;
	}
};


struct ReferData
{
	int xianbai;
	Robot Posxianbai[5];
	Robot Poshoubai[5];
	Vector3D Posball;
	PlayMode gameState;
	char blueTeamName[50];
	char yellowTeamName[50];
};


class STRATEGY_API Team{
public:
	StateSpace statespace;
	TeamColor duiwu;      
	bool xianbai;         
	bool houbai;          
	int ballslow;         
	int pushball;         
	int Foul_pushball;    
	void Judge_duiwu(Environment *pEnv);
	int Judge_PENALTY_KICK(Environment *pEnv);		  
	int Judge_GOAL_KICK1(Environment *pEnv);          
	int Judge_GOAL_KICK2(Environment *pEnv);          
	int Judge_PLACE_KICK(Environment *pEnv);          
	int Judge_FREE_BALL(Environment *pEnv);           
	int Judge_FREE_KICK(Environment *pEnv);			  
	bool Set_PLACE_KICK(int PLACE_KICK);
	bool Set_GOAL_KICK(int GOAL_KICK1);
	bool Set_PENALTY_KICK(int PENALTY_KICK);
	bool Set_FREE_BALL(int FREE_BALL);

	Team()
	{						  
		ballslow = 0;         
		pushball = 0;         
		Foul_pushball = 0;    

		//home			  
		recordtime1 = 0;    
		recordtime2 = 0;    
		recordtime3 = 0;    
		recordtime4 = 0;    
		recordrobot = 0;    
		recordzong = 0;     
		recordrobot3 = 0;   
		recordrobot4 = 0;   
		recordzong4 = 0;    

		//opponent
		op_recordtime1 = 0;    
		op_recordtime2 = 0;    
		op_recordtime3 = 0;    
		op_recordtime4 = 0;    
		op_recordrobot = 0;    
		op_recordzong = 0;     
		op_recordrobot3 = 0;   
		op_recordrobot4 = 0;   
		op_recordzong4 = 0;    
	}

private:
	//home
	int recordtime1;    
	int recordtime2;    
	int recordtime3;    
	int recordtime4;    
	int recordrobot;    
	int recordzong;     
	int recordrobot3;   
	int recordrobot4;   
	int recordzong4;    
					    
	//opponent
	int op_recordtime1;    
	int op_recordtime2;    
	int op_recordtime3;    
	int op_recordtime4;    
	int op_recordrobot;    
	int op_recordzong;     
	int op_recordrobot3;   
	int op_recordrobot4;   
	int op_recordzong4;    
};


