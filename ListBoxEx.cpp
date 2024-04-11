// ListBoxEx.cpp 
//

#include "stdafx.h"
#include "ALCSTest.h"
#include "ListBoxEx.h"
#include "resource.h"
#include "strsafe.h"



// CListBoxEx

IMPLEMENT_DYNAMIC(CListBoxEx, CListBox)

CListBoxEx::CListBoxEx()
{

}

CListBoxEx::~CListBoxEx()
{
}


BEGIN_MESSAGE_MAP(CListBoxEx, CListBox)
	ON_WM_CONTEXTMENU()
    ON_WM_CHAR()
    ON_COMMAND(ID_POPUPMENUFORLISTBOX_SELECTALL, OnPopupmenuforlistboxSelectall)
    ON_COMMAND(ID_POPUPMENUFORLISTBOX_COPY, OnPopupmenuforlistboxCopy)
END_MESSAGE_MAP()



// CListBoxEx 



/****************************************************************************
*                          CListBoxEx::OnContextMenu
* Inputs:
*       CWnd * pWnd:
*       CPoint point: Point in screen coordinates
* Result: void
*       
* Effect: 
*       Pops up the context menu
****************************************************************************/


void CListBoxEx::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
    {
     CMenu menu;
     menu.LoadMenu(IDR_LISTBOX_POPUP);
     CMenu * popup = menu.GetSubMenu(0);

     int itemcount = CListBox::GetCount();
     int selcount = CListBox::GetSelCount();
     popup->EnableMenuItem(ID_POPUPMENUFORLISTBOX_SELECTALL,
                           MF_BYCOMMAND | ((itemcount > 0 && selcount != itemcount) ? MF_ENABLED : MF_GRAYED));

     popup->EnableMenuItem(ID_POPUPMENUFORLISTBOX_COPY,
                           MF_BYCOMMAND | (selcount > 0 ? MF_ENABLED : MF_GRAYED));

#ifndef _DEBUG
//     popup->DeleteMenu(ID_POPUPMENUFORLISTBOX_ENUMCLIPBOARDFORMATS, MF_BYCOMMAND);
#endif

     popup->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
    }

/****************************************************************************
*                             CListBoxEx::OnCopy
* Inputs:
*       WPARAM: ignored, 0
*       LPARAM: ignored, 0
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Invokes the copy operation
****************************************************************************/

LRESULT CListBoxEx::OnCopy(WPARAM, LPARAM)
    {
     DoCopy();
     return 0;
    } // CListBoxEx::OnCopy

/****************************************************************************
*                           CListBoxEx::OnChar
* Inputs:
*       UINT nChar: Character code
*       UINT nIndex: The current list-box caret
* Result: void
*       
* Effect: 
*       Implements the shortcut keys for select all and copy
****************************************************************************/
#define SHORTCUT_SELECT_ALL 0x0001
#define SHORTCUT_COPY       0x0003
#ifdef _DEBUG
#define SHORTCUT_ENUM_CLIPBOARD_FORMATS 0x0005
#endif

void CListBoxEx::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
    {
     switch(nChar)
        { /* nChar */
         case SHORTCUT_SELECT_ALL:
            DoSelectAll();
            return;
         case SHORTCUT_COPY:
            DoCopy();
            return;
        } /* nChar */
    CListBox::OnChar(nChar, nRepCnt, nFlags);
    }

/****************************************************************************
*                           CListBoxEx::DoSelectAll
* Result: void
*       
* Effect: 
*       Selects all items in the listbox
****************************************************************************/

void CListBoxEx::DoSelectAll()
    {
     CListBox::SelItemRange(TRUE, 0, CListBox::GetCount());
    } // CListBoxEx::DoSelectAll

/****************************************************************************
*                            CListBoxEx::GetString
* Inputs:
*       int i: Index of element whose string is to be obtained
* Result: CString
*       String representation of element
* Effect: 
*       Converts the list item index to a string for the clipboard
* Notes:
*       This is a virtual method, and can be overridden in a subclass
*       to handle other kinds of listboxes
****************************************************************************/

/* virtual */ CString CListBoxEx::GetString(int i)
    {
     //*****************************************************************************
     // This segment of code only works if the listbox is non-owner-draw,          *
     // or is owner-draw with LBS_HASSTRINGS                                       *
     // So first check to make sure this is true                                   *
     //*****************************************************************************
     ASSERT( (GetStyle() & (LBS_OWNERDRAWFIXED | LBS_OWNERDRAWVARIABLE)) == 0 ||
             (GetStyle() & LBS_HASSTRINGS) == LBS_HASSTRINGS);

     // Extract the text
     CString t;
     CListBox::GetText(i, t);
     return t;
    } // CListBoxEx::GetString

/****************************************************************************
*                             CListBoxEx::DoCopy
* Result: void
*       
* Effect: 
*       Copies the text to the clipboard
****************************************************************************/

void CListBoxEx::DoCopy()
    {
     CArray<int, int> sels;
     int n = CListBox::GetSelCount();
     if(n <= 0)
        return; // nothing to copy

     sels.SetSize(n);
     CListBox::GetSelItems(n, sels.GetData());

     CString s;

     // Extract the text
     for(int i = 0; i < n; i++)
        { /* copy items */
         CString t;       
         t = GetString(sels[i]);
         t += _T("\r\n");
         s += t;
        } /* copy items */

     HGLOBAL g = ::GlobalAlloc(GMEM_MOVEABLE, (s.GetLength() + 1) * sizeof(TCHAR));
     if(g == NULL)
        { /* alloc failed */
         ASSERT(FALSE);  // failed to allocate memory
         return;
        } /* alloc failed */

     LPTSTR p = (LPTSTR)::GlobalLock(g);
     if(p == NULL)
        { /* lock failed */
         ASSERT(FALSE);
         return;
        } /* lock failed */

     StringCchCopy(p, s.GetLength() + 1, (LPCTSTR)s);

     ::GlobalUnlock(g);

     if(!OpenClipboard())
        { /* clipboard open failed */
         ASSERT(FALSE);
         GlobalFree(g);
         return;
        } /* clipboard open failed */

     if(!EmptyClipboard())
        { /* empty failed */
         ASSERT(FALSE);
         GlobalFree(g);
         return;
        } /* empty failed */

     if(::SetClipboardData(CF_TEXT, g) == NULL)
        { /* SetClipboardData failed */
         ASSERT(FALSE); //
         ::CloseClipboard();
         ::GlobalFree(g);
         return;
        } /* SetClipboardData failed */
     ::CloseClipboard();
    } // CListBoxEx::DoCopy

void CListBoxEx::OnPopupmenuforlistboxSelectall()
    {
     DoSelectAll();
    }

void CListBoxEx::OnPopupmenuforlistboxCopy()
    {
     DoCopy();
    }

