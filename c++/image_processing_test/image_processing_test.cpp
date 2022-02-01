// image_processing_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include "image_processing_test.h"

using namespace std;
using namespace cv;

void gray_image(Mat image) {

	Mat newImage;
	int red, green, blue;
	//int width = 960, height = 540;// 1920 * 1080
	//resize(image, newImage, Size(width, height));
	Mat lum(image.rows, image.cols, CV_8UC1, Scalar(0));
		// I = 0.299*R + 0.587*G + 0.114*B
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			red = image.at<Vec3b>(i, j)[2];
			green = image.at<Vec3b>(i, j)[1];
			blue = image.at<Vec3b>(i, j)[0];

			lum.at<uchar>(i, j) = (0.299 * red + 0.587 * green + 0.114 * blue);
		}
	}
	

	namedWindow("grayscale", WINDOW_AUTOSIZE);
	imshow("grayscale", lum);
}

void invertd_image(Mat image) {
	Mat newImage = image;
	int red, green, blue;
	//int width = 960, height = 540;// 1920 * 1080
	//resize(image, newImage, Size(width, height));
	Mat inverted = Mat::zeros(newImage.size(), newImage.type());
		// I = 0.299*R + 0.587*G + 0.114*B
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

	namedWindow("Invert_Color", WINDOW_AUTOSIZE);
	imshow("Invert_Color", inverted);
}

void mirror_image(Mat image)
{
	Mat3b newImage = image;
	/*int width = 960, height = 540;
	resize(image, newImage, Size(width, height));*/
	Mat3b mirror(newImage.rows, newImage.cols);
	for (int i = 0; i < mirror.rows; ++i)
	{
		for (int j = 0; j < mirror.cols; ++j)
		{
			mirror(i, j) = newImage(i, newImage.cols - 1 - j);
		}
	}
	namedWindow("Mirror", WINDOW_AUTOSIZE);
	imshow("Mirror", mirror);
}

void sobel_filter(Mat image)
{
	// TODO: Add your command handler code here
	int MaskSobelX[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };
	int MaskSobelY[3][3] = { {1,2,1},{0,0,0},{-1,-2,-1} };
	Mat img_src = image;
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

			//Or
			/*mOutImg.at<Vec3b>(i, j)[0] = constBVal1 * pTmpXB[i * size_img.width + j] + constBVal2;
			mOutImg.at<Vec3b>(i, j)[1] = constGVal1 * pTmpXG[i * size_img.width + j] + constGVal2;
			mOutImg.at<Vec3b>(i, j)[2] = constRVal1 * pTmpXR[i * size_img.width + j] + constRVal2;*/
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

void dark_luminune(Mat image)
{
	Mat newImage = image;
	Mat dark = Mat::zeros(newImage.size(), newImage.type());
	int dark_lumine = 100;
	int red, green, blue;
	int r, g, b;
	for (int i = 0; i < newImage.rows; i++)
	{
		for (int j = 0; j < newImage.cols; j++)
		{
			red = newImage.at<Vec3b>(i, j)[2];
			blue = newImage.at<Vec3b>(i, j)[0];
			green = newImage.at<Vec3b>(i, j)[1];

			r = red - dark_lumine;
			g = green - dark_lumine;
			b = blue - dark_lumine;

			if (r < 0)
			{
				r = 0;
			}
			if (g < 0)
			{
				g = 0;
			}
			if (b < 0)
			{
				b = 0;
			}

			dark.at<Vec3b>(i, j)[2] = r;
			dark.at<Vec3b>(i, j)[1] = g;
			dark.at<Vec3b>(i, j)[0] = b;
		}
	}
	namedWindow("Dark Luminane", WINDOW_AUTOSIZE);
	imshow("Dark Luminane", dark);
}

void light_luminune(Mat image)
{
	Mat newImage = image;
	Mat light = Mat::zeros(newImage.size(), newImage.type());
	int light_lumine = 100;
	int red, green, blue;
	int r, g, b;
	for (int i = 0; i < newImage.rows; i++)
	{
		for (int j = 0; j < newImage.cols; j++)
		{
			red = newImage.at<Vec3b>(i, j)[2];
			blue = newImage.at<Vec3b>(i, j)[0];
			green = newImage.at<Vec3b>(i, j)[1];

			r = red + light_lumine;
			g = green + light_lumine;
			b = blue + light_lumine;

			if (r > 255)
			{
				r = 255;
			}
			if (g > 255)
			{
				g = 255;
			}
			if (b > 255)
			{
				b = 255;
			}

			light.at<Vec3b>(i, j)[2] = r;
			light.at<Vec3b>(i, j)[1] = g;
			light.at<Vec3b>(i, j)[0] = b;
		}
	}
	namedWindow("Light Luminane", WINDOW_AUTOSIZE);
	imshow("Light Luminane", light);
}

void histogram_equalization(Mat image)
{
	// TODO: Add your command handler code here
	Mat img_src = image;
	Mat imgEqual = Mat(img_src.rows, img_src.cols, CV_8UC3);
	imgEqual = img_src;
	int r, g, b;
	BYTE intensityB;
	BYTE intensityG;
	BYTE intensityR;
	unsigned int histoB[256] = { 0, };
	unsigned int histoG[256] = { 0, };
	unsigned int histoR[256] = { 0, };
	BYTE LUTB[256] = { 0, };
	BYTE LUTG[256] = { 0, };
	BYTE LUTR[256] = { 0, };

	for (int y = 0; y < img_src.rows; y++)
	{
		for (int x = 0; x < img_src.cols; x++)
		{
			intensityB = img_src.at<Vec3b>(Point(x, y))[0];
			intensityG = img_src.at<Vec3b>(Point(x, y))[1];
			intensityR = img_src.at<Vec3b>(Point(x, y))[2];

			histoB[intensityB]++;
			histoG[intensityG]++;
			histoR[intensityR]++;
		}
	}

	for (int i = 0; i < 256; i++)
	{
		if (i == 0)
		{
			histoB[i] = histoB[0];
			histoG[i] = histoG[0];
			histoR[i] = histoR[0];
		}
		else
		{
			histoB[i] = histoB[i] + histoB[i - 1];
			histoG[i] = histoG[i] + histoG[i - 1];
			histoR[i] = histoR[i] + histoR[i - 1];
		}
	}

	for (int i = 0; i < 256; i++)
	{
		LUTB[i] = ((float)histoB[i] / (float)(img_src.cols * img_src.rows)) * 255;
		LUTG[i] = ((float)histoG[i] / (float)(img_src.cols * img_src.rows)) * 255;
		LUTR[i] = ((float)histoR[i] / (float)(img_src.cols * img_src.rows)) * 255;
	}

	// write your code here	
	for (int y = 0; y < img_src.rows; y++)
	{
		for (int x = 0; x < img_src.cols; x++)
		{
			// step 1: get_original RGB value

			r = img_src.at<Vec3b>(y, x)[2];
			g = img_src.at<Vec3b>(y, x)[1];
			b = img_src.at<Vec3b>(y, x)[0];

			// step 2: RGB value = Look Up Table

			r = int(LUTR[r]);
			g = int(LUTG[g]);
			b = int(LUTB[b]);
			
			// step 3: new_image = RGB value

			imgEqual.at<Vec3b>(y, x)[0] = b;
			imgEqual.at<Vec3b>(y, x)[1] = g;
			imgEqual.at<Vec3b>(y, x)[2] = r;

		}
	}

	//img_save = imgEqual;
	namedWindow("Histogram Equalization", WINDOW_AUTOSIZE);
	imshow("Histogram Equalization", imgEqual);
}

int main()
{   
	Mat image, newImage;
    image = imread("../../resource/glass.jpg", IMREAD_COLOR);
	int old_width, old_height;
	int choise;
	string ans;
	old_height = image.rows;
	old_width = image.cols;
	int width = old_width / 1, height = old_height / 1;// 1920 * 1080
	resize(image, newImage, Size(width, height));

	namedWindow("image", WINDOW_AUTOSIZE);
	imshow("image", newImage);

	/*cout << "Do you want to see original image? ";
	cin >> ans;
	if (ans == "yes" || ans == "y")
	{
		namedWindow("image", WINDOW_AUTOSIZE);
		imshow("image", newImage);
	}
	else
	{
		cout << "Original have not been show" << endl;
	}

	cout << """ 1. Grayscale Image. \n 2. invert image \n 3.Mirror image \n 4. Sobel image\n""";
	cout << "Enter the number of your choise: ";
	cin >> choise;

	switch (choise)
	{
	case 1: 
		gray_image(newImage);
		break;
	case 2:
		invertd_image(newImage);
		break;
	case 3:
		mirror_image(newImage);
		break;
	case 4:
		sobel_filter(newImage);
		break;
	default:
		exit(0);
		break;
	}*/

	
	

	/*gray_image(newImage);
	invertd_image(newImage);
	mirror_image(newImage);*/
	//sobel_filter(newImage);
	//dark_luminune(newImage);
	//light_luminune(newImage);
	histogram_equalization(newImage);


    waitKey(0);
    destroyAllWindows();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
