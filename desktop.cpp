#include <time.h>
#include <vector>
#include <stdio.h>
#include <comdef.h>
#include <iostream>
#include <atlimage.h>
#include <Windows.h>
#include <tchar.h>
#include <conio.h>
#include <opencv.hpp>

// ��������
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 

using namespace std;
using namespace cv;

// ��yolov5-lite�õ�Ԥ�⺯��
extern void detect(cv::Mat mat1, cv::Mat &mat2);
// ����
void Screen();
// hBitmapתIplImage
IplImage* hBitmapToIpl(HBITMAP hBmp);

// ���������ָ��
HBITMAP	hBmp;
HBITMAP	hOld;
Mat dst;
Mat image;
IplImage* inter;

// �õ���Ļ�ߴ�
extern int nWidth;
extern int nHeight;
int main()
{
	while (true)
	{
		// ��׽����Ҽ����ߣ������˳���ȫ�ֿ���
		if (KEY_DOWN(VK_RBUTTON)) { Sleep(5000); }
		else if (KEY_DOWN(VK_MBUTTON)) {break; }

		// ��Ļ��ȡ
		Screen();
		// hBitmapתIplImage
		inter = hBitmapToIpl(hBmp);
		// IplImageתMat
		image = cvarrToMat(inter);
		// ͼ����
		resize(image, image, cv::Size(320, 320));
		// ���
		detect(image, dst);
		// ������ʾ
		resize(dst, dst, cv::Size(nWidth/4, nHeight/4));

		// �����ö�
		namedWindow("window");
		HWND hWnd = (HWND)cvGetWindowHandle("window");
		HWND hRawWnd = ::GetParent(hWnd);
		if (NULL != hRawWnd)
		{
			BOOL bRet = ::SetWindowPos(hRawWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
			//assert(bRet);
		}

		// ͼ����ʾ
		cv::imshow("window", dst);
		cv::waitKey(1);

		// �ͷ��ڴ�
		DeleteObject(hBmp);
		cvReleaseImage(&inter);
	}
	return 0;
}


IplImage* hBitmapToIpl(HBITMAP hBmp)
{
	BITMAP bmp;
	GetObject(hBmp, sizeof(BITMAP), &bmp);   
	// ͨ��
	int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
	// ͨ�����
	int depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
	// Ԥ����ռ�
	IplImage* img = cvCreateImage(cvSize(bmp.bmWidth, bmp.bmHeight), depth, nChannels);
	// �����ڴ�
	BYTE* pBuffer = new BYTE[bmp.bmHeight * bmp.bmWidth * nChannels*5];
	// ������ͼƬ���ݴ����м����pBuffer 
	GetBitmapBits(hBmp, bmp.bmHeight * bmp.bmWidth * nChannels, pBuffer);
	// ��ͼƬ���ݴ��м����ת��img
	memcpy(img->imageData, pBuffer, bmp.bmHeight * bmp.bmWidth * nChannels);
	// �ͷ��ڴ�
	delete[] pBuffer;
	pBuffer = nullptr;
	// ����Ŀ��ͼƬ
	IplImage* dst = cvCreateImage(cvGetSize(img), img->depth, 3);
	// ������ת����ɫ
	cvCvtColor(img, dst, CV_BGRA2BGR);
	// �ͷ��ڴ�
	cvReleaseImage(&img);
	return dst;
}


//ץȡ��ǰ��Ļ����
void Screen() {
	//��������
	HDC hScreen = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	HDC	hCompDC = CreateCompatibleDC(hScreen);
	//ȡ��Ļ��Ⱥ͸߶�
	int	nWidth = GetSystemMetrics(SM_CXSCREEN);
	int	nHeight = GetSystemMetrics(SM_CYSCREEN);
	//����Bitmap����
	hBmp = CreateCompatibleBitmap(hScreen, nWidth, nHeight);
	hOld = (HBITMAP)SelectObject(hCompDC, hBmp);
	BitBlt(hCompDC, 0, 0, nWidth, nHeight, hScreen, 0, 0, SRCCOPY);
	SelectObject(hCompDC, hOld);
	//�ͷŶ���
	DeleteDC(hScreen);
	DeleteDC(hCompDC);
}