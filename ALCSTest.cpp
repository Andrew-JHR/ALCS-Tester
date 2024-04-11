/***********************************************************************************

	Updated from TCP/IP Builder V 1.8  andrew Jan

*************************************************************************************/

// ALCSTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ALCSTest.h"
#include "ALCSTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CALCSTestApp

BEGIN_MESSAGE_MAP(CALCSTestApp, CWinApp)
	//{{AFX_MSG_MAP(CALCSTestApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CALCSTestApp construction

CALCSTestApp::CALCSTestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CALCSTestApp object

CALCSTestApp theApp;
WSADATA wsaData;

/////////////////////////////////////////////////////////////////////////////
// CALCSTestApp initialization

BOOL CALCSTestApp::InitInstance()
{
	if (!AfxSocketInit(&wsaData))
	{
		AfxMessageBox("Unable to initialize Sockets API.", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
#endif

	m_pDlg = new CALCSTestDlg();
	m_pMainWnd = m_pDlg;
	int nResponse = m_pDlg->DoModal();

	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	delete m_pDlg;

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}



BOOL CALCSTestApp::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message) {
						// OnConnect
		case WM_USER+1: if (m_pDlg) {
							m_pDlg->Connected();
						}
						break;
						// OnReceive data
		case WM_USER+2:	if (m_pDlg) {
							m_pDlg->Receive(pMsg->lParam > 0);
						}
						break;
						// OnAccept
		case WM_USER+3:	if (m_pDlg) {
							m_pDlg->Accept();
						}
						break;
	}
	
	return CWinApp::PreTranslateMessage(pMsg);
}
