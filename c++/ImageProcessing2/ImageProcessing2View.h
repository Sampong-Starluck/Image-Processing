
// ImageProcessing2View.h : interface of the CImageProcessing2View class
//

#pragma once
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>

using namespace std;
using namespace cv;
	
class CImageProcessing2View : public CView
{
protected: // create from serialization only
	CImageProcessing2View() noexcept;
	DECLARE_DYNCREATE(CImageProcessing2View)

// Attributes
public:
	CImageProcessing2Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CImageProcessing2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOperationGrayscale();
	afx_msg void OnFileOpen();
	Mat image_source;
	afx_msg void OnFileSave();
	Mat img_save;
	afx_msg void OnOperationInvertcolor();
	afx_msg void OnOperationMirrorimage();
	int width = 960;
	int height = 540;
	afx_msg void OnOperationSobelfilter();
};

#ifndef _DEBUG  // debug version in ImageProcessing2View.cpp
inline CImageProcessing2Doc* CImageProcessing2View::GetDocument() const
   { return reinterpret_cast<CImageProcessing2Doc*>(m_pDocument); }
#endif

