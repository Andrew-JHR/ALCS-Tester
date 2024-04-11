#pragma once


// CListBoxEx

class CListBoxEx : public CListBox
{
	DECLARE_DYNAMIC(CListBoxEx)

public:
	CListBoxEx();
	virtual ~CListBoxEx();
protected: // methods
    void DoCopy();
    void DoSelectAll();
    virtual CString GetString(int i);
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
    afx_msg LRESULT OnCopy(WPARAM, LPARAM);
    afx_msg void OnPopupmenuforlistboxSelectall();
    afx_msg void OnPopupmenuforlistboxCopy();
};


