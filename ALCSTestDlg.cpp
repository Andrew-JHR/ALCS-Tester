/***********************************************************************************

	Updated from TCP/IP Builder V 1.8  andrew Jan

*************************************************************************************/

// ALCSTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ALCSTest.h"
#include "ALCSTestDlg.h"
#include "InfoDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern WSADATA wsaData;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CALCSTestDlg dialog

CALCSTestDlg::CALCSTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CALCSTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CALCSTestDlg)
	m_iPort = 0;
	m_strReceive = _T("");
	m_strSend = _T("");
	m_iRPort = 0;
	m_strPackets = _T("");
	m_strBytes = _T("");
	m_strLast = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


	// Socket
	m_pSocket = new CMSocket(); 
	m_bRepeat = 0;  // initiate the value
	m_bTrace  = 0;  // initiate the value
	
}

void CALCSTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CALCSTestDlg)
	DDX_Control(pDX, IDC_SBUFFER, m_cSBuffer);
	DDX_Control(pDX, IDC_RBUFFER, m_cRBuffer);
	DDX_Control(pDX, IDC_RIPADDR, m_cRIP);
	DDX_Control(pDX, IDC_CONNECT, m_cConnect);
	DDX_Control(pDX, IDC_SEND, m_cSend);
	DDX_Control(pDX, IDC_CONTINUE, m_cContinue);
	DDX_Control(pDX, IDC_DESTROY, m_cDestroy);
	DDX_Control(pDX, IDC_CREATE, m_cCreate);
	DDX_Control(pDX, IDC_IPADDR, m_cIP);
	DDX_Text(pDX, IDC_PORT, m_iPort);
	DDV_MinMaxUInt(pDX, m_iPort, 0, 65535);
	DDX_Text(pDX, IDC_RBUFFER, m_strReceive);
	DDX_Text(pDX, IDC_SBUFFER, m_strSend);
	DDX_Text(pDX, IDC_RPORT, m_iRPort);
	DDV_MinMaxUInt(pDX, m_iRPort, 0, 65535);
	DDX_Text(pDX, IDC_PACKETS, m_strPackets);
	DDX_Text(pDX, IDC_BYTES, m_strBytes);
	DDX_Text(pDX, IDC_LAST, m_strLast);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_REPEAT, m_cRepeat);
	DDX_Control(pDX, IDC_COUNT, m_cCount);
}

BEGIN_MESSAGE_MAP(CALCSTestDlg, CDialog)
	//{{AFX_MSG_MAP(CALCSTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CREATE, OnCreate)
	ON_BN_CLICKED(IDC_DESTROY, OnDestroy)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_EN_CHANGE(IDC_RBUFFER, OnChangeRbuffer)
	ON_BN_CLICKED(IDC_RCLR, OnRclr)
	ON_BN_CLICKED(IDC_SCLR, OnSclr)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_NETSTAT, OnNetstat)
	ON_BN_CLICKED(IDC_CONTINUE, OnContinue)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_REPEAT, &CALCSTestDlg::OnBnClickedRepeat)
	ON_EN_UPDATE(IDC_COUNT, &CALCSTestDlg::OnEnUpdateCount)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CALCSTestDlg message handlers

BOOL CALCSTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);

			// No Size
			pSysMenu->EnableMenuItem(2, MF_GRAYED | MF_BYPOSITION);
			// No Maximize
			pSysMenu->EnableMenuItem(4, MF_GRAYED | MF_BYPOSITION);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Init
	// Default
	m_cIP.SetAddress(192,168,110,51); // instead of 127.0.0.1
	m_cRIP.SetAddress(10,64,8,101);
//	m_dwRAddress = 0x0a400905; // 10.64.9.5
    m_dwRAddress = 0x0a400865; // 10.64.8.101
	CheckRadioButton(IDC_TCP, IDC_UDP, IDC_TCP);

	m_cCreate.EnableWindow(TRUE);
	m_cDestroy.EnableWindow(FALSE);
	m_cConnect.EnableWindow(FALSE);
	m_cSend.EnableWindow(FALSE);

	DWORD dwVal=1;
	m_pSocket->IOCtl(FIONBIO, &dwVal);


	m_dwPackets=0;
	m_dwBytes=0;
	m_strPackets.Format("%u", m_dwPackets);
	m_strBytes.Format("%u", m_dwBytes);
	m_strLast.Format("%u", 0);

	m_iCountSet = 1000;
	m_iCount = m_iCountSet;
	itoa(m_iCount,m_sCount,10);
	m_cCount.SetWindowTextA(m_sCount);
	
	UpdateDataPatch(FALSE);

	left = 0;  //initiate the # of bytes left within a packet belonging to another line
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CALCSTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CALCSTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

//		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CALCSTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CALCSTestDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	//Socket
	delete m_pSocket;
	
	return CDialog::DestroyWindow();
}

void CALCSTestDlg::OnCreate() 
{
	char str[256]={"No more info."};

	//Update
	UpdateDataPatch(TRUE);
	
	//Create
	if (!m_pSocket->Create(m_iPort, m_iType, FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE, m_strIP)) { 

		SetErrorString(m_pSocket->GetLastError(), str, sizeof(str)-1);

		MessageBox(str, "Can't create socket", MB_ICONSTOP | MB_OK);
	}
	else {
		m_cCreate.EnableWindow(FALSE);
		m_cDestroy.EnableWindow(TRUE);
		if (m_iType == SOCK_STREAM) {
			m_cConnect.EnableWindow(TRUE);
		}
		else {
			m_cSend.EnableWindow(TRUE);
		}

		if (!m_iPort) {
			m_pSocket->GetSockName(m_strIP, m_iPort);
			UpdateDataPatch(FALSE);
		}
	}

}


void CALCSTestDlg::UpdateDataPatch(BOOL bGetData)
{
	BYTE vip[4];
	UINT button;


	// El update normal
	UpdateData(bGetData);

	if (bGetData) {
		// Patch para el IP 
		m_cIP.GetAddress(vip[0], vip[1], vip[2], vip[3]);
		m_strIP.Format("%d.%d.%d.%d", vip[0], vip[1], vip[2], vip[3]);

		// Patch para el RIP 
		m_cRIP.GetAddress(vip[0], vip[1], vip[2], vip[3]);
		m_strRIP.Format("%d.%d.%d.%d", vip[0], vip[1], vip[2], vip[3]);
		m_cRIP.GetAddress(m_dwRAddress);

		// Patch para Protocolo
		button = GetCheckedRadioButton(IDC_TCP, IDC_UDP);
		if (button==IDC_TCP) m_iType = SOCK_STREAM;
		if (button==IDC_UDP) m_iType = SOCK_DGRAM;
	}
	else {

		// Patch para el RIP 
		m_cRIP.SetAddress(m_dwRAddress);
	}

}


void CALCSTestDlg::SetErrorString(int error, char *str, int strsize)
{

	switch(error) {
		case WSANOTINITIALISED:strcpy_s(str, strsize, "Socket API not initialized.");
								break;
		case WSAENETDOWN:     strcpy_s(str, strsize, "Network subsystem failed.");
								break;
		case WSAEADDRINUSE:   strcpy_s(str, strsize, "The specified address is already in use.");
								break;
		case WSAEACCES:       strcpy_s(str, strsize, "The requested address is a broadcast address, but the appropriate flag was not set.");
								break;
		case WSAEAFNOSUPPORT:	strcpy_s(str, strsize, "Address family not supported.");
								break;
		case WSAECONNREFUSED:	strcpy_s(str, strsize, "The attempt to connect was rejected.");
								break;
		case WSAEDESTADDRREQ:	strcpy_s(str, strsize, "A destination address is required.");
								break;
		case WSAEINPROGRESS:	strcpy_s(str, strsize, "A blocking Windows Sockets operation is in progress.");
								break;
		case WSAEADDRNOTAVAIL:strcpy_s(str, strsize, "The specified address is not available from the local machine.");
								break;
		case WSAEFAULT:			  strcpy_s(str, strsize, "* The lpBuf argument is not in a valid part of the user address space.");
								break;
		case WSAEINVAL:			  strcpy_s(str, strsize, "Invalid host address / The socket has not been bound with Bind.");
								break;
		case WSAEISCONN:		  strcpy_s(str, strsize, "The socket is already connected.");
								break;
		case WSAEMFILE:			  strcpy_s(str, strsize, "No more file descriptors are available.");
								break;
		case WSAENETUNREACH:	strcpy_s(str, strsize, "The network cannot be reached from this host at this time.");
								break;
		case WSAENETRESET:		strcpy_s(str, strsize, "The connection must be reset because the Windows Sockets implementation dropped it.");
								break;
		case WSAENOBUFS:		  strcpy_s(str, strsize, "No buffer space is available.");
								break;
		case WSAENOTCONN:		  strcpy_s(str, strsize, "The socket is not connected.");
								break;
		case WSAENOTSOCK:		  strcpy_s(str, strsize, "The descriptor is not a socket.");
								break;
		case WSAETIMEDOUT:		strcpy_s(str, strsize, "Attempt to connect timed out without establishing a connection.");
								break;
		case WSAEPROTONOSUPPORT:strcpy_s(str, strsize, "The specified port is not supported.");
								break;
		case WSAEPROTOTYPE:		strcpy_s(str, strsize, "The specified port is the wrong type for this socket.");
								break;
		case WSAESOCKTNOSUPPORT:strcpy_s(str, strsize, "The specified socket type is not supported in this address family.");
								break;
		case WSAEOPNOTSUPP:		strcpy_s(str, strsize, "Out of band was specified, but the socket is not of type TCP.");
								break;
		case WSAESHUTDOWN:		strcpy_s(str, strsize, "The socket has been shut down.");
								break;
		case WSAEWOULDBLOCK:	strcpy_s(str, strsize, "The socket is marked as nonblocking and the requested operation would block.");
								break;
		case WSAEMSGSIZE:		  strcpy_s(str, strsize, "The socket is of type UDP, and the datagram is larger than the maximum supported by the Windows Sockets implementation.");
								break;
		case WSAECONNABORTED:	strcpy_s(str, strsize, "The virtual circuit was aborted due to timeout or other failure.");
								break;
		case WSAECONNRESET:		strcpy_s(str, strsize, "The virtual circuit was reset by the remote side.");
								break;
	}

}

void CALCSTestDlg::OnDestroy() 
{
	// TODO: Add your control notification handler code here

	delete m_pSocket;
	m_pSocket = new CMSocket();

	m_strReceive.Empty();

	UpdateDataPatch(FALSE);

	m_cCreate.EnableWindow(TRUE);
	m_cDestroy.EnableWindow(FALSE);
	m_cConnect.EnableWindow(FALSE);
	m_cSend.EnableWindow(FALSE);
}

void CALCSTestDlg::OnSend() 
{
	int Flags = 0;
	char str[256]={"No more info."};
	char *Buffer;
	int BufferLength;

	nCurLine = m_cRBuffer.GetCount(); // get the current count of the output window

	// Leo datos
	UpdateDataPatch(TRUE);

	BufferLength = m_strSend.GetLength();
	Buffer = (char *)malloc(BufferLength); 

	if (Buffer) {
		
			memcpy(Buffer, m_strSend.GetBuffer(m_strSend.GetLength()), BufferLength);
		

		if (m_iType == SOCK_STREAM) {
			if (m_pSocket->Send(Buffer, BufferLength, Flags) == SOCKET_ERROR) {

				SetErrorString(m_pSocket->GetLastError(), str, sizeof(str));
				MessageBox(str, "Can't send to socket", MB_ICONSTOP | MB_OK);
			}
			else	{	
			 
			}
			
		}
		else {
			if (m_strSend.GetLength()) {
				if (m_strSend.GetLength() < wsaData.iMaxUdpDg) {
					if (m_pSocket->SendTo(Buffer, BufferLength, m_iRPort, m_strRIP, Flags) == SOCKET_ERROR) {

						SetErrorString(m_pSocket->GetLastError(), str, sizeof(str));
						MessageBox(str, "Can't send to socket", MB_ICONSTOP | MB_OK);
					}
					else {
						
					}
				}
				else {
					CString strTmp;
					strTmp.Format("Microsoft's sockects API returned %d as the largest UDP packet possible.", wsaData.iMaxUdpDg);
					MessageBox(strTmp, "UDP Packet Limit", MB_ICONSTOP | MB_OK);
				}
			}
			else {
				MessageBox("Won't send empty UDP packet.", "UDP Protection", MB_ICONSTOP | MB_OK);
			}
		}

		// free buffer
		free(Buffer);
	}
	else {
		MessageBox("Can't allocate memory for binary buffer", "Critical error", MB_ICONSTOP | MB_OK);
	}
}

void CALCSTestDlg::OnConnect() 
{
	char str[256]={"No more info."};

	// Leo datos
	UpdateDataPatch(TRUE);

	SetCursor(LoadCursor(NULL, IDC_WAIT));

	// Conecto
	if (!m_pSocket->Connect(m_strRIP, m_iRPort)) {

		if (m_pSocket->GetLastError() != WSAEWOULDBLOCK) {
			SetErrorString(m_pSocket->GetLastError(), str, sizeof(str));
			MessageBox(str, "Can't connect socket", MB_ICONSTOP | MB_OK);
		}
		else {
		}
	}
	else {

		m_cSend.EnableWindow(TRUE);
	}

	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

LRESULT CALCSTestDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::WindowProc(message, wParam, lParam);

}

void CALCSTestDlg::Receive(BOOL bOOB)
{
	CString tmp, ttmp, strAddress;
	int count, i, j;
	int flags = 0;
	UINT iPort;
	int Flags = 0;
	char RptBfr[1];
	RptBfr[0] = '+';
	int  RptBfrLen = 1;
	
  memset(str, 0, RCV_BUFFER_SIZE);

	// OOB
	if (bOOB) flags |= MSG_OOB;

	if (m_iType == SOCK_STREAM) {
		count = m_pSocket->Receive(str, RCV_BUFFER_SIZE-1, flags);
	}
	else {
		count = m_pSocket->ReceiveFrom(str, RCV_BUFFER_SIZE-1, strAddress, iPort, flags);
	}

	// normal
	if (!count) {

		if (m_pSocket->GetLastError() != WSAEWOULDBLOCK) {
			SetErrorString(m_pSocket->GetLastError(), estr, sizeof(estr));
			MessageBox(estr, "Can't receive from socket", MB_ICONSTOP | MB_OK);
		}
	}
	else {
		i = 0;
		j = 0;

		if ( left != 0 )
		{
			for (i=0 ; i < count ; i++)
			{
				if (str[i] == 0x0a)
				{
					str[i] = 0;
					break;
				}				    
			}
			strcpy(&(residual[left]),str);
			m_cRBuffer.AddString(residual);  // write to listbox
			j = i + 1;

		}

		// deal with other characters of this block
		for (i=j; i < count ; i++)
		{
			if (str[i] == 0x0a)
			{
				str[i] = 0;
				m_cRBuffer.AddString(&(str[j]));
				j = i+1;
			}
		}
		
		left = count - j;  // create new 'left': any characters left? -- because of the packet size
		
		if ( (left == 2) && (str[j] = '>') && (str[j+1] = '+') ) // indicator for end of block
			left = 0;
		else if ( left < 0 )
			left = 0;
		

		if ( left != 0 )
			memcpy(residual,&(str[j]),left); // keep the left characters 
				

		m_cRBuffer.SetTopIndex(nCurLine); //display the top of the latest response
		m_cSBuffer.SetFocus(); //move the current to the input window
	  	m_dwPackets++;
		m_strPackets.Format("%u", m_dwPackets);
		m_strLast.Format("%u", count);
		m_dwBytes += count;
		m_strBytes.Format("%u", m_dwBytes);

		if ( ( m_iType == SOCK_STREAM ) && ( m_bTrace == true ) )   // automatically generate "+" input
		{	
			if ( strncmp(str,"TRACE -- ENTER MESSAGE TO TRACE",31) == 0 )
			{
				m_bTrace = false;
        		m_cContinue.SetWindowText("&Auto Off");
			}
			else if (m_pSocket->Send(RptBfr, RptBfrLen, Flags) == SOCKET_ERROR)
			{

				SetErrorString(m_pSocket->GetLastError(), str, sizeof(str));
				MessageBox(str, "Can't send to socket", MB_ICONSTOP | MB_OK);
			}
		}
		else if  ( (m_iType == SOCK_STREAM ) && ( m_bRepeat == true ) )
		{
			if (m_iCount > 0 )
			{
		    	this->OnSend();
				m_iCount--;
				itoa(m_iCount,m_sCount,10);
	            m_cCount.SetWindowTextA(m_sCount);
			}
			else
			{
				m_iCount = m_iCountSet;
				itoa(m_iCountSet,m_sCount,10);
	            m_cCount.SetWindowTextA(m_sCount);
				m_bRepeat = false;
	            m_cRepeat.SetWindowText("&Repeat Off");
			}
		}
	}

	UpdateDataPatch(FALSE);

}

void CALCSTestDlg::Connected()
{

	m_cSend.EnableWindow(TRUE);

}

void CALCSTestDlg::OnChangeRbuffer() 
{
}

void CALCSTestDlg::OnRclr() 
{
	// TODO: Add your control notification handler code here
	m_cRBuffer.ResetContent();   // clear listbox buffer andrewj 
	
	UpdateDataPatch(TRUE);
	m_strReceive.Empty();
	m_dwPackets=0;
	m_dwBytes=0;
	m_strPackets.Format("%u", m_dwPackets);
	m_strBytes.Format("%u", m_dwBytes);
	m_strLast.Format("%u", 0);
	UpdateDataPatch(FALSE);
	
}

void CALCSTestDlg::OnSclr() 
{
	// TODO: Add your control notification handler code here
	
	UpdateDataPatch(TRUE);
	m_strSend.Empty();
	UpdateDataPatch(FALSE);

}


void CALCSTestDlg::OnAbout() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CALCSTestDlg::OnNetstat() 
{

	CInfoDlg info;
	info.DoModal();
		
}

void CALCSTestDlg::Accept()
{
	char str[256]={"No more info."};
	CString tmp;
	SOCKADDR_IN SockAddr;
	int SockAddrLen = sizeof(SOCKADDR_IN);

	CMSocket *pTmpSock = new CMSocket();

	if (m_pSocket->Accept(*pTmpSock, (SOCKADDR *)&SockAddr, &SockAddrLen)) {

		// Kill old socket
		delete m_pSocket;

		// Still NASTY
		m_pSocket = pTmpSock;

		m_dwRAddress =	(SockAddr.sin_addr.S_un.S_un_b.s_b1 << 24) |
						(SockAddr.sin_addr.S_un.S_un_b.s_b2 << 16) | 
						(SockAddr.sin_addr.S_un.S_un_b.s_b3 << 8) | 
						(SockAddr.sin_addr.S_un.S_un_b.s_b4 << 0);

		m_iRPort = ntohs(SockAddr.sin_port);
 
		// Patch for limit
		tmp.Format("Connected\r\n");

		m_strReceive.Insert(m_strReceive.GetLength(), tmp);

		UpdateDataPatch(FALSE);

		m_cSend.EnableWindow(TRUE);

	}
	else {
		SetErrorString(m_pSocket->GetLastError(), str, sizeof(str));
		MessageBox(str, "Can't accept socket connection", MB_ICONSTOP | MB_OK);
	}

}



void CAboutDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CDialog::OnLButtonUp(nFlags, point);

	EndModalLoop(1);
}

void CAboutDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CDialog::OnRButtonUp(nFlags, point);

	EndModalLoop(1);
}

void CALCSTestDlg::OnCancel() 
{
	if (MessageBox("Do you really want to quit?", "ALCS Sockets Tester", MB_YESNO | MB_DEFBUTTON2 | MB_ICONWARNING) == IDYES) {


		CDialog::OnCancel();
	}
}

void CALCSTestDlg::OnLbnErrspaceRbuffer()
{
	AfxMessageBox(" Space Is Full, All OUTPUT Data Will Be Erased ! ");
	m_cRBuffer.ResetContent(); // clear listbox buffer andrewj
}

void CALCSTestDlg::OnContinue() 
{
  if (m_bTrace)
  {
	  m_bTrace = false;
	  m_cContinue.SetWindowText("&Trace Off");
  }
  else
  {
	  m_bTrace = true;
	  m_cContinue.SetWindowText("&Trace On");
  }

}

void CALCSTestDlg::OnBnClickedRepeat()
{
  if (m_bRepeat)
  {	  
	  m_bRepeat = false;
	  m_cRepeat.SetWindowText("&Repeat Off");
	  m_iCount = m_iCountSet;
	  itoa(m_iCount,m_sCount,10);
	  m_cCount.SetWindowTextA(m_sCount);
  }
  else
  {
	  m_bRepeat = true;
	  m_cRepeat.SetWindowText("&Repeat On");
	  
  }

}


void CALCSTestDlg::OnEnUpdateCount()
{
	m_cCount.GetWindowText((CString)m_sCount);
	m_iCountSet = atoi(m_sCount);
	m_iCount = m_iCountSet;
}
