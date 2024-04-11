/***********************************************************************************

	Updated from TCP/IP Builder V 1.8  andrew Jan

*************************************************************************************/

// ALCSTest.h : main header file for the ALCSTest application
//

#if !defined(AFX_ALCSTest_H__D1DD7966_5BB1_11D6_804B_004033E1EE0D__INCLUDED_)
#define AFX_ALCSTest_H__D1DD7966_5BB1_11D6_804B_004033E1EE0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "ALCSTestDlg.h"



/////////////////////////////////////////////////////////////////////////////
// CALCSTestApp:
// See ALCSTest.cpp for the implementation of this class
//

class CALCSTestApp : public CWinApp
{
public:
	CALCSTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALCSTestApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CALCSTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CALCSTestDlg * m_pDlg;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALCSTest_H__D1DD7966_5BB1_11D6_804B_004033E1EE0D__INCLUDED_)
