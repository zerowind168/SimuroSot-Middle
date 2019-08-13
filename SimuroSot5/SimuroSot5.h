
// SimuroSot5.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSimuroSot5App:
// See SimuroSot5.cpp for the implementation of this class
//

class CSimuroSot5App : public CWinApp
{
public:
	CSimuroSot5App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSimuroSot5App theApp;