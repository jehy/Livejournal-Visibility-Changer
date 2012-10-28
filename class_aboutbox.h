#pragma once


// class_aboutbox dialog

class class_aboutbox : public CDialog
{
	DECLARE_DYNAMIC(class_aboutbox)

public:
	class_aboutbox(CWnd* pParent = NULL);   // standard constructor
	virtual ~class_aboutbox();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
