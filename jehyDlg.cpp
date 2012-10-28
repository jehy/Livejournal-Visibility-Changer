// jehyDlg.cpp : implementation file
//
#include "stdafx.h"
#include "jehy.h"
#include "help.h"
#include "jehyDlg.h"
#include "ljwrapper.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//CEdit* log;
ljwrapper* lj;


// CjehyDlg dialog

CjehyDlg::CjehyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CjehyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CjehyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT7, mylog);
	//DDX_Control(pDX, IDC_CHECK1, c1);
	//DDX_Control(pDX, IDC_CHECK2, c2);
	//DDX_Control(pDX, IDC_CHECK4, direct_chk);
	//DDX_Control(pDX, IDC_CHECK3, proxy_chk);
	DDX_Control(pDX, IDC_EDIT4, hostname);
	//DDX_Control(pDX, IDC_IPADDRESS1, ip);
	DDX_Control(pDX, IDC_EDIT2, port);
	//DDX_Control(pDX, IDC_EDIT1, proxy_addr);
	DDX_Control(pDX, IDC_EDIT3, user);
	DDX_Control(pDX, IDC_EDIT5, pass);
	DDX_Control(pDX, IDC_EDIT6, fromday);
	DDX_Control(pDX, IDC_EDIT8, frommonth);
	DDX_Control(pDX, IDC_EDIT9, fromyear);
	DDX_Control(pDX, IDC_EDIT10, today);
	DDX_Control(pDX, IDC_EDIT11, tomonth);
	DDX_Control(pDX, IDC_EDIT12, toyear);
}

BEGIN_MESSAGE_MAP(CjehyDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
ON_WM_CLOSE()
//ON_BN_CLICKED(IDOK, &CjehyDlg::OnBnClickedOk)
//ON_EN_CHANGE(IDC_EDIT4, &CjehyDlg::OnEnChangeEdit4)
//ON_BN_CLICKED(IDC_BUTTON4, &CjehyDlg::OnBnClickedButton4)
//ON_EN_UPDATE(IDC_EDIT1, &CjehyDlg::OnEnUpdateEdit1)
//ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS1, &CjehyDlg::OnIpnFieldchangedIpaddress1)
//ON_BN_CLICKED(IDC_CHECK3, &CjehyDlg::OnBnClickedCheck3)
//ON_BN_CLICKED(IDC_CHECK4, &CjehyDlg::OnBnClickedCheck4)
//ON_BN_CLICKED(IDC_CHECK1, &CjehyDlg::OnBnClickedCheck1)
//ON_BN_CLICKED(IDC_CHECK2, &CjehyDlg::OnBnClickedCheck2)
ON_BN_CLICKED(IDC_BUTTON1, &CjehyDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON8, &CjehyDlg::OnBnClickedButton8)
ON_BN_CLICKED(IDC_BUTTON2, &CjehyDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON3, &CjehyDlg::OnBnClickedButton3)
ON_BN_CLICKED(IDC_BUTTON6, &CjehyDlg::OnBnClickedButton6)
ON_BN_CLICKED(IDC_BUTTON4, &CjehyDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CjehyDlg message handlers

BOOL CjehyDlg::OnInitDialog()
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
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	

	port.SetWindowTextA("80");
	hostname.SetWindowTextA("www.livejournal.com");
	fromday.SetWindowTextA("1");
	frommonth.SetWindowTextA("9");
	fromyear.SetWindowTextA("2008");
	today.SetWindowTextA("1");
	tomonth.SetWindowTextA("9");
	toyear.SetWindowTextA("2008");
	//ip.SetWindowTextA("204.8.177.18");
//	c1.SetCheck(BST_CHECKED);
	//direct_chk.SetCheck(BST_CHECKED);
	lj=new ljwrapper();
	lj->log=&mylog;
	//AfxSocketInit();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CjehyDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

HCURSOR CjehyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CjehyDlg::freeze(bool disable)
{
	if(disable)
	{
		//if(runbutton)
		GetDlgItem(IDC_BUTTON4)->EnableWindow(0);
		GetDlgItem(IDC_BUTTON8)->EnableWindow(0);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(0);
		GetDlgItem(IDC_BUTTON6)->EnableWindow(0);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(0);
		GetDlgItem(IDCANCEL)->EnableWindow(0);
		GetDlgItem(IDOK)->EnableWindow(0);
	}
	else
	{
		//if(runbutton)
		GetDlgItem(IDC_BUTTON4)->EnableWindow(1);
		GetDlgItem(IDC_BUTTON8)->EnableWindow(1);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(1);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(1);
		GetDlgItem(IDC_BUTTON6)->EnableWindow(1);
		GetDlgItem(IDCANCEL)->EnableWindow(1);
		GetDlgItem(IDOK)->EnableWindow(1);
	}
}






void CjehyDlg::OnClose()
{
	delete(lj);
	CDialog::OnClose();
}


void CjehyDlg::OnBnClickedOk()
{
	PostMessage(WM_CLOSE,0,0);
	//OnOK();
}


//void CjehyDlg::OnEnChangeEdit4()
//{
//	CString temp;
//	hostname.GetWindowTextA(temp);
//	if(temp.GetLength()>0)
//	{
//		c1.SetCheck(BST_CHECKED);
//		c2.SetCheck(BST_UNCHECKED);
//	}
//	else
//	{
//		c1.SetCheck(BST_UNCHECKED);
//		c2.SetCheck(BST_CHECKED);
//	}
//}
/*
void CjehyDlg::OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	CString temp;
	ip.GetWindowTextA(temp);
	if(temp.GetLength()>0)
	{
		c2.SetCheck(BST_CHECKED);
		c1.SetCheck(BST_UNCHECKED);
	}
	else
	{
		c2.SetCheck(BST_UNCHECKED);
		c1.SetCheck(BST_CHECKED);
	}
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	*pResult = 0;
}*/
void CjehyDlg::OnBnClickedButton4()
{
	freeze(1);
	CString hs,ps;
	hostname.GetWindowTextA(hs);
	port.GetWindowTextA(ps);
	int z=lj->Connect(hs.GetBuffer(),ps.GetBuffer());
	if(z)
	{
		CString u,p;
		user.GetWindowTextA(u);
		pass.GetWindowTextA(p);
		lj->Login(u.GetBuffer(),p.GetBuffer(),hs.GetBuffer());
	}
	lj->Disconnect();
	freeze(0);
	/*
OnBnClickedButton3();//Sleep(1000);
int recip=threads.GetCurSel();
if(recip==1)recip=MAIN_THREAD_ID;
else if(recip==0)recip=ALL_THREADS_ID;
else recip-=2;
CString hostname,ipstring,port;
GetDlgItem(IDC_EDIT4)->GetWindowTextA(hostname);
GetDlgItem(IDC_IPADDRESS1)->GetWindowTextA(ipstring);
GetDlgItem(IDC_EDIT2)->GetWindowTextA(port);
int z=SendTcpIpMessage(hostname,ipstring,port,TYPE_EVENT,recip,SENDFILE,NULL);
if(z==0)
	addlog("Sendfile event sucessfully sent!",0);
else adderr(z);
freeze(0,1);*/
}


void CjehyDlg::OnEnUpdateEdit1()
{
	proxy_chk.SetCheck(BST_CHECKED);
	direct_chk.SetCheck(BST_UNCHECKED);
}


void CjehyDlg::OnBnClickedCheck3()
{
	direct_chk.SetCheck(BST_UNCHECKED);
}

void CjehyDlg::OnBnClickedCheck4()
{
	proxy_chk.SetCheck(BST_UNCHECKED);
}


//void CjehyDlg::OnBnClickedCheck1()
//{
//	c2.SetCheck(BST_UNCHECKED);
//}

//void CjehyDlg::OnBnClickedCheck2()
//{
//	c1.SetCheck(BST_UNCHECKED);
//}

void CjehyDlg::OnBnClickedButton1()
{
	mylog.SetWindowTextA("");
	// TODO: Add your control notification handler code here
}

void CjehyDlg::OnBnClickedButton8()
{
cv(0);
}

void CjehyDlg::OnBnClickedButton2()
{
	help* d=new help();
	delete(d);
}

void CjehyDlg::OnBnClickedButton3()
{
cv(1);
}

void CjehyDlg::OnBnClickedButton6()
{
cv(2);
}
void CjehyDlg::cv(int how)
{
	freeze(1);
	CString hs,ps,s;
	hostname.GetWindowTextA(hs);
	port.GetWindowTextA(ps);
	int Fromday,Frommonth,Fromyear,Today,Tomonth,Toyear;
	fromday.GetWindowTextA(s);
	Fromday=atoi(s.GetBuffer());
	frommonth.GetWindowTextA(s);
	Frommonth=atoi(s.GetBuffer());
	fromyear.GetWindowTextA(s);
	Fromyear=atoi(s.GetBuffer());
	today.GetWindowTextA(s);
	Today=atoi(s.GetBuffer());
	tomonth.GetWindowTextA(s);
	Tomonth=atoi(s.GetBuffer());
	toyear.GetWindowTextA(s);
	Toyear=atoi(s.GetBuffer());
	int z=lj->Connect(hs.GetBuffer(),ps.GetBuffer());
	if(z)
	{
		lj->ChangePostsVisibility(how,Fromday,Frommonth,Fromyear,Today,Tomonth,Toyear);
	}
	lj->Disconnect();
	freeze(0);
}
