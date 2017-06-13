
// SpeechRecognitionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include <stdio.h>
#include <string.h>

//�������������������matlab������ӿ�
#pragma comment(lib,"libmat.lib")
#pragma comment(lib,"libmx.lib")
#pragma comment(lib,"libeng.lib")


#include "SpeechRecognition.h"
#include "SpeechRecognitionDlg.h"
#include "afxdialogex.h"
#include <cmath>

#pragma comment(lib,"libmex.lib")
#define BUFSIZE 256
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSpeechRecognitionDlg �Ի���




CSpeechRecognitionDlg::CSpeechRecognitionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSpeechRecognitionDlg::IDD, pParent)
	, m_data_show(_T(""))
	, m_edit_fs_show(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpeechRecognitionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM, m_MSComm);
	DDX_Control(pDX, IDC_SET_PORTNUM, m_combobox);
	DDX_Text(pDX, IDC_DATA_SHOW, m_data_show);
	DDX_Text(pDX, IDC_FS_SHOW, m_edit_fs_show);
}

BEGIN_MESSAGE_MAP(CSpeechRecognitionDlg, CDialogEx)//�˴�����Ϣ������У�����Ŀ����Ϣû�����뺯����������û������Ϣ������
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPENPORT, &CSpeechRecognitionDlg::OnBnClickedBtnOpenport)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO1, &CSpeechRecognitionDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CSpeechRecognitionDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CSpeechRecognitionDlg ��Ϣ�������

BOOL CSpeechRecognitionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	initial();



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSpeechRecognitionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�


/***************************************
����onpaint()���ڴ�����С���ͼ���ػ棬����Сǰ����С��û������
****************************************/
void CSpeechRecognitionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
/***************************���������ӵ����******************************************************/
	CDC *pDC=GetDC();//��ȡ��ͼ�豸�ľ��

	pDC->FillRect(CRect(20,65,700,315),&CBrush(RGB(255,255,255)));//��̬������ʾ���ĳ�ʼ�����������ư�ɫ����
	pDC->MoveTo(20,65);
	pDC->LineTo(20,315);
	pDC->MoveTo(700,65);
	pDC->LineTo(700,315);

	int temp_count=m_count;//��ȡ��ǰ�ɼ����ڼ�������
	int temp_draw_count=m_draw_count;//��ȡ��ǰ�ڻ�ͼ�����Ƶ��ڼ�������
	bool temp_judge=false;//�����ж��Ƿ��ػ����
	//�ػ溯��������
	while(1)
	{
		if(!temp_count||(temp_draw_count==m_draw_count&&temp_judge))break;
		if(!temp_draw_count)
		{
			temp_draw_count=677;
			temp_judge=true;
		}
		pDC->MoveTo(20+temp_draw_count,315-m_voice_data[temp_count-1]);
		pDC->LineTo(19+temp_draw_count,315-m_voice_data[temp_count-2]);
		temp_count--;
		temp_draw_count--;

	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSpeechRecognitionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/***********************************************************
����initial()���ڶԻ���ʼʱ�����ݵĳ�ʼ�����ڶԻ���ĳ�ʼ�������������
************************************************************/
void CSpeechRecognitionDlg::initial()
{
	m_combobox.SetCurSel(0);//��ʼ��COMBOBX�б�
	m_count=0;//�ɼ����ݸ����ļ�����ʼ��
	m_draw_count=0;//��ͼ���ݸ����ĳ�ʼ��
	m_btn_status=0;//����״̬��ʼ�������ڸı䡰�򿪴��ڡ���ť����Ļ�Լ�����ִ�г���
	m_lastdata=0;//��һ�����ݣ����ڻ�ͼ
	m_max_datalength=1000;
	m_radio_train=false;//����ģʽѡ���ʼ��
	m_radio_online=false;//����ģʽѡ���ʼ��

	m_voice_data=new double[m_max_datalength];
	m_matdata_flashing=new double[m_max_datalength];
	//����mat�ļ������Ƶĳ�ʼ��
	//pmat_name="VoiceData.mat";
	//pmat_name="TestData.mat";
	pmat_name="2013-10-2-data3.mat";
}



void CSpeechRecognitionDlg::OnBnClickedBtnOpenport()
{
	
	// TODO: Add your control notification handler code here
	Engine *mateng=engOpen(NULL);
	engEvalString(mateng,"DATAFFT();");
	if(m_radio_train==false && m_radio_online==false)//�ж��Ƿ��Ѿ�����ģʽѡ��
	{
		MessageBox(L"��ѡ����ģʽ",MB_OK);
	}
	else
	{
		if(!m_btn_status)//�жϴ�ʱ��ť״̬�����Ϊfalse��ʼִ�����ݲɼ�����س���
		{
			//����Mat�ļ�
			pmat=matOpen(pmat_name,"w");
			if(pmat==NULL)
			{
				MessageBox(L"error open mat file",MB_OK);
			}
			
			m_portnumber=m_combobox.GetCurSel();//���COMBOBOX�д���Ŀ��
			if(m_MSComm.GetPortOpen())//�ж�COM���Ƿ�򿪣�����ر�
			{
				m_MSComm.SetPortOpen(FALSE);
			}
			
			//COM�ڳ�ʼ������
			m_MSComm.SetCommPort(m_portnumber);
			m_MSComm.SetInBufferSize(1024);
			m_MSComm.SetInputLen(4);
			m_MSComm.SetInputMode(0);
			m_MSComm.SetRThreshold(1);
			m_MSComm.SetSettings(L"9600,n,8,1");
			m_MSComm.SetOutBufferCount(0);
			m_MSComm.SetInBufferCount(0);

			if(!m_MSComm.GetPortOpen())//��ʼ����Ϻ�򿪴���
			{
				m_MSComm.SetPortOpen(TRUE);
			}
			
			CWnd *p_wnd=GetDlgItem(IDC_BTN_OPENPORT);
			p_wnd->SetWindowTextW(_T("�رմ���"));			
			m_btn_status=true;

			//�жϴ�ʱѡ��Ĺ���ģʽ�������trainģʽ�������Ӵ���
			if(m_radio_train)
			{
				//SetTimer(1,10,NULL);//����û��Ӳ���ɼ�ʱ�ĳ�����ԣ���ʱ�������ݴ���Ӳ���ɼ�
				m_dlg_train.Create(IDD_DLG_TRAIN);
				m_dlg_train.ShowWindow(SW_SHOW);
				m_dlg_train.m_dlg_close=false;
				
			}
		}
		else
		{
			//KillTimer(1);//�رմ���ʱ�رն�ʱ��

			//�ر�mat�ļ�
			if(matClose(pmat))
			{
				MessageBox(L"error close file",MB_OK);
			}
			
			//�رմ���
			if(m_MSComm.GetPortOpen())
			{
				m_MSComm.SetPortOpen(FALSE);
			}
			//��մ��ڽ��ջ�����
			m_MSComm.SetInBufferCount(0);
			
			//�ı䰴ť״̬
			CWnd *p_wnd=GetDlgItem(IDC_BTN_OPENPORT);
			p_wnd->SetWindowTextW(_T("�򿪴���"));
			m_btn_status=false;
			//��trainģʽ������ر��Ӵ���
			if(m_radio_train)
			{
				m_dlg_train.DestroyWindow();
			}
			ClosePort();
		}
	}
}
BEGIN_EVENTSINK_MAP(CSpeechRecognitionDlg, CDialogEx)
	ON_EVENT(CSpeechRecognitionDlg, IDC_MSCOMM, 1, CSpeechRecognitionDlg::OnCommMscomm, VTS_NONE)
END_EVENTSINK_MAP()


void CSpeechRecognitionDlg::OnCommMscomm()
{
	// TODO: Add your message handler code here
	m_receive=m_MSComm.GetInput();//�������
	CString str=m_receive;
	/*if(str.Left(1)!='A')
	{
		//m_MSComm.SetPortOpen(FALSE);
		Sleep(1);
		m_MSComm.SetInBufferCount(0);
		//m_MSComm.SetPortOpen(TRUE);
	}
	else
	{*/
		m_receive=m_receive.Right(3);
		m_MSComm.SetInBufferCount(0);
		//��ò���Ƶ��
		if(m_getfs.GetFs(m_count))
		{
			m_edit_fs_show=m_getfs.m_string_fs;
			m_getfs.Initialize();
			UpdateData(false);
		}
		//��û�ͼ�豸���
		CDC *pDC=GetDC();

		//trainģʽ�µĹ�������
		if(m_radio_train)
		{
			if(m_dlg_train.m_train_begin)
			{
				if(m_dlg_train.m_dlg_teston)
				{
	
					m_matdata_flashing[m_count]=1;
				}
				else 
				{
					m_matdata_flashing[m_count]=0;
				}

				m_voice_data[m_count]=_ttoi(m_receive);//����ת��
				//�ڻ�ͼ����ͼ
				pDC->FillRect(CRect(21+m_draw_count,65,23+m_draw_count,315),&CBrush(RGB(255,255,255)));
				pDC->MoveTo(20+m_draw_count,315-m_lastdata);
				pDC->LineTo(21+m_draw_count,315-m_voice_data[m_count]);
				m_lastdata=m_voice_data[m_count];
				m_draw_count++;
				m_count++;
				m_data_show=m_receive;
				UpdateData(FALSE);//����EDITBOX������
			}
			if(m_dlg_train.m_dlg_close)
			{
				SaveDataToMat(m_count);
			}
		}
		//onlineģʽ�µĹ�������
		else
		{
			m_voice_data[m_count]=_ttoi(m_receive);//����ת��

			pDC->FillRect(CRect(21+m_draw_count,65,23+m_draw_count,315),&CBrush(RGB(255,255,255)));
			if(m_count==0)m_lastdata=m_voice_data[m_count];
			pDC->MoveTo(20+m_draw_count,315-m_lastdata);
			pDC->LineTo(21+m_draw_count,315-m_voice_data[m_count]);
			m_lastdata=m_voice_data[m_count];
			m_draw_count++;
			m_count++;
			m_data_show=m_receive;
			UpdateData(FALSE);//����EDITBOX������
		}
		if(m_draw_count>=677)m_draw_count=0;
		//�˴���Ҫ�Ľ��������Ǵ��������mat�ļ���
		if(m_count>=m_max_datalength)
		{
			SaveDataToMat(m_max_datalength);
			m_max_datalength+=1000;
			m_voice_data=(double*)realloc(m_voice_data,m_max_datalength*sizeof(double));
			m_matdata_flashing=(double*)realloc(m_matdata_flashing,m_max_datalength*sizeof(double));		
		}	
	//}
}

/***********************************************************************
����ontimer()���ڶ�ʱ�������ݣ��Դ���Ӳ����������
************************************************************************/
void CSpeechRecognitionDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==1&&m_dlg_train.m_train_begin)
	{
		int temp=0;
		if(m_getfs.GetFs(m_count))
		{
			m_edit_fs_show=m_getfs.m_string_fs;
			m_getfs.Initialize();
			UpdateData(false);
		}
		/*if(m_count%2==0)
		{
			GetSystemTime(&m_time);
			m_time_last=m_time.wMilliseconds;
		}
		else
		{
			if(m_count%2==1)
			{
				GetSystemTime(&m_time);
				m_time_new=m_time.wMilliseconds;
				if(m_time_new-m_time_last>0)
				{
					m_fs=1000/(m_time_new-m_time_last);
				}
				else
				{
					m_fs=1000/(1000+m_time_new-m_time_last);
				}
				CString str;
				str.Format(_T("%d"),m_fs);
				m_edit_fs_show=str;
				UpdateData(FALSE);
			}
		}*/
		if(m_dlg_train.m_dlg_teston)
		{
			temp=rand()%254+1;
			m_matdata_flashing[m_count]=1;
		}
		else 
		{
			temp=100+60*sin(double(m_draw_count)/10);
			m_matdata_flashing[m_count]=0;
		}
		m_voice_data[m_count]=temp;
		if(!m_count)m_lastdata=temp;
		m_count++;
		//�������ݲɼ����֣��������ݵ�mat�ļ���
		if(m_count>=m_max_datalength)
		{
			SaveDataToMat(m_max_datalength);
			m_max_datalength+=1000;
			m_voice_data=(double*)realloc(m_voice_data,m_max_datalength*sizeof(double));
			m_matdata_flashing=(double*)realloc(m_matdata_flashing,m_max_datalength*sizeof(double));
			/*
			m_count=0;
			mxArray *p_array_data,*p_array_flashing;			
			
			p_array_data=mxCreateDoubleMatrix(1,8000,mxREAL);
			p_array_flashing=mxCreateDoubleMatrix(1,8000,mxREAL);
			memcpy((void*)(mxGetPr(p_array_data)),(void*)m_voice_data,sizeof(m_voice_data));
			memcpy((void*)(mxGetPr(p_array_flashing)),(void*)m_matdata_flashing,sizeof(m_matdata_flashing));
			if(matPutVariable(pmat,"DATA",p_array_data))
			{
				MessageBox(L"error operater",MB_OK);
			}

			if(matPutVariable(pmat,"Flashing",p_array_flashing))
			{
				MessageBox(L"error operater",MB_OK);
			}
			mxDestroyArray(p_array_data);		
			mxDestroyArray(p_array_flashing);
			MessageBox(L"LOAD DATA INTO THE MAT FILE SUCCESSED",MB_OK);
			m_MSComm.SetInBufferCount(0);
			*/
		}
		//��ͼ������ʾ�����γɵ�ͼ�񣬶�̬����
		CDC *pDC=GetDC();
		pDC->FillRect(CRect(21+m_draw_count,65,23+m_draw_count,315),&CBrush(RGB(255,255,255)));
		pDC->MoveTo(20+m_draw_count,315-m_lastdata);
		pDC->LineTo(21+m_draw_count,315-temp);
		m_draw_count++;
		if(m_draw_count>=677)m_draw_count=0;
		m_lastdata=temp;
	}
	if(nIDEvent==1 && m_dlg_train.m_dlg_close)
	{
		SaveDataToMat(m_count);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CSpeechRecognitionDlg::OnBnClickedRadio1()//���ڸı䵥ѡ���״̬
{
	m_radio_train=false;
	m_radio_online=true;
	// TODO: Add your control notification handler code here
}


void CSpeechRecognitionDlg::OnBnClickedRadio2()//���ڸı䵥ѡ���״̬
{
	m_radio_train=true;
	m_radio_online=false;
	// TODO: Add your control notification handler code here
}
void CSpeechRecognitionDlg::SaveDataToMat(int length)
{
		mxArray *p_array_data,*p_array_flashing;//��������array������ָ��				
		p_array_data=mxCreateDoubleMatrix(1,length,mxREAL);
		p_array_flashing=mxCreateDoubleMatrix(1,length,mxREAL);//���������������ڴ�������

		memcpy((void*)(mxGetPr(p_array_data)),(void*)m_voice_data,length*sizeof(double));
		memcpy((void*)(mxGetPr(p_array_flashing)),(void*)m_matdata_flashing,length*sizeof(double));//�����ݿ�����ARRAY����ռ�

		//��ARRAY���鱣����PMATָ��ָ���MAT�ļ���
		if(matPutVariable(pmat,"Data",p_array_data))
		{
			MessageBox(L"error operater",MB_OK);
		}

		if(matPutVariable(pmat,"Flashing",p_array_flashing))
		{
			MessageBox(L"error operater",MB_OK);
		}
		mxDestroyArray(p_array_data);		
		mxDestroyArray(p_array_flashing);
		//MessageBox(L"LOAD DATA INTO THE MAT FILE SUCCESSED",MB_OK);
}
void CSpeechRecognitionDlg::ClosePort()
{
	m_count=0;//�ɼ����ݸ����ļ�����ʼ��
	m_draw_count=0;//��ͼ���ݸ����ĳ�ʼ��
	m_lastdata=0;//��һ�����ݣ����ڻ�ͼ
	m_max_datalength=1000;
	free(m_voice_data);
	free(m_matdata_flashing);
	m_voice_data=new double[m_max_datalength];
	m_matdata_flashing=new double[m_max_datalength];
}