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

// 定义鼠标宏
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 

using namespace std;
using namespace cv;

// 从yolov5-lite拿到预测函数
extern void detect(cv::Mat mat1, cv::Mat &mat2);
// 截屏
void Screen();
// hBitmap转IplImage
IplImage* hBitmapToIpl(HBITMAP hBmp);

// 定义变量和指针
HBITMAP	hBmp;
HBITMAP	hOld;
Mat dst;
Mat image;
IplImage* inter;

// 拿到屏幕尺寸
extern int nWidth;
extern int nHeight;
int main()
{
	while (true)
	{
		// 捕捉鼠标右键休眠，滚轮退出，全局可用
		if (KEY_DOWN(VK_RBUTTON)) { Sleep(5000); }
		else if (KEY_DOWN(VK_MBUTTON)) {break; }

		// 屏幕截取
		Screen();
		// hBitmap转IplImage
		inter = hBitmapToIpl(hBmp);
		// IplImage转Mat
		image = cvarrToMat(inter);
		// 图像处理
		resize(image, image, cv::Size(320, 320));
		// 检测
		detect(image, dst);
		// 缩放显示
		resize(dst, dst, cv::Size(nWidth/4, nHeight/4));

		// 窗口置顶
		namedWindow("window");
		HWND hWnd = (HWND)cvGetWindowHandle("window");
		HWND hRawWnd = ::GetParent(hWnd);
		if (NULL != hRawWnd)
		{
			BOOL bRet = ::SetWindowPos(hRawWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
			//assert(bRet);
		}

		// 图像显示
		cv::imshow("window", dst);
		cv::waitKey(1);

		// 释放内存
		DeleteObject(hBmp);
		cvReleaseImage(&inter);
	}
	return 0;
}


IplImage* hBitmapToIpl(HBITMAP hBmp)
{
	BITMAP bmp;
	GetObject(hBmp, sizeof(BITMAP), &bmp);   
	// 通道
	int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
	// 通道深度
	int depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
	// 预分配空间
	IplImage* img = cvCreateImage(cvSize(bmp.bmWidth, bmp.bmHeight), depth, nChannels);
	// 申请内存
	BYTE* pBuffer = new BYTE[bmp.bmHeight * bmp.bmWidth * nChannels*5];
	// 将输入图片内容传入中间变量pBuffer 
	GetBitmapBits(hBmp, bmp.bmHeight * bmp.bmWidth * nChannels, pBuffer);
	// 将图片内容从中间变量转到img
	memcpy(img->imageData, pBuffer, bmp.bmHeight * bmp.bmWidth * nChannels);
	// 释放内存
	delete[] pBuffer;
	pBuffer = nullptr;
	// 创建目标图片
	IplImage* dst = cvCreateImage(cvGetSize(img), img->depth, 3);
	// 拷贝并转换颜色
	cvCvtColor(img, dst, CV_BGRA2BGR);
	// 释放内存
	cvReleaseImage(&img);
	return dst;
}


//抓取当前屏幕函数
void Screen() {
	//创建画板
	HDC hScreen = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	HDC	hCompDC = CreateCompatibleDC(hScreen);
	//取屏幕宽度和高度
	int	nWidth = GetSystemMetrics(SM_CXSCREEN);
	int	nHeight = GetSystemMetrics(SM_CYSCREEN);
	//创建Bitmap对象
	hBmp = CreateCompatibleBitmap(hScreen, nWidth, nHeight);
	hOld = (HBITMAP)SelectObject(hCompDC, hBmp);
	BitBlt(hCompDC, 0, 0, nWidth, nHeight, hScreen, 0, 0, SRCCOPY);
	SelectObject(hCompDC, hOld);
	//释放对象
	DeleteDC(hScreen);
	DeleteDC(hCompDC);
}