/*! @file
********************************************************************************
<PRE>
Module			 : Implementation of referee logics, strategy agency.
File			 : Team2.cpp
Relevent File(s) : Team2.h, Referee.h
Function(s)      : The automatic referee and strategy agency for FIRA MiroSot/SimuroSot.
Author(s)        : Le Li, Linquan Yang
Version          : 0.2
--------------------------------------------------------------------------------
Remarks           : -
--------------------------------------------------------------------------------
Modifications : 
Date          Version           Modifier				  Content
2018/03/06      0.1             Le Li, Dr.YANG             Create
2018/06/12      0.2             Le Li, Dr.YANG             Modify
</PRE>
******************************************************************************** 

* Copyright(c) 2018-, Linquan Yang, All rights reserved. 
* Contact:	yanglinquan@126.com
* China University of Geosciences.
*******************************************************************************/
// Team2.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Team2.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#include "Referee.h"

using namespace std;

#pragma comment(lib,"Referee.lib")
#pragma comment(lib,"Strategy4Yellow.lib")


STRATEGY_API void SetYellowTeamName(char* teamName);
STRATEGY_API void SetFormerRobots(PlayMode gameState, Robot robots[]);
STRATEGY_API void SetLaterRobots(PlayMode gameState, Robot formerRobots[], Vector3D ball, Robot laterRobots[]);
STRATEGY_API void SetBall(PlayMode gameState, Vector3D * pBall); 
STRATEGY_API void RunStrategy(Environment *pEnv);

STRATEGY_API Team team2;
STRATEGY_API PlayMode gamestate;		 
STRATEGY_API Robot Posxianbai[5];        
STRATEGY_API Robot Copy_Posxianbai[5];   
STRATEGY_API Robot Poshoubai[5];         
STRATEGY_API Vector3D Posball;           
STRATEGY_API Vector3D Copy_Posball;      
STRATEGY_API char strBlueName[50];		 
STRATEGY_API char strYellowName[50];

STRATEGY_API void CheckPosxianbai(Robot Posxianbai[], PlayMode gameState);
STRATEGY_API void CheckPoshoubai(Robot Poshoubai[], PlayMode gameState);
STRATEGY_API void CheckPosBall(Vector3D &Posball, PlayMode gameState);
STRATEGY_API void BaiQiu(Vector3D &Posball, PlayMode gameState);

void ChangeSystem(Environment* pEnv);

// #############################################################################################
// #############################################################################################

extern "C" TEAM2_API void Create ( Environment *pEnv )
{

	// allocate user data and assign to pEnv->userData
	// eg. pEnv->userData = ( void * ) new MyVariables ();
}

extern "C" TEAM2_API void Destroy ( Environment *pEnv )
{

	// free any user data created in Create ( Environment * )

	// eg. if ( pEnv->userData != NULL ) delete ( MyVariables * ) pEnv->userData;
}

extern "C" TEAM2_API void Strategy ( Environment *pEnv )
{
	ChangeSystem(pEnv);
	if (team2.Foul_pushball >=4)
		MessageBox(NULL, "The Yellow team has violated the nopushing rule for four times!", "Yellow", MB_OK); 

	if (team2.statespace.pastTime == 0)
	{
		team2.Judge_duiwu(pEnv);
		if (team2.duiwu == BLUE_TEAM)
		{
			team2.statespace.gameState = PM_PlaceKick_Blue;
			team2.statespace.bNew = true;
			team2.statespace.nNewCount = 0;
			team2.xianbai = true;
		}
		if (team2.duiwu == YELLOW_TEAM)
		{
			team2.statespace.gameState = PM_PlaceKick_Blue;
			team2.statespace.bNew = true;
			team2.statespace.nNewCount = 0;
			team2.houbai = true;
			SetYellowTeamName(strYellowName);
		}
	}
	team2.statespace.pastTime = team2.statespace.pastTime + 1;

	bool Judge = true;
	if (team2.statespace.bNew)
	{
		team2.ballslow = 0;
		team2.statespace.nNewCount = team2.statespace.nNewCount + 1;
		if (team2.statespace.nNewCount == 1 && team2.houbai)
		{
			Judge = false;
		}
		else if (team2.statespace.nNewCount == 2 && team2.houbai)
		{
			gamestate = team2.statespace.gameState;
			SetLaterRobots(gamestate, Copy_Posxianbai, Copy_Posball, Poshoubai);
			CheckPoshoubai(Poshoubai, team2.statespace.gameState);                  
			team2.statespace.bNew = false;
			team2.statespace.nNewCount = 0;
			team2.houbai = false;
			Judge = false;

			ReferData  rData;
			rData.Posball = Posball;
			for (int i = 0; i < 5; i++)
			{
				rData.Posxianbai[i] = Posxianbai[i];			
				rData.Poshoubai[i] = Poshoubai[i];
			}			

			if (team2.duiwu == 1)
				rData.xianbai = 2;
			else
				rData.xianbai = 1;

			rData.gameState = team2.statespace.gameState;
			strcpy(rData.blueTeamName, strBlueName);
			strcpy(rData.yellowTeamName, strYellowName);

			const char szDlgTitle[] = "SimuroSot5";
			HWND hRecvWindow = ::FindWindow(NULL, szDlgTitle);
			REFERDATA data;
			data.dwData = 0;
			data.cbData = sizeof(ReferData);
			data.lpData = &rData;
			::SendMessage(hRecvWindow, 0x004a, (WPARAM)data.cbData, (LPARAM)&data);
		}
		else if (team2.statespace.nNewCount == 1 && team2.xianbai)
		{
			gamestate = team2.statespace.gameState; 
			SetFormerRobots(gamestate, Posxianbai);
			PlayMode gamestate = team2.statespace.gameState;
			if (team2.statespace.gameState == 11 || team2.statespace.gameState == 12)
			{ 
				SetBall(gamestate, &Posball);
				CheckPosBall(Posball, team2.statespace.gameState);                          
			}
			else
			{
				BaiQiu(Posball, team2.statespace.gameState);                                
			}
			CheckPosxianbai(Posxianbai, team2.statespace.gameState);                         
			for (int i = 0; i < 5; i++)
			{
				Copy_Posxianbai[i] = Posxianbai[i];
			}
			Copy_Posball = Posball;
			team2.xianbai = false;
			Judge = false;
		}
		else
		{
			team2.statespace.bNew = false;
			team2.statespace.nNewCount = 0;
			Judge = false;
		}
	}
	else
	{
		team2.statespace.gameState = PM_PlayOn;
		int PLACE_KICK = team2.Judge_PLACE_KICK(pEnv);
		if (PLACE_KICK)
		{
			if (team2.Set_PLACE_KICK(PLACE_KICK))
			{
				team2.statespace.bNew = true;
				team2.statespace.nNewCount = 0;
				team2.xianbai = true;
				Judge = false;
			}
			else
			{
				team2.statespace.bNew = true;
				team2.statespace.nNewCount = 0;
				team2.houbai = true;
				Judge = false;
			}
		}
		if (Judge)
		{
			int GOAL_KICK1 = team2.Judge_GOAL_KICK1(pEnv);        
			if (GOAL_KICK1)
			{
				if (team2.Set_GOAL_KICK(GOAL_KICK1))
				{
					team2.statespace.bNew = true;
					team2.statespace.nNewCount = 0;
					team2.xianbai = true;
					Judge = false;
				}
				else
				{
					team2.statespace.bNew = true;
					team2.statespace.nNewCount = 0;
					team2.houbai = true;
					Judge = false;
				}
			}
		}
		if (Judge)
		{
			int PENALTY_KICK = team2.Judge_PENALTY_KICK(pEnv);
			if (PENALTY_KICK)
			{
				if (team2.Set_PENALTY_KICK(PENALTY_KICK))
				{
					team2.statespace.bNew = true;
					team2.statespace.nNewCount = 0;
					team2.xianbai = true;
					Judge = false;
				}
				else
				{
					team2.statespace.bNew = true;
					team2.statespace.nNewCount = 0;
					team2.houbai = true;
					Judge = false;
				}
			}
		}
		if(Judge)
		{
			int GOAL_KICK2 = team2.Judge_GOAL_KICK2(pEnv);
			if (GOAL_KICK2)
			{
				if (team2.Set_GOAL_KICK(GOAL_KICK2))
				{
					team2.statespace.bNew = true;
					team2.statespace.nNewCount = 0;
					team2.xianbai = true;
					Judge = false;
				}
				else
				{
					team2.statespace.bNew = true;
					team2.statespace.nNewCount = 0;
					team2.houbai = true;
					Judge = false;
				}
			}
		}
		if(Judge)
		{
			int FREE_BALL = team2.Judge_FREE_BALL(pEnv);
			if (FREE_BALL)
			{
				if (team2.Set_FREE_BALL(FREE_BALL))
				{
					team2.statespace.bNew = true;
					team2.statespace.nNewCount = 0;
					team2.xianbai = true;
					Judge = false;
				}
				else
				{
					team2.statespace.bNew = true;
					team2.statespace.nNewCount = 0;
					team2.houbai = true;
					Judge = false;
				}
			}
		}
		if (Judge)
		{
			int FREE_KICK = team2.Judge_FREE_KICK(pEnv);
		}
		if (Judge)                                           
		{
			RunStrategy(pEnv);                        //Playon
		}
	}

	pEnv->lastBall = pEnv->currentBall;
}

// #############################################################################################
// #############################################################################################

void ChangeSystem(Environment* pEnv)
{
	// ball
	pEnv->currentBall.pos.x = (pEnv->currentBall.pos.x - FLEFTX) * 2.54;
	pEnv->currentBall.pos.y = (pEnv->currentBall.pos.y - FBOT) * 2.54;

	pEnv->lastBall.pos.x = (pEnv->lastBall.pos.x - FLEFTX) * 2.54;
	pEnv->lastBall.pos.y = (pEnv->lastBall.pos.y - FBOT) * 2.54;

	for (int i=0; i<5; i++)
	{
		// home robots
		pEnv->home[i].pos.x = (pEnv->home[i].pos.x - FLEFTX) * 2.54;
		pEnv->home[i].pos.y = (pEnv->home[i].pos.y - FBOT) * 2.54;

		// opponent robots
		pEnv->opponent[i].pos.x = (pEnv->opponent[i].pos.x - FLEFTX) * 2.54 ;
		pEnv->opponent[i].pos.y = (pEnv->opponent[i].pos.y - FBOT) * 2.54;
	}
}

