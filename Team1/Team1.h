/*! @file
********************************************************************************
<PRE>
Module			 : Basic structures and some definitions.
File			 : Team1.h
Relevent File(s) : Team1.cpp
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

*******************************************************************************/
#ifndef Team1_H
#define Team1_H

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TEAM1_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// STRATEGY_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef TEAM1_EXPORTS
#define TEAM1_API __declspec(dllexport)
#define STRATEGY_API __declspec(dllimport)
#else
#define TEAM1_API __declspec(dllimport)
#define STRATEGY_API __declspec(dllexport)
#endif

#include "stdafx.h"

const long PLAYERS_PER_SIDE = 5;

// gameState
const long FREE_BALL = 1;
const long PLACE_KICK = 2;
const long PENALTY_KICK = 3;
const long FREE_KICK = 4;
const long GOAL_KICK = 5;

// whosBall
const long ANYONES_BALL = 0;
const long BLUE_BALL = 1;
const long YELLOW_BALL = 2;

// global variables -- Useful field positions  
const double FTOP = 77.2392;
const double FBOT = 6.3730;
const double GTOPY = 49.6801;
const double GBOTY = 33.9320;
const double GRIGHT = 97.3632;
const double GLEFT = 2.8748;
const double FRIGHTX = 93.4259;
const double FLEFTX = 6.8118;

typedef struct
{
	double x, y, z;
} Vector3D;

typedef struct
{
	long left, right, top, bottom;
} Bounds;

typedef struct
{
	Vector3D pos;
	double rotation;
	double velocityLeft, velocityRight;
} Robot;

typedef struct
{
	Vector3D pos;
	double rotation;
} OpponentRobot;

typedef struct
{
	Vector3D pos;
} Ball;

typedef struct
{
	Robot home[PLAYERS_PER_SIDE];
	OpponentRobot opponent[PLAYERS_PER_SIDE];
	Ball currentBall, lastBall, predictedBall;
	Bounds fieldBounds, goalBounds;
	long gameState;
	long whosBall;
	void *userData;
} Environment;

typedef void (*MyStrategyProc)(Environment*);
typedef COPYDATASTRUCT SENDREFER;
/* MUST BE IMPLEMENTED */
extern "C" TEAM1_API void Create ( Environment *env );   
extern "C" TEAM1_API void Strategy ( Environment *env );
extern "C" TEAM1_API void Destroy ( Environment *env ); 

typedef OpponentRobot LogRobot;

typedef struct
{
	LogRobot blueRobot[5];
	LogRobot yellowRobot[5];
	Vector3D currentBall;	
	long gameState;
	long whosBall;
} LogEnvironment;

#endif // Team1_H