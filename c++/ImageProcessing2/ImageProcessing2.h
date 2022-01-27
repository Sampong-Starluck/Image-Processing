
// ImageProcessing2.h : main header file for the ImageProcessing2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CImageProcessing2App:
// See ImageProcessing2.cpp for the implementation of this class
//

class CImageProcessing2App : public CWinApp
{
public:
	CImageProcessing2App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CImageProcessing2App theApp;
