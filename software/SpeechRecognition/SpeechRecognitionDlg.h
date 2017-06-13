
// SpeechRecognitionDlg.h : 头文件
//

#pragma once
#include "mscomm.h"
#include "afxwin.h"
#include "TrainDlg.h"
#include "engine.h"
#include "mat.h"
#include "TimeGetFs.h"

// CSpeechRecognitionDlg 对话框
class CSpeechRecognitionDlg : public CDialogEx
{
// 构造
public:
	CSpeechRecognitionDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SPEECHRECOGNITION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
//个人添加的东西
public:
	CMscomm m_MSComm;
	CString m_receive;
	int m_portnumber;
	double *m_voice_data;//[8000];
	double *m_matdata_flashing;//[8000];
	int m_count;
	int m_max_datalength;
	int m_draw_count,m_lastdata;
	bool m_btn_status;
	void initial();
	const char *pmat_name;
	afx_msg void OnBnClickedBtnOpenport();
	MATFile *pmat;
	bool m_radio_train,m_radio_online;
protected:
	void SaveDataToMat(int length);
	void ClosePort();
	CTimeGetFs m_getfs;
	CComboBox m_combobox;
	CString m_data_show;
	CTrainDlg m_dlg_train;
public:
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
protected:
	CString m_edit_fs_show;
};
