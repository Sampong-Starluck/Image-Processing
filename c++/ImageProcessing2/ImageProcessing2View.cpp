
// ImageProcessing2View.cpp : implementation of the CImageProcessing2View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ImageProcessing2.h"
#endif

#include "ImageProcessing2Doc.h"
#include "ImageProcessing2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessing2View

IMPLEMENT_DYNCREATE(CImageProcessing2View, CView)

BEGIN_MESSAGE_MAP(CImageProcessing2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_OPERATION_GRAYSCALE, &CImageProcessing2View::OnOperationGrayscale)
	ON_COMMAND(ID_FILE_OPEN, &CImageProcessing2View::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CImageProcessing2View::OnFileSave)
	ON_COMMAND(ID_OPERATION_INVERTCOLOR, &CImageProcessing2View::OnOperationInvertcolor)
	ON_COMMAND(ID_OPERATION_MIRRORIMAGE, &CImageProcessing2View::OnOperationMirrorimage)
	ON_COMMAND(ID_OPERATION_SOBELFILTER, &CImageProcessing2View::OnOperationSobelfilter)
END_MESSAGE_MAP()

// CImageProcessing2View construction/destruction

CImageProcessing2View::CImageProcessing2View() noexcept
{
	// TODO: add construction code here
	image_source = 0;
	img_save = 0;
}

CImageProcessing2View::~CImageProcessing2View()
{
	image_source = 0;
	img_save = 0;

	destroyAllWindows();
}

BOOL CImageProcessing2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CImageProcessing2View drawing

void CImageProcessing2View::OnDraw(CDC* /*pDC*/)
{
	CImageProcessing2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CImageProcessing2View printing

BOOL CImageProcessing2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImageProcessing2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImageProcessing2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CImageProcessing2View diagnostics

#ifdef _DEBUG
void CImageProcessing2View::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessing2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessing2Doc* CImageProcessing2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessing2Doc)));
	return (CImageProcessing2Doc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessing2View message handlers


void CImageProcessing2View::OnOperationGrayscale()
{
	// TODO: Create a function to turn RGB image to grayscale image 
	Mat image, newImage, grayImage;

	//image = imread("../resource/test_img.jpg", IMREAD_COLOR);
	image = image_source;
	int red, green, blue;
	//int width = 960, height = 540;// 1920 * 1080??
	resize(image, newImage, Size(width, height));
	Mat lum(newImage.rows, newImage.cols, CV_8UC1, Scalar(0));
		// I = 0.299*R + 0.587*G + 0.114*B
	for (int i = 0; i < newImage.rows; i++)
	{
		for (int j = 0; j < newImage.cols; j++)
		{
			red = newImage.at<Vec3b>(i, j)[2];
			green = newImage.at<Vec3b>(i, j)[1];
			blue = newImage.at<Vec3b>(i, j)[0];

			lum.at<uchar>(i, j) = (0.299 * red + 0.587 * green + 0.114 * blue);
		}
	}

	//cvtColor(newImage, grayImage, COLOR_RGB2GRAY);

	namedWindow("grayscale", WINDOW_AUTOSIZE);
	imshow("grayscale", lum);

	/*namedWindow("GrayImage", WINDOW_AUTOSIZE);
	imshow("GrayImage", grayImage);*/

	waitKey(0);
}



void CImageProcessing2View::OnFileOpen()
{
	// TODO: Add your command handler code here
	CFileDialog dlg(TRUE, _T("*.bmp"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.bmp; *.jpg; *.gif; *.jpeg; *.png; *.tif) |*.bmp;*.jpg; *.gif; *.jpeg; *.png; *.tif|All Files (*.*)|*.*||"), NULL);

	dlg.m_ofn.lpstrTitle = _T("Open an Image");

	if (dlg.DoModal() == IDOK)
	{
		CImageProcessing2Doc* pDoc = GetDocument();
		CString path = dlg.GetPathName(); // contain the selected filename
		char* path_image = new char[path.GetLength() + 1];
		wsprintfA(path_image, "%ls", path);
		String windowName = "Source Image";
		image_source = imread(path_image, IMREAD_COLOR);
		namedWindow(windowName, WINDOW_AUTOSIZE);
		//MessageBox(NULL, (CString)path_image, MB_OK);
		img_save = image_source;
		//int width = 960, height = 540;// 1920 * 1080
		resize(image_source, image_source, Size(width, height));
		imshow(windowName, image_source);
	}
}


void CImageProcessing2View::OnFileSave()
{
	// TODO: Add your command handler code here
	CFileDialog dlg(FALSE, _T("*.bmp"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.bmp; *.jpg; *.gif; *.jpeg; *.png; *.tif) |*.bmp;*.jpg; *.gif; *.jpeg; *.png; *.tif|All Files (*.*)|*.*||"), NULL);

	dlg.m_ofn.lpstrTitle = _T("Save Image");

	if (dlg.DoModal() == IDOK)
	{
		CString file = dlg.GetPathName();
		char* filename = new char[file.GetLength() + 1];
		wsprintfA(filename, "%ls", file);
		imwrite(filename, img_save);
	}
}

void CImageProcessing2View::OnOperationInvertcolor()
{
	// TODO: Add your command handler code here
	Mat image, newImage;
	image = image_source;
	//int width = 960, height = 540;// 1920 * 1080
	int red, green, blue;
	resize(image, newImage, Size(width, height));

	Mat inverted = Mat::zeros(newImage.size(), newImage.type());
	for (int i = 0; i < newImage.rows; i++)
	{
		for (int j = 0; j < newImage.cols; j++)
		{
			red = newImage.at<Vec3b>(i, j)[2];
			green = newImage.at<Vec3b>(i, j)[1];
			blue = newImage.at<Vec3b>(i, j)[0];

			inverted.at<Vec3b>(i, j)[2] = 255 - red;
			inverted.at<Vec3b>(i, j)[1] = 255 - green;
			inverted.at<Vec3b>(i, j)[0] = 255 - blue;
		}
	}

	namedWindow("Invert_Image", WINDOW_AUTOSIZE);
	imshow("Invert_Image", inverted);
}


void CImageProcessing2View::OnOperationMirrorimage()
{
	// TODO: Add your command handler code here
	Mat3b newImage, image;
	image = image_source;
	//int width = 960, height = 540;
	resize(image, newImage, Size(width, height));
	Mat3b mirror(newImage.rows, newImage.cols, CV_8UC3);
	for (int i = 0; i < mirror.rows; i++)
	{
		for (int j = 0; j < mirror.cols; j++)
		{
			mirror(i, j) = newImage(i, newImage.cols - 1 - j);
		}
	}
	namedWindow("Mirror_Image", WINDOW_AUTOSIZE);
	imshow("Mirror_Image", mirror);

}


void CImageProcessing2View::OnOperationSobelfilter()
{
	// TODO: Add your command handler code here
	int MaskSobelX[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };
	int MaskSobelY[3][3] = { {1,2,1},{0,0,0},{-1,-2,-1} };
	Mat img_src = image_source;
	int height = img_src.rows;
	int width = img_src.cols;
	int r, g, b;
	//int* R = nullptr, * G = nullptr, * B = nullptr;
	int mr; // Mask row
	int mc; // Mask column
	int newValueB, newValueG, newValueR;
	int i, j;
	int minB, maxB, minG, maxG, minR, maxR;
	int* pTmpXB, * pTmpYB;
	int* pTmpXG, * pTmpYG;
	int* pTmpXR, * pTmpYR;
	float constBVal1, constBVal2, constGVal1, constGVal2, constRVal1, constRVal2;
	Size size_img;
	size_img.width = img_src.cols;
	size_img.height = img_src.rows;
	Mat mOutImg = Mat(size_img, CV_8UC3);
	//Mat mOutImg = Mat::zeros(size_img, img_src.type());
	pTmpXB = new int[size_img.width * size_img.height];
	pTmpXG = new int[size_img.width * size_img.height];
	pTmpXR = new int[size_img.width * size_img.height];
	pTmpYB = new int[size_img.width * size_img.height];
	pTmpYG = new int[size_img.width * size_img.height];
	pTmpYR = new int[size_img.width * size_img.height];

	mOutImg = 0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			pTmpXB[i * size_img.width + j] = 0;
			pTmpXG[i * size_img.width + j] = 0;
			pTmpXR[i * size_img.width + j] = 0;
			pTmpYB[i * size_img.width + j] = 0;
			pTmpYG[i * size_img.width + j] = 0;
			pTmpYR[i * size_img.width + j] = 0;

		}
	}

	for (i = 1; i < height - 1; i++)
	{
		for (j = 1; j < width - 1; j++)
		{
			newValueB = 0;
			newValueG = 0;
			newValueR = 0;
			for (mr = 0; mr < 3; mr++)
			{
				for (mc = 0; mc < 3; mc++)
				{
					newValueB += MaskSobelX[mr][mc] * img_src.at<Vec3b>(Point(j + mc - 1, i + mr - 1))[0];
					newValueG += MaskSobelX[mr][mc] * img_src.at<Vec3b>(Point(j + mc - 1, i + mr - 1))[1];
					newValueR += MaskSobelX[mr][mc] * img_src.at<Vec3b>(Point(j + mc - 1, i + mr - 1))[2];
				}
			}
			pTmpXB[i * size_img.width + j] = newValueB;
			pTmpXG[i * size_img.width + j] = newValueG;
			pTmpXR[i * size_img.width + j] = newValueR;
		}
	}


	for (i = 1; i < height - 1; i++)
	{
		for (j = 1; j < width - 1; j++)
		{
			newValueB = 0;
			newValueG = 0;
			newValueR = 0;
			for (mr = 0; mr < 3; mr++)
			{
				for (mc = 0; mc < 3; mc++)
				{
					newValueB += MaskSobelY[mr][mc] * img_src.at<Vec3b>(Point(j + mc - 1, i + mr - 1))[0];
					newValueG += MaskSobelY[mr][mc] * img_src.at<Vec3b>(Point(j + mc - 1, i + mr - 1))[1];
					newValueR += MaskSobelY[mr][mc] * img_src.at<Vec3b>(Point(j + mc - 1, i + mr - 1))[2];
				}
			}
			pTmpYB[i * size_img.width + j] = newValueB;
			pTmpYG[i * size_img.width + j] = newValueG;
			pTmpYR[i * size_img.width + j] = newValueR;
		}
	}

	for (i = 1; i < height - 1; i++)
	{
		for (j = 1; j < width - 1; j++)
		{
			constBVal1 = pTmpXB[i * size_img.width + j];
			constGVal1 = pTmpXG[i * size_img.width + j];
			constRVal1 = pTmpXR[i * size_img.width + j];
			constBVal2 = pTmpYB[i * size_img.width + j];
			constGVal2 = pTmpYG[i * size_img.width + j];
			constRVal2 = pTmpYR[i * size_img.width + j];
			if (constBVal1 < 0)
			{
				constBVal1 = -constBVal1;
			}
			if (constGVal1 < 0)
			{
				constGVal1 = -constGVal1;
			}
			if (constRVal1 < 0)
			{
				constRVal1 = -constRVal1;
			}
			if (constBVal2 < 0)
			{
				constBVal2 = -constBVal2;
			}
			if (constGVal2 < 0)
			{
				constGVal2 = -constGVal2;
			}
			if (constRVal2 < 0)
			{
				constRVal2 = -constRVal2;
			}

			pTmpXB[i * size_img.width + j] = constBVal1 + constBVal2;
			pTmpXG[i * size_img.width + j] = constGVal1 + constGVal2;
			pTmpXR[i * size_img.width + j] = constRVal1 + constRVal2;
		}
	}

	minB = minG = minR = (int)10e10;
	maxB = maxG = maxR = (int)-10e10;
	for (i = 1; i < height - 1; i++)
	{
		for (j = 1; j < width - 1; j++)
		{
			newValueB = pTmpXB[i * size_img.width + j];
			newValueG = pTmpXG[i * size_img.width + j];
			newValueR = pTmpXR[i * size_img.width + j];
			if (newValueB < minB)
			{
				minB = newValueB;
			}
			if (newValueB > maxB)
			{
				maxB = newValueB;
			}
			if (newValueG < minG)
			{
				minG = newValueG;
			}
			if (newValueG > maxG)
			{
				maxG = newValueG;
			}
			if (newValueR < minR)
			{
				minR = newValueR;
			}
			if (newValueR > maxR)
			{
				maxR = newValueR;
			}
		}
	}
	constBVal1 = (float)(255.0 / (maxB - minB));
	constBVal2 = (float)(-255.0 * minB / (maxB - minB));
	constGVal1 = (float)(255.0 / (maxG - minG));
	constGVal2 = (float)(-255.0 * minG / (maxG - minG));
	constRVal1 = (float)(255.0 / (maxR - minR));
	constRVal2 = (float)(-255.0 * minR / (maxR - minR));


	// write your code here
	for (i = 1; i < height - 1; i++)
	{
		for (j = 1; j < width - 1; j++)
		{
			//? ? ? Write your code here
			// Step 1
			b = pTmpXB[i * size_img.width + j];
			g = pTmpXG[i * size_img.width + j];
			r = pTmpXR[i * size_img.width + j];

			// Step 2

			b = constBVal1 * b + constBVal2;
			g = constGVal1 * g + constGVal2;
			r = constRVal1 * r + constRVal2;

			// Step 3
			mOutImg.at<Vec3b>(i, j)[0] = b;
			mOutImg.at<Vec3b>(i, j)[1] = g;
			mOutImg.at<Vec3b>(i, j)[2] = r;
			//mOutImg.at<Vec3b>(i, j) = b + g + r;

		}
	}

	delete[] pTmpXB;
	delete[] pTmpXG;
	delete[] pTmpXR;
	delete[] pTmpYB;
	delete[] pTmpYG;
	delete[] pTmpYR;

	//free;
	//img_save = mOutImg;

	namedWindow("Edge Sobel", 1);
	imshow("Edge Sobel", mOutImg);
}
