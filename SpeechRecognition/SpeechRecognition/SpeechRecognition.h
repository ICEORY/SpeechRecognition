
// SpeechRecognition.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSpeechRecognitionApp:
// �йش����ʵ�֣������ SpeechRecognition.cpp
//

class CSpeechRecognitionApp : public CWinApp
{
public:
	CSpeechRecognitionApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSpeechRecognitionApp theApp;