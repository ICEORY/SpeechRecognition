
// SpeechRecognitionDlg.h : ͷ�ļ�
//

#pragma once
#include "mscomm.h"
#include "afxwin.h"
#include "TrainDlg.h"
#include "engine.h"
#include "mat.h"
#include "TimeGetFs.h"

// CSpeechRecognitionDlg �Ի���
class CSpeechRecognitionDlg : public CDialogEx
{
// ����
public:
	CSpeechRecognitionDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SPEECHRECOGNITION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
//������ӵĶ���
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
