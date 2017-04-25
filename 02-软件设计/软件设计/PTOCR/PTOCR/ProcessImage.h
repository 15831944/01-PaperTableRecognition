#pragma once
   
#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <vector>

using namespace std;   
using namespace cv;



class ProcessImage
{
public:
	ProcessImage();
	~ProcessImage();


	void  FindOutBorder();     //���Ҷ�λ�߿�
	void  WipeSheetBorder();  //����������б߿�
	void  ReadImage(const string &fileName);   //��ȡ�ļ�
	void  ReadImage(Mat img);
	string  RecROI(int x, int y, int width, int height);   //ʶ��ͼƬ��ָ������

private:

	Mat srcImage;
	Rect outBorder;




};

