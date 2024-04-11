/***********************************************************************************

	Updated from TCP/IP Builder V 1.8  andrew Jan

*************************************************************************************/

#if !defined(AFX_MSOCKET_H__D1DD7973_5BB1_11D6_804B_004033E1EE0D__INCLUDED_)
#define AFX_MSOCKET_H__D1DD7973_5BB1_11D6_804B_004033E1EE0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CMSocket command target

class CMSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CMSocket();
	virtual ~CMSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSocket)
	public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	void SetErrorString(int error, char *str, int strsize);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSOCKET_H__D1DD7973_5BB1_11D6_804B_004033E1EE0D__INCLUDED_)
