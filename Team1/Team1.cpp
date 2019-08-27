/*! @file
********************************************************************************
<PRE>
Module			 : Implementation of referee logics, strategy agency and logging.
File			 : Team1.cpp
Relevent File(s) : Team1.h, Referee.h
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
// Team1.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Team1.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#include "Referee.h"

using namespace std;

#pragma comment(lib,"Referee.lib")
#pragma comment(lib,"Strategy4Blue.lib")

STRATEGY_API void SetBlueTeamName(char* teamName);
STRATEGY_API void SetFormerRobots(PlayMode gameState, Robot robots[]);
STRATEGY_API void SetLaterRobots(PlayMode gameState, Robot formerRobots[], Vector3D ball, Robot laterRobots[]);
STRATEGY_API void SetBall(PlayMode gameState, Vector3D * pBall); 
STRATEGY_API void RunStrategy(Environment *pEnv);

STRATEGY_API Team team1;
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
STRATEGY_API void CheckPoshoubai(Robot Posxianbai[5], Robot Poshoubai[5], PlayMode gameState);
STRATEGY_API void CheckPosBall(Vector3D &Posball, PlayMode gameState);
STRATEGY_API void BaiQiu(Vector3D &Posball, PlayMode gameState);

ofstream fout;
void ChangeSystem(Environment* pEnv);
void Environment2Log(const Environment* pEnv, LogEnvironment* pLogEnv);
string Int2String(int n);
string ST2String(SYSTEMTIME st);
void WriteLog(const Environment* pEnv);
// #############################################################################################
// #############################################################################################

extern "C" TEAM1_API void Create ( Environment *pEnv )
{
	// allocate user data and assign to pEnv->userData
	// eg. pEnv->userData = ( void * ) new MyVariables ();
}

extern "C" TEAM1_API void Destroy ( Environment *pEnv )
{
	// free any user data created in Create ( Environment * )

	// eg. if ( pEnv->userData != NULL ) delete ( MyVariables * ) pEnv->userData;
	if (fout.is_open())		fout.close();
}

extern "C" TEAM1_API void Strategy ( Environment *pEnv )
{
	ChangeSystem(pEnv);
	Environment oEnv = *pEnv;
	if (team1.Foul_pushball >=4)
		MessageBox(NULL, "The Blue team has violated the nopushing rule for four times!", "Blue", MB_OK); 

	if (team1.statespace.pastTime == 0)
	{		
		team1.Judge_duiwu(pEnv);
		if (team1.duiwu == BLUE_TEAM)
		{
			team1.statespace.gameState = PM_PlaceKick_Blue;
			team1.statespace.bNew = true;
			team1.statespace.nNewCount = 0;
			team1.xianbai = true;
			SetBlueTeamName(strBlueName);
		}
		if (team1.duiwu == YELLOW_TEAM)
		{
			team1.statespace.gameState = PM_PlaceKick_Blue;
			team1.statespace.bNew = true;
			team1.statespace.nNewCount = 0;
			team1.houbai = true;
		}
	}
	team1.statespace.pastTime = team1.statespace.pastTime + 1;

	bool Judge = true;
	if (team1.statespace.bNew)
	{
		team1.ballslow = 0;
		team1.statespace.nNewCount = team1.statespace.nNewCount + 1;
		if (team1.statespace.nNewCount == 1 && team1.houbai)
		{
			Judge = false;
		}
		else if (team1.statespace.nNewCount == 2 && team1.houbai)
		{
			gamestate = team1.statespace.gameState;
			SetLaterRobots(gamestate, Copy_Posxianbai, Copy_Posball, Poshoubai);
			CheckPoshoubai(Posxianbai, Poshoubai, team1.statespace.gameState);
			team1.statespace.bNew = false;
			team1.statespace.nNewCount = 0;
			team1.houbai = false;
			Judge = false;
			
			ReferData  rData;
			rData.Posball = Posball;
			for (int i = 0; i < 5; i++)
			{
				rData.Posxianbai[i] = Posxianbai[i];
				rData.Poshoubai[i] = Poshoubai[i];
			}	

			if (team1.duiwu == 1)
				rData.xianbai = 2;
			else
				rData.xianbai = 1;

			rData.gameState = team1.statespace.gameState;
			strcpy(rData.blueTeamName, strBlueName);
			strcpy(rData.yellowTeamName, strYellowName);

			const char szDlgTitle[] = "SimuroSot5";
			HWND hRecvWindow = ::FindWindow(NULL, szDlgTitle);	
			SENDREFER data;					
			data.dwData = 0;
			data.cbData = sizeof(ReferData);
			data.lpData = &rData;			
			::SendMessage(hRecvWindow, 0x004a, (WPARAM)data.cbData, (LPARAM)&data);
		}
		else if (team1.statespace.nNewCount == 1 && team1.xianbai)
		{
			gamestate = team1.statespace.gameState;
			SetFormerRobots(gamestate, Posxianbai);
			PlayMode gamestate = team1.statespace.gameState;
			if (team1.statespace.gameState == 11 || team1.statespace.gameState == 12)
			{
				SetBall(gamestate, &Posball);
				CheckPosBall(Posball, team1.statespace.gameState);                         
			}
			else
			{
				BaiQiu(Posball, team1.statespace.gameState);                                
			}
			CheckPosxianbai(Posxianbai, team1.statespace.gameState);                         
			for (int i = 0; i < 5; i++)
			{
				Copy_Posxianbai[i] = Posxianbai[i];
			}
			Copy_Posball = Posball;
			team1.xianbai = false;
			Judge = false;
		}
		else
		{
			team1.statespace.bNew = false;
			team1.statespace.nNewCount = 0;
			Judge = false;
		}
	}
	else
	{
		team1.statespace.gameState = PM_PlayOn;
		int PLACE_KICK = team1.Judge_PLACE_KICK(pEnv);
		if (PLACE_KICK)
		{
			if (team1.Set_PLACE_KICK(PLACE_KICK))
			{
				team1.statespace.bNew = true;
				team1.statespace.nNewCount = 0;
				team1.xianbai = true;
				Judge = false;
			}
			else
			{
				team1.statespace.bNew = true;
				team1.statespace.nNewCount = 0;
				team1.houbai = true;
				Judge = false;
			}
		}
		if (Judge)
		{
			int GOAL_KICK1 = team1.Judge_GOAL_KICK1(pEnv);       
			if (GOAL_KICK1)
			{
				if (team1.Set_GOAL_KICK(GOAL_KICK1))
				{
					team1.statespace.bNew = true;
					team1.statespace.nNewCount = 0;
					team1.xianbai = true;
					Judge = false;
				}
				else
				{
					team1.statespace.bNew = true;
					team1.statespace.nNewCount = 0;
					team1.houbai = true;
					Judge = false;
				}
			}
		}
		if (Judge)
		{
			int PENALTY_KICK = team1.Judge_PENALTY_KICK(pEnv);
			if (PENALTY_KICK)
			{
				if (team1.Set_PENALTY_KICK(PENALTY_KICK))
				{
					team1.statespace.bNew = true;
					team1.statespace.nNewCount = 0;
					team1.xianbai = true;
					Judge = false;
				}
				else
				{
					team1.statespace.bNew = true;
					team1.statespace.nNewCount = 0;
					team1.houbai = true;
					Judge = false;
				}
			}
		}
		if(Judge)
		{
			int GOAL_KICK2 = team1.Judge_GOAL_KICK2(pEnv);
			if (GOAL_KICK2)
			{
				if (team1.Set_GOAL_KICK(GOAL_KICK2))
				{
					team1.statespace.bNew = true;
					team1.statespace.nNewCount = 0;
					team1.xianbai = true;
					Judge = false;
				}
				else
				{
					team1.statespace.bNew = true;
					team1.statespace.nNewCount = 0;
					team1.houbai = true;
					Judge = false;
				}
			}
		}
		if(Judge)
		{
			int FREE_BALL = team1.Judge_FREE_BALL(pEnv);
			if (FREE_BALL)
			{
				if (team1.Set_FREE_BALL(FREE_BALL))
				{
					team1.statespace.bNew = true;
					team1.statespace.nNewCount = 0;
					team1.xianbai = true;
					Judge = false;
				}
				else
				{
					team1.statespace.bNew = true;
					team1.statespace.nNewCount = 0;
					team1.houbai = true;
					Judge = false;
				}
			}
		}
		if (Judge)
		{
			int FREE_KICK = team1.Judge_FREE_KICK(pEnv);
		}
		if (Judge)                                          
		{
			RunStrategy(pEnv);                        // Playon 
		}
	}

	pEnv->lastBall = oEnv.currentBall;

	WriteLog(&oEnv);
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

void Environment2Log(const Environment* pEnv, LogEnvironment* pLogEnv)
{
	// robots of two teams
	for (int i=0; i<5; i++)
	{
		pLogEnv->blueRobot[i].pos = pEnv->home[i].pos;
		pLogEnv->blueRobot[i].rotation = pEnv->home[i].rotation;

		pLogEnv->yellowRobot[i].pos = pEnv->opponent[i].pos;
		pLogEnv->yellowRobot[i].rotation = pEnv->opponent[i].rotation;
	}

	// ball and game state
	pLogEnv->currentBall = pEnv->currentBall.pos;
	pLogEnv->gameState = pEnv->gameState;
	pLogEnv->whosBall = pEnv->whosBall;	
}

// 
string Int2String(int n)
{
	string strResult;
	if (n < 10)			
	{
		char c = '0' + n;
		strResult.push_back('0');
		strResult.push_back(c);
	}
	else				
	{		
		char buff[10] = {0};
		itoa(n, buff, 10);
		strResult = buff;
	}

	return strResult;
}  

//
string ST2String(SYSTEMTIME st)
{
	string strResult;
	strResult.append(Int2String(st.wYear));
	strResult.append(Int2String(st.wMonth));
	strResult.append(Int2String(st.wDay));
	strResult.append(Int2String(st.wHour));
	strResult.append(Int2String(st.wMinute));
	strResult.append(Int2String(st.wSecond));

	return strResult;	
}  

void WriteLog(const Environment* pEnv)
{
	if (team1.statespace.pastTime == 2)
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		string strFile = ST2String(st);
		strFile = strFile + "-" + "5" + "-" + strYellowName + "-" + strBlueName + ".rlg";		

		fout.open(strFile.c_str(), ios_base::out | ios_base::binary);	
		if (!fout)
		{
			fout.close();
			MessageBox(NULL, "Failed to create a Log file!", "Error", MB_OK|MB_ICONERROR);
			exit(0);
		}
	}
	else if (team1.statespace.pastTime > 2)
	{	
		LogEnvironment logEnv;
		Environment2Log(pEnv, &logEnv);
		fout.write((char*)&logEnv, sizeof(LogEnvironment));
	}
}
