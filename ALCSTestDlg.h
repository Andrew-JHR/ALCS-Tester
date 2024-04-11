/***********************************************************************************

	Updated from TCP/IP Builder V 1.8  andrew Jan

*************************************************************************************/

// ALCSTestDlg.h : header file
//

#if !defined(AFX_ALCSTestDLG_H__D1DD7968_5BB1_11D6_804B_004033E1EE0D__INCLUDED_)
#define AFX_ALCSTestDLG_H__D1DD7968_5BB1_11D6_804B_004033E1EE0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MSocket.h"
#include "ListBoxEx.h"
#include "afxwin.h"

#define RCV_BUFFER_SIZE 32760

/////////////////////////////////////////////////////////////////////////////
// CALCSTestDlg dialog

class CALCSTestDlg : public CDialog
{
// Construction
public:
	void Accept(void);
	void Connected(void);
	void Receive(BOOL bOOB);
	CALCSTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CALCSTestDlg)
	enum { IDD = IDD_ALCSTest_DIALOG };
	CEdit   m_cSBuffer;
	CListBoxEx	m_cRBuffer;
	CIPAddressCtrl	m_cRIP;
	CButton	m_cConnect;
	CButton	m_cSend;
	CButton	m_cDestroy;
	CButton	m_cCreate;
	CButton m_cContinue;
	CIPAddressCtrl	m_cIP;
	UINT	m_iPort;
	CString	m_strReceive;
	CString	m_strSend;
	UINT	m_iRPort;
	CString	m_strPackets;
	CString	m_strBytes;
	CString	m_strLast;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALCSTestDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

private:
	char str[RCV_BUFFER_SIZE];
	char estr[256];
	int  nCurLine;  // keep the current line
	bool m_bRepeat;
	bool m_bTrace;
	int left;  // used to count bytes left to form a complete line within a packet
	char residual[2048]; // keep the left bytes
	int  m_iCount;
	int  m_iCountSet;
	char m_sCount[16];


// Implementation
protected:
	DWORD m_dwRAddress;
	DWORD m_dwBytes;
	DWORD m_dwPackets;
	CString m_strRIP;
	void SetErrorString(int error, char *str, int strsize);
	int m_iType;
	CString m_strIP;
	void UpdateDataPatch(BOOL bGetData);
	CMSocket * m_pSocket;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CALCSTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCreate();
	afx_msg void OnDestroy();
	afx_msg void OnSend();
	afx_msg void OnConnect();
	afx_msg void OnChangeRbuffer();
	afx_msg void OnRclr();
	afx_msg void OnSclr();
	afx_msg void OnAbout();
	afx_msg void OnNetstat();
	afx_msg void OnLbnErrspaceRbuffer();
	afx_msg void OnContinue();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CButton m_cRepeat;
	afx_msg void OnBnClickedRepeat();
	CEdit m_cCount;
	afx_msg void OnEnUpdateCount();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALCSTestDLG_H__D1DD7968_5BB1_11D6_804B_004033E1EE0D__INCLUDED_)
