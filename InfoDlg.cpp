/***********************************************************************************

	Updated from TCP/IP Builder V 1.8  andrew Jan

*************************************************************************************/

// InfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ALCSTest.h"
#include "InfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg dialog


CInfoDlg::CInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfoDlg)
	m_strInfo = _T("");
	//}}AFX_DATA_INIT
}


void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoDlg)
	DDX_Text(pDX, IDC_INFO, m_strInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CInfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg message handlers

BOOL CInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	////
	SYSTEM_INFO lpSystemInfo;
	struct hostent FAR *host;
	CString strPArch, strPType, strCName;
	CString strPInfo, strCInfo, strWSInfo;
	CString str, tmp;
	int i=0, j=0;
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;


	SetCursor(LoadCursor(NULL, IDC_WAIT));

	// Sysinfo
	GetSystemInfo(&lpSystemInfo);
 
	switch(lpSystemInfo.wProcessorArchitecture) {
		case PROCESSOR_ARCHITECTURE_INTEL:	strPArch = "x86";
											break;
		case PROCESSOR_ARCHITECTURE_UNKNOWN:	strPArch = "Unknown";
												break;
		case PROCESSOR_ARCHITECTURE_IA64:	strPArch = "IA64";
											break;
		default:	strPArch = "Couldn't get info";
					break;
	}

	if (lpSystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
		switch(lpSystemInfo.wProcessorLevel) {
			case 3: strPType = "Intel 80386";
					break;
			case 4: strPType = "Intel 80486";
					break;
			case 5: strPType = "Intel Pentium";
					break;
			case 6: strPType = "Intel Pentium II, III, IV or better";
					break;
			default:	strPType = "Couldn't get info";
						break;
		}

	if (lpSystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
		strPType = "1";

	strPInfo.Format("Processor architecture: \t%s\r\nProcessor type: \t\t%s\r\nQuantity: \t\t\t%d\r\n", strPArch, strPType, lpSystemInfo.dwNumberOfProcessors);

	// Computer info
 	if (host = gethostbyname ("")) {
		strCInfo.Format("Computer name: \t%s\r\nAddresses: \r\n", host->h_name);

		while(host->h_addr_list[i]) {
			str = "\t\t";
			for(j=0; j<host->h_length; j++) {
				tmp.Format("%d", (unsigned char)host->h_addr_list[i][j]);
				str += tmp;
				if (j<(host->h_length-1)) str += ".";
			}
			str += "\r\n";
			strCInfo.Insert(strCInfo.GetLength(), str);
			i++;
		}
	}
	else {
		strCInfo = "Can't get computer name nor addresses.\r\n";
	}


	// WinSock Info
	wVersionRequested = MAKEWORD(1,0);
 
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		strWSInfo = "Can't find WinSock DLL";
	}
	else {

		strWSInfo.Format("Version: \t\t%d.%d\r\nDescription: \t%s\r\nSystem status: \t%s\r\nMax UDP packet: \t%d bytes\r\n\r\n", HIBYTE(wsaData.wHighVersion), LOBYTE(wsaData.wHighVersion), wsaData.szDescription, wsaData.szSystemStatus, wsaData.iMaxUdpDg);

		/* Clean up*/ 
		WSACleanup();
	}
 
    
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	m_strInfo.Format("--- Processor Info ---\r\n%s\r\n--- Computer Info ---\r\n%s\r\n--- WinSock Info ---\r\n%s\r\n", strPInfo, strCInfo, strWSInfo);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
