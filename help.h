#pragma once
#include "Resource.h"

// help dialog

class help : public CDialog
{
	DECLARE_DYNAMIC(help)

public:
	help(CWnd* pParent = NULL);   // standard constructor
	virtual ~help();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
