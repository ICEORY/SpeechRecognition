// TimeGetFs.cpp : implementation file
//

#include "stdafx.h"
#include "SpeechRecognition.h"
#include "TimeGetFs.h"


// CTimeGetFs

IMPLEMENT_DYNAMIC(CTimeGetFs, CWnd)

CTimeGetFs::CTimeGetFs()
{
	Initialize();
}

CTimeGetFs::~CTimeGetFs()
{
}


BEGIN_MESSAGE_MAP(CTimeGetFs, CWnd)
END_MESSAGE_MAP()



// CTimeGetFs message handlers
void CTimeGetFs::Initialize()
{
	m_string_fs="";
	m_second_last=0;
	m_milisecond_new=0;
	m_milisecond_last=0;
	m_second_new=0;
	m_start=false;
	m_count_last=0;
	m_count_new=0;
	m_int_fs=0;
}
bool CTimeGetFs::GetFs(int count)
{
	if(!m_start)
	{
		GetSystemTime(&m_time);
		m_milisecond_last=m_time.wMilliseconds;
		m_second_last=m_time.wSecond;
		if(m_second_last<=58)
		{
			m_count_last=count;
			m_start=true;
		}
		return false;
	}
	else
	{
		if(m_start)
		{
			GetSystemTime(&m_time);
			m_milisecond_new=m_time.wMilliseconds;
			m_second_new=m_time.wSecond;
			m_count_new=count;
			if(m_second_new>m_second_last && m_milisecond_new>=m_milisecond_last)
			{
				m_int_fs=m_count_new-m_count_last;
				m_string_fs.Format(_T("%d"),m_int_fs);
				m_start=false;
				return true;
			}
			else return false;
		}
		else return false;
	}
}

