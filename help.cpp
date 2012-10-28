// help.cpp : implementation file
//

#include "stdafx.h"
#include "help.h"


// help dialog

IMPLEMENT_DYNAMIC(help, CDialog)

help::help(CWnd* pParent /*=NULL*/)
	: CDialog(help::IDD, pParent)
{
	this->DoModal();
}

help::~help()
{
}

void help::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(help, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &help::OnBnClickedButton1)
END_MESSAGE_MAP()


// help message handlers

void help::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
}
