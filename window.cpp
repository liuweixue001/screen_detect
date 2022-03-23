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
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )  // 设置连接器选项
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
//	GetCursorPos(&pt);//得到当前鼠标所点的应用程序
//	HWND	hpWnd = NULL, hcWnd = NULL;
//	hpWnd = ::WindowFromPoint(pt);
//	//BOOL bOK = ::ScreenToClient(hpWnd, &pt);
//	//hpWnd = ::ChildWindowFromPoint(hpWnd, pt);
//	//HWND hpWnd = GetDesktopWindow();//得到桌面句柄
//	if (IsWindow(hpWnd))
//		std::cout << "拿到应用句柄" << endl;
//		//hcWnd = ::ChildWindowFromPointEx(hpWnd, pt, CWP_ALL);
//		hcWnd = ::ChildWindowFromPoint(hpWnd, pt);
//	if (IsWindow(hcWnd) == FALSE)
//		hcWnd = hpWnd;
//	HDC hDc, memDc;
//	hDc = GetDC(hcWnd);//取得桌面设备 hdc
//	memDc = CreateCompatibleDC(hDc);//创建与HDC（桌面）兼容的设备memDc
//	HBITMAP hBitMap;
//	//HWND hWnd = GetDesktopWindow();//得到桌面句柄
//	RECT rect;
//	GetWindowRect(hcWnd, &rect);//桌面的矩形
//	int width = (rect.right - rect.left); //桌面的宽
//	int hight = (rect.bottom - rect.top); //桌面的高
//	while (waitKey(50) != 27 && IsWindow(hcWnd))//当按下ESC或者应用窗口退出时退出程序
//	{
//
//
//
//		POINT	pt;
//		GetCursorPos(&pt);//得到当前鼠标所点的应用程序
//		HWND	hpWnd = NULL, hcWnd = NULL;
//		hpWnd = ::WindowFromPoint(pt);
//		if (IsWindow(hpWnd))
//			//hcWnd = ::ChildWindowFromPointEx(hpWnd, pt, CWP_ALL);
//			hcWnd = ::ChildWindowFromPoint(hpWnd, pt);
//		//if (IsWindow(hcWnd) == FALSE)
//		//	cout << "hcWnd 不是窗口" << endl;
//		//	return -2;
//		//	hcWnd = hpWnd;
//		HDC hDc, memDc;
//		hDc = GetDC(hcWnd);//取得桌面设备 hdc
//		memDc = CreateCompatibleDC(hDc);//创建与HDC（桌面）兼容的设备memDc
//		HBITMAP hBitMap;
//		//HWND hWnd = GetDesktopWindow();//得到桌面句柄
//		RECT rect;
//		GetWindowRect(hcWnd, &rect);//桌面的矩形
//		int width = (rect.right - rect.left); //桌面的宽
//		int hight = (rect.bottom - rect.top); //桌面的高
//
//
//		hBitMap = CreateCompatibleBitmap(hDc, width, hight);//创建与桌面兼容的画布
//		SelectObject(memDc, hBitMap);//关联设备和画布
//		BitBlt(memDc, 0, 0, width, hight, hDc, 0, 0, SRCCOPY);//吧桌面往兼容设备里复制
//		IplImage* src = hBitmapToIpl(hBitMap);
//		Mat image = cvarrToMat(src);
//		resize(image, image, cv::Size(320, 320));
//		image = predict(image);
//		resize(image, image, cv::Size(480, 270));
//
//		// 窗口置顶
//		namedWindow("window");
//		HWND hWnd = (HWND)cvGetWindowHandle("window");
//		HWND hRawWnd = ::GetParent(hWnd);
//		if (NULL != hRawWnd)
//		{
//			BOOL bRet = ::SetWindowPos(hRawWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
//			assert(bRet);
//		}
//		// 图像显示
//		imshow("window", image);
//		waitKey(1);
//		cvReleaseImage(&src);
//		DeleteObject(hBitMap);
//	}
//	return 0;
//}
//
