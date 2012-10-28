// jehyDlg.h : header file

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
// CjehyDlg dialog
class CjehyDlg : public CDialog
{
// Construction
public:
	CjehyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_JEHY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
public:
	afx_msg void OnBnClickedOk();
public:
	void freeze(bool disable);
//public:
	//void adderr(int err_code);
public:
	CEdit mylog;
public:
//	afx_msg void OnEnChangeEdit4();
//public:
	//CButton c1;
//public:
	//CButton c2;
public:
	afx_msg void OnBnClickedButton4();
public:
	CButton direct_chk;
public:
	CButton proxy_chk;
public:
public:
	afx_msg void OnEnUpdateEdit1();
public:
	CEdit hostname;
//public:
	//CIPAddressCtrl ip;
public:
	CEdit port;
public:
	CEdit proxy_addr;
//public:
//	afx_msg void OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedCheck3();
public:
	afx_msg void OnBnClickedCheck4();
public:
//	afx_msg void OnBnClickedCheck1();
//public:
	//afx_msg void OnBnClickedCheck1();
//public:
	//afx_msg void OnBnClickedCheck2();
public:
	CEdit user;
public:
	CEdit pass;
public:
	afx_msg void OnBnClickedButton1();
public:
	afx_msg void OnBnClickedButton8();
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton6();
	CEdit fromday;
	CEdit frommonth;
	CEdit fromyear;
	CEdit today;
	CEdit tomonth;
	CEdit toyear;
	void cv(int how);
};
