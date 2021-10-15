
// SimuroSot5Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimuroSot5.h"
#include "SimuroSot5Dlg.h"
#include "afxdialogex.h"
#include "PlatformOperator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#pragma comment(lib,"Strategy4Blue.lib")
//#pragma comment(lib,"Strategy4Yellow.lib")
//

#define WM_RECEIVE_DATA WM_USER+120
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSimuroSot5Dlg dialog


CSimuroSot5Dlg::CSimuroSot5Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSimuroSot5Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	nPause = 0;
	nPastSecond = 0;
	nBlueGoals = 0;
	nYellowGoals = -1;
	memset(&m_data, 0, sizeof(ReferData));
}

void CSimuroSot5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSimuroSot5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BN_START, &OnBnClickedBnStart)
	ON_BN_CLICKED(IDC_BN_PAUSE, &OnBnClickedBnPause)
	ON_BN_CLICKED(IDC_BN_CLOSE, &OnBnClickedBnClose)
	ON_MESSAGE(WM_RECEIVE_DATA, &OnReceiveData)
	ON_WM_COPYDATA()
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CSimuroSot5Dlg message handlers

BOOL CSimuroSot5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	::ShellExecute(NULL, "OPEN", ".\\WorldModel.exe", NULL, NULL, SW_NORMAL);
	SleepEx(2000, TRUE);

	SetDlgItemText(IDC_STATIC_SCORE, "0  :  0");

	return TRUE;  // return TRUE  unless you set the focus to a control
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSimuroSot5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSimuroSot5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSimuroSot5Dlg::OnBnClickedBnStart()
{
	// TODO: Add your message handler code here and/or call default 
	CPlatformOperator opr;
	opr.SetStrategy();
	opr.SetStart();
	SetTimer(2, 1000, NULL);
}

void CSimuroSot5Dlg::OnBnClickedBnPause()
{
	// TODO: Add your message handler code here and/or call default 
	if (nPause == 0)
	{
		nPause = 1;
		KillTimer(2);
		SetDlgItemText(IDC_BN_PAUSE, "Continue");
	}
	else
	{
		nPause = 0;
		SetTimer(2, 1000, NULL);
		SetDlgItemText(IDC_BN_PAUSE, "Pause");
	}

	CPlatformOperator opr;
	opr.SetPause();
}


void CSimuroSot5Dlg::OnBnClickedBnClose()
{
	// TODO: Add your message handler code here and/or call default 
	CPlatformOperator opr;
	opr.CloseServer();
	SleepEx(2000, TRUE);

	CDialogEx::OnCancel();
}


LRESULT CSimuroSot5Dlg::OnReceiveData(WPARAM wParam, LPARAM lParam)
{	
	CPlatformOperator opr;
	opr.SetStop();
	ReferData*  pData = (ReferData*)lParam;
	m_data = *pData;
	work = true;
	SetTimer(1, 1000, NULL);
	return  1L;
}


void CSimuroSot5Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default   
	if (nIDEvent == 2)
	{
		nPastSecond++;
		CString strTime;
		strTime.Format("  %d  ", 300-nPastSecond);	
		SetDlgItemText(IDC_STATIC_TIME, strTime);
		if (nPastSecond >= 300)
			OnBnClickedBnPause();
	}
	else if (nIDEvent == 1)
	{
		if (work == true)
		{
			SetDlgItemText(IDC_STATIC_TEAMY, m_data.yellowTeamName);
			SetDlgItemText(IDC_STATIC_TEAMB, m_data.blueTeamName);

			work = false;
			CPlatformOperator opr;

			CString strScore;
			static int nBPushTimeLast = 0;   
			static int nYPushTimeLast = 0; 
			switch (m_data.gameState)
			{
			case PM_FreeBall_LeftTop:			
			case PM_FreeBall_LeftBot:
			case PM_FreeBall_RightTop: 
			case PM_FreeBall_RightBot:  
				{ 
					static int nB4 = 0;
					static int nY4 = 0;
					nB4 += (m_data.nBlueVPushTime - nBPushTimeLast); 
					nY4 += (m_data.nYellowVPushTime - nYPushTimeLast); 

					if (nB4 >= 4)
					{
						nYellowGoals++;
						nB4 = 0;
					}
					if (nY4 >= 4)
					{
						nBlueGoals++;
						nY4 = 0;
					}

					nBPushTimeLast = m_data.nBlueVPushTime;
					nYPushTimeLast = m_data.nYellowVPushTime;

					strScore.Format("%d  :  %d", nYellowGoals, nBlueGoals);
					SetDlgItemText(IDC_STATIC_SCORE, strScore);

					CString strPushTime;
					strPushTime.Format(" %d   :   %d ", m_data.nYellowVPushTime, m_data.nBlueVPushTime);
					SetDlgItemText(IDC_STATIC_PUSHTIME, strPushTime);					
				}
				opr.SetFreeBall();break;
			case PM_PlaceKick_Yellow:  
				nBlueGoals++;
				strScore.Format("%d  :  %d", nYellowGoals, nBlueGoals);
				SetDlgItemText(IDC_STATIC_SCORE, strScore);
				opr.SetPlaceKick('Y');break;
			case PM_PlaceKick_Blue:     
				nYellowGoals++;
				strScore.Format("%d  :  %d", nYellowGoals, nBlueGoals);
				SetDlgItemText(IDC_STATIC_SCORE, strScore);
				opr.SetPlaceKick('B');break;
			case PM_PenaltyKick_Yellow:				
				opr.SetPenaltyKick('Y'); break;
			case PM_PenaltyKick_Blue:
				opr.SetPenaltyKick('B'); break;
			case PM_FreeKick_Yellow:   
				opr.SetFreeKick('Y'); break;
			case PM_FreeKick_Blue:   
				opr.SetFreeKick('B'); break;
			case PM_GoalKick_Yellow:
				opr.SetGoalKick('Y'); break;
			case PM_GoalKick_Blue:     
				opr.SetGoalKick('B'); break;
			}			

			SleepEx(1000, TRUE);
			opr.SetBall(m_data.Posball.x, m_data.Posball.y);
			SleepEx(1000, TRUE);
			if (m_data.xianbai == 1)
			{
				for (int i = 0; i < 5; i++)
				{
					opr.SetRobot('B', i, m_data.Posxianbai[i].pos.x, m_data.Posxianbai[i].pos.y, 
						m_data.Posxianbai[i].rotation);			
				}
				for (int i = 0; i < 5; i++)
				{
					opr.SetRobot('Y', i, m_data.Poshoubai[i].pos.x, m_data.Poshoubai[i].pos.y, 
						m_data.Poshoubai[i].rotation);				
				}
			}
			else if (m_data.xianbai == 2)
			{
				for (int i = 0; i < 5; i++)
				{
					opr.SetRobot('Y', i, m_data.Posxianbai[i].pos.x, m_data.Posxianbai[i].pos.y, 
						m_data.Posxianbai[i].rotation);
				}
				for (int i = 0; i < 5; i++)
				{
					opr.SetRobot('B', i, m_data.Poshoubai[i].pos.x, m_data.Poshoubai[i].pos.y, 
						m_data.Poshoubai[i].rotation);
				}
			}
			opr.SetStart();
		}
		KillTimer(1);
	}


	CDialogEx::OnTimer(nIDEvent);
}

void CSimuroSot5Dlg::OnClose()
{
	CPlatformOperator opr;
	opr.CloseServer();
	SleepEx(2000, TRUE);

	CDialogEx::OnClose();
}


void CSimuroSot5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

BOOL CSimuroSot5Dlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	CPlatformOperator opr;
	opr.SetStop();
	ReferData*  pData = (ReferData*)pCopyDataStruct->lpData;
	m_data = *pData;
	work = true;
	SetTimer(1, 1000, NULL);
	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

