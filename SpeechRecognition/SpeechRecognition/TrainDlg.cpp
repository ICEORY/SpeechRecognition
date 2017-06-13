// TrainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpeechRecognition.h"
#include "TrainDlg.h"
#include "afxdialogex.h"


// CTrainDlg dialog

IMPLEMENT_DYNAMIC(CTrainDlg, CDialogEx)

CTrainDlg::CTrainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTrainDlg::IDD, pParent)
	, m_edit_tipshow(_T(""))
{
	Initialize();
}

CTrainDlg::~CTrainDlg()
{
}

void CTrainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TIPS, m_edit_tipshow);
	DDX_Control(pDX, IDC_BTN_SETBIGIN, m_btn_control);
}


BEGIN_MESSAGE_MAP(CTrainDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SETBIGIN, &CTrainDlg::OnBnClickedBtnSetbigin)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTrainDlg message handlers

void CTrainDlg::Initialize()
{
	m_time_count=0;//���ڼ�ʱ
	m_train_step=0;//��Ӧ��ʱ�������жϲ������е��ڼ�����
	m_dlg_teston=false;//�����ж��Ƿ�ʼĿ�������ɼ�
	m_train_begin=false;//�ж��Ƿ�ʼ����
	//m_dlg_close=false;
}

void CTrainDlg::OnBnClickedBtnSetbigin()
{
	// TODO: Add your control notification handler code here
	if(m_train_step==4)//�رմ���
	{
		Initialize();
		m_edit_tipshow=_T("");
		UpdateData(FALSE);
		m_dlg_close=true;
		this->OnOK();
	}
	else
	{
		SetTimer(0,1000,NULL);
		m_dlg_close=false;
		m_train_begin=true;
		//��ȡ��ͼ�豸���������λͼ
		CDC *pDC=GetDC();
		m_bmp_time[0].LoadBitmapW(IDB_BMP_TIME1);
		m_bmp_time[1].LoadBitmapW(IDB_BMP_TIME2);
		m_bmp_time[2].LoadBitmapW(IDB_BMP_TIME3);
		for(int i=0;i<3;i++)
		{
			m_cdc_time[i].CreateCompatibleDC(pDC);
			m_cdc_time[i].SelectObject(m_bmp_time[i]);
		}
		//��ʼ����ͼ��
		pDC->FillRect(CRect(40,100,136,196),&CBrush(RGB(0,0,0)));
		m_btn_control.EnableWindow(false);

		//�ֱ�ִ�в�ͬ����ʾ
		switch(m_train_step)
		{
		case 0:
			m_edit_tipshow=_T("��һ�������ڵ���ʱ������������ʱ������ͨ��˵���ϡ�");
			break;
		case 1:
			m_edit_tipshow=_T("�ڶ��������ڵ���ʱ������������ʱ������ͨ��˵���¡�");
			break;
		case 2:
			m_edit_tipshow=_T("�����������ڵ���ʱ������������ʱ������ͨ��˵����");
			break;
		case 3:
			m_edit_tipshow=_T("���Ĳ������ڵ���ʱ������������ʱ������ͨ��˵���ҡ�");
			break;
		}
		UpdateData(FALSE);
	}
}

//���ڶ�ʱ������ʾ���û�������ʾ������������ɲ���
void CTrainDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==0)
	{
		CDC *pDC=GetDC();
		if(m_time_count<=2)
		{
			pDC->BitBlt(40,100,136,196,&m_cdc_time[2-m_time_count],0,0,SRCCOPY);
			m_bmp_time[2-m_time_count].Detach();
			m_cdc_time[2-m_time_count].Detach();
		}
		if(m_time_count==3)
		{
			pDC->FillRect(CRect(40,100,136,196),&CBrush(RGB(0,255,0)));
			m_dlg_teston=true;
		}
		m_time_count++;
		if(m_time_count==6)
		{
			pDC->FillRect(CRect(40,100,136,196),&CBrush(RGB(0,0,0)));
			KillTimer(0);
			m_time_count=0;
			m_train_step++;
			m_dlg_teston=false;
			if(m_train_step==4)
			{
				m_edit_tipshow=_T("���Խ�������رնԻ���");
				m_btn_control.SetWindowTextW(L"�ر�");
			}
			else
			{
				m_btn_control.SetWindowTextW(L"NEXT");
			}
			m_btn_control.EnableWindow(true);
			
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}
