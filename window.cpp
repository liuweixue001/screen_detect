////#include "stdafx.h"
//#include <time.h>
//#include <vector>
//#include <stdio.h>
//#include <comdef.h>
//#include <iostream>
//#include <atlimage.h>
//#include <Windows.h>
//#include <tchar.h>
//using namespace std;
//#include <opencv.hpp>
//using namespace cv;
//
//extern cv::Mat predict(cv::Mat& frame);
//
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )  // ����������ѡ��
//
//
//
//IplImage* hBitmapToIpl(HBITMAP hBmp)
//{
//	BITMAP bmp;
//
//	GetObject(hBmp, sizeof(BITMAP), &bmp);
//
//	int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
//
//	int depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
//
//	IplImage* img = cvCreateImage(cvSize(bmp.bmWidth, bmp.bmHeight), depth, nChannels);
//
//	BYTE* pBuffer = new BYTE[bmp.bmHeight * bmp.bmWidth * nChannels];
//
//	GetBitmapBits(hBmp, bmp.bmHeight * bmp.bmWidth * nChannels, pBuffer);
//
//	memcpy(img->imageData, pBuffer, bmp.bmHeight * bmp.bmWidth * nChannels);
//	delete pBuffer;
//
//	IplImage* dst = cvCreateImage(cvGetSize(img), img->depth, 3);
//
//	cvCvtColor(img, dst, CV_BGRA2BGR);
//	cvReleaseImage(&img);
//
//	return dst;
//}
//
//int main(int argc, _TCHAR* argv[])
//{
//
//	POINT	pt;
//	GetCursorPos(&pt);//�õ���ǰ��������Ӧ�ó���
//	HWND	hpWnd = NULL, hcWnd = NULL;
//	hpWnd = ::WindowFromPoint(pt);
//	//BOOL bOK = ::ScreenToClient(hpWnd, &pt);
//	//hpWnd = ::ChildWindowFromPoint(hpWnd, pt);
//	//HWND hpWnd = GetDesktopWindow();//�õ�������
//	if (IsWindow(hpWnd))
//		std::cout << "�õ�Ӧ�þ��" << endl;
//		//hcWnd = ::ChildWindowFromPointEx(hpWnd, pt, CWP_ALL);
//		hcWnd = ::ChildWindowFromPoint(hpWnd, pt);
//	if (IsWindow(hcWnd) == FALSE)
//		hcWnd = hpWnd;
//	HDC hDc, memDc;
//	hDc = GetDC(hcWnd);//ȡ�������豸 hdc
//	memDc = CreateCompatibleDC(hDc);//������HDC�����棩���ݵ��豸memDc
//	HBITMAP hBitMap;
//	//HWND hWnd = GetDesktopWindow();//�õ�������
//	RECT rect;
//	GetWindowRect(hcWnd, &rect);//����ľ���
//	int width = (rect.right - rect.left); //����Ŀ�
//	int hight = (rect.bottom - rect.top); //����ĸ�
//	while (waitKey(50) != 27 && IsWindow(hcWnd))//������ESC����Ӧ�ô����˳�ʱ�˳�����
//	{
//
//
//
//		POINT	pt;
//		GetCursorPos(&pt);//�õ���ǰ��������Ӧ�ó���
//		HWND	hpWnd = NULL, hcWnd = NULL;
//		hpWnd = ::WindowFromPoint(pt);
//		if (IsWindow(hpWnd))
//			//hcWnd = ::ChildWindowFromPointEx(hpWnd, pt, CWP_ALL);
//			hcWnd = ::ChildWindowFromPoint(hpWnd, pt);
//		//if (IsWindow(hcWnd) == FALSE)
//		//	cout << "hcWnd ���Ǵ���" << endl;
//		//	return -2;
//		//	hcWnd = hpWnd;
//		HDC hDc, memDc;
//		hDc = GetDC(hcWnd);//ȡ�������豸 hdc
//		memDc = CreateCompatibleDC(hDc);//������HDC�����棩���ݵ��豸memDc
//		HBITMAP hBitMap;
//		//HWND hWnd = GetDesktopWindow();//�õ�������
//		RECT rect;
//		GetWindowRect(hcWnd, &rect);//����ľ���
//		int width = (rect.right - rect.left); //����Ŀ�
//		int hight = (rect.bottom - rect.top); //����ĸ�
//
//
//		hBitMap = CreateCompatibleBitmap(hDc, width, hight);//������������ݵĻ���
//		SelectObject(memDc, hBitMap);//�����豸�ͻ���
//		BitBlt(memDc, 0, 0, width, hight, hDc, 0, 0, SRCCOPY);//�������������豸�︴��
//		IplImage* src = hBitmapToIpl(hBitMap);
//		Mat image = cvarrToMat(src);
//		resize(image, image, cv::Size(320, 320));
//		image = predict(image);
//		resize(image, image, cv::Size(480, 270));
//
//		// �����ö�
//		namedWindow("window");
//		HWND hWnd = (HWND)cvGetWindowHandle("window");
//		HWND hRawWnd = ::GetParent(hWnd);
//		if (NULL != hRawWnd)
//		{
//			BOOL bRet = ::SetWindowPos(hRawWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
//			assert(bRet);
//		}
//		// ͼ����ʾ
//		imshow("window", image);
//		waitKey(1);
//		cvReleaseImage(&src);
//		DeleteObject(hBitMap);
//	}
//	return 0;
//}
//
