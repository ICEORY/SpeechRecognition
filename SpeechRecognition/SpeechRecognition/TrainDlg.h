#pragma once
#include "afxwin.h"


// CTrainDlg dialog

class CTrainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTrainDlg)

public:
	CTrainDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTrainDlg();

// Dialog Data
	enum { IDD = IDD_DLG_TRAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSetbigin();
protected:
	CString m_edit_tipshow;
	CBitmap m_bmp_time[3];//
	CDC m_cdc_time[3];//
	int m_time_count;
	void Initialize();
	int m_train_step;
public:
	CButton m_btn_control;
	bool m_dlg_teston,m_train_begin,m_dlg_close;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
