#pragma once


// CTimeGetFs

class CTimeGetFs : public CWnd
{
	DECLARE_DYNAMIC(CTimeGetFs)

public:
	CTimeGetFs();
	virtual ~CTimeGetFs();

protected:
	DECLARE_MESSAGE_MAP()

public:
	SYSTEMTIME m_time;
	int m_second_last, m_second_new,m_milisecond_last,m_milisecond_new;;
	void Initialize();
	bool GetFs(int count);
	bool m_start;
	int m_count_last;
	int m_count_new;
	CString m_string_fs;
	int m_int_fs;
};


