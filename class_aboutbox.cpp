// lass_aboutbox.cpp : implementation file
//

#include "stdafx.h"
#include "lass_aboutbox.h"


// class_aboutbox dialog

IMPLEMENT_DYNAMIC(class_aboutbox, CDialog)

class_aboutbox::class_aboutbox(CWnd* pParent /*=NULL*/)
	: CDialog(class_aboutbox::IDD, pParent)
{

}

class_aboutbox::~class_aboutbox()
{
}

void class_aboutbox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(class_aboutbox, CDialog)
END_MESSAGE_MAP()


// class_aboutbox message handlers
