
// SpeechRecognitionDlg.cpp : 实现文件
//

#include "stdafx.h"

#include <stdio.h>
#include <string.h>

//以下三个语句用于引入matlab相关链接库
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CSpeechRecognitionDlg 对话框




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

BEGIN_MESSAGE_MAP(CSpeechRecognitionDlg, CDialogEx)//此处将消息加入队列，倘若目标消息没有跳入函数，可能是没加入消息队列中
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPENPORT, &CSpeechRecognitionDlg::OnBnClickedBtnOpenport)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO1, &CSpeechRecognitionDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CSpeechRecognitionDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CSpeechRecognitionDlg 消息处理程序

BOOL CSpeechRecognitionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	initial();



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。


/***************************************
函数onpaint()用于窗口缩小后的图像重绘，是缩小前与缩小后没有区别
****************************************/
void CSpeechRecognitionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
/***************************以下是增加的语句******************************************************/
	CDC *pDC=GetDC();//获取绘图设备的句柄

	pDC->FillRect(CRect(20,65,700,315),&CBrush(RGB(255,255,255)));//动态曲线显示区的初始化操作，绘制白色背景
	pDC->MoveTo(20,65);
	pDC->LineTo(20,315);
	pDC->MoveTo(700,65);
	pDC->LineTo(700,315);

	int temp_count=m_count;//获取当前采集到第几个数据
	int temp_draw_count=m_draw_count;//获取当前在绘图区绘制到第几个数据
	bool temp_judge=false;//用于判断是否重绘结束
	//重绘函数的主体
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSpeechRecognitionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/***********************************************************
函数initial()用于对话框开始时对数据的初始化，在对话框的初始化函数里面调用
************************************************************/
void CSpeechRecognitionDlg::initial()
{
	m_combobox.SetCurSel(0);//初始化COMBOBX列表
	m_count=0;//采集数据个数的计数初始化
	m_draw_count=0;//绘图数据个数的初始化
	m_btn_status=0;//按键状态初始化，用于改变“打开串口”按钮的字幕以及决定执行程序
	m_lastdata=0;//上一个数据，用于绘图
	m_max_datalength=1000;
	m_radio_train=false;//测试模式选择初始化
	m_radio_online=false;//测试模式选择初始化

	m_voice_data=new double[m_max_datalength];
	m_matdata_flashing=new double[m_max_datalength];
	//储存mat文件的名称的初始化
	//pmat_name="VoiceData.mat";
	//pmat_name="TestData.mat";
	pmat_name="2013-10-2-data3.mat";
}



void CSpeechRecognitionDlg::OnBnClickedBtnOpenport()
{
	
	// TODO: Add your control notification handler code here
	Engine *mateng=engOpen(NULL);
	engEvalString(mateng,"DATAFFT();");
	if(m_radio_train==false && m_radio_online==false)//判断是否已经进行模式选择
	{
		MessageBox(L"请选择工作模式",MB_OK);
	}
	else
	{
		if(!m_btn_status)//判断此时按钮状态，如果为false则开始执行数据采集的相关程序
		{
			//建立Mat文件
			pmat=matOpen(pmat_name,"w");
			if(pmat==NULL)
			{
				MessageBox(L"error open mat file",MB_OK);
			}
			
			m_portnumber=m_combobox.GetCurSel();//获得COMBOBOX中串口目标
			if(m_MSComm.GetPortOpen())//判断COM口是否打开，是则关闭
			{
				m_MSComm.SetPortOpen(FALSE);
			}
			
			//COM口初始化设置
			m_MSComm.SetCommPort(m_portnumber);
			m_MSComm.SetInBufferSize(1024);
			m_MSComm.SetInputLen(4);
			m_MSComm.SetInputMode(0);
			m_MSComm.SetRThreshold(1);
			m_MSComm.SetSettings(L"9600,n,8,1");
			m_MSComm.SetOutBufferCount(0);
			m_MSComm.SetInBufferCount(0);

			if(!m_MSComm.GetPortOpen())//初始化完毕后打开串口
			{
				m_MSComm.SetPortOpen(TRUE);
			}
			
			CWnd *p_wnd=GetDlgItem(IDC_BTN_OPENPORT);
			p_wnd->SetWindowTextW(_T("关闭串口"));			
			m_btn_status=true;

			//判断此时选择的工作模式，如果是train模式，则开启子窗口
			if(m_radio_train)
			{
				//SetTimer(1,10,NULL);//用于没有硬件采集时的程序测试，定时产生数据代替硬件采集
				m_dlg_train.Create(IDD_DLG_TRAIN);
				m_dlg_train.ShowWindow(SW_SHOW);
				m_dlg_train.m_dlg_close=false;
				
			}
		}
		else
		{
			//KillTimer(1);//关闭窗口时关闭定时器

			//关闭mat文件
			if(matClose(pmat))
			{
				MessageBox(L"error close file",MB_OK);
			}
			
			//关闭串口
			if(m_MSComm.GetPortOpen())
			{
				m_MSComm.SetPortOpen(FALSE);
			}
			//清空串口接收缓存区
			m_MSComm.SetInBufferCount(0);
			
			//改变按钮状态
			CWnd *p_wnd=GetDlgItem(IDC_BTN_OPENPORT);
			p_wnd->SetWindowTextW(_T("打开串口"));
			m_btn_status=false;
			//在train模式下仍需关闭子窗口
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
	m_receive=m_MSComm.GetInput();//获得数据
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
		//获得采样频率
		if(m_getfs.GetFs(m_count))
		{
			m_edit_fs_show=m_getfs.m_string_fs;
			m_getfs.Initialize();
			UpdateData(false);
		}
		//获得绘图设备句柄
		CDC *pDC=GetDC();

		//train模式下的工作程序
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

				m_voice_data[m_count]=_ttoi(m_receive);//数据转换
				//在绘图区绘图
				pDC->FillRect(CRect(21+m_draw_count,65,23+m_draw_count,315),&CBrush(RGB(255,255,255)));
				pDC->MoveTo(20+m_draw_count,315-m_lastdata);
				pDC->LineTo(21+m_draw_count,315-m_voice_data[m_count]);
				m_lastdata=m_voice_data[m_count];
				m_draw_count++;
				m_count++;
				m_data_show=m_receive;
				UpdateData(FALSE);//更新EDITBOX中数据
			}
			if(m_dlg_train.m_dlg_close)
			{
				SaveDataToMat(m_count);
			}
		}
		//online模式下的工作程序
		else
		{
			m_voice_data[m_count]=_ttoi(m_receive);//数据转换

			pDC->FillRect(CRect(21+m_draw_count,65,23+m_draw_count,315),&CBrush(RGB(255,255,255)));
			if(m_count==0)m_lastdata=m_voice_data[m_count];
			pDC->MoveTo(20+m_draw_count,315-m_lastdata);
			pDC->LineTo(21+m_draw_count,315-m_voice_data[m_count]);
			m_lastdata=m_voice_data[m_count];
			m_draw_count++;
			m_count++;
			m_data_show=m_receive;
			UpdateData(FALSE);//更新EDITBOX中数据
		}
		if(m_draw_count>=677)m_draw_count=0;
		//此处需要改进，功能是储存变量到mat文件中
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
函数ontimer()用于定时产生数据，以代替硬件产生数据
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
		//仿照数据采集部分，储存数据到mat文件中
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
		//绘图处理，显示数据形成的图像，动态曲线
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


void CSpeechRecognitionDlg::OnBnClickedRadio1()//用于改变单选框的状态
{
	m_radio_train=false;
	m_radio_online=true;
	// TODO: Add your control notification handler code here
}


void CSpeechRecognitionDlg::OnBnClickedRadio2()//用于改变单选框的状态
{
	m_radio_train=true;
	m_radio_online=false;
	// TODO: Add your control notification handler code here
}
void CSpeechRecognitionDlg::SaveDataToMat(int length)
{
		mxArray *p_array_data,*p_array_flashing;//定义两个array的数组指针				
		p_array_data=mxCreateDoubleMatrix(1,length,mxREAL);
		p_array_flashing=mxCreateDoubleMatrix(1,length,mxREAL);//创建两个数组用于储存数据

		memcpy((void*)(mxGetPr(p_array_data)),(void*)m_voice_data,length*sizeof(double));
		memcpy((void*)(mxGetPr(p_array_flashing)),(void*)m_matdata_flashing,length*sizeof(double));//把数据拷贝到ARRAY数组空间

		//把ARRAY数组保存在PMAT指针指向的MAT文件中
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
	m_count=0;//采集数据个数的计数初始化
	m_draw_count=0;//绘图数据个数的初始化
	m_lastdata=0;//上一个数据，用于绘图
	m_max_datalength=1000;
	free(m_voice_data);
	free(m_matdata_flashing);
	m_voice_data=new double[m_max_datalength];
	m_matdata_flashing=new double[m_max_datalength];
}