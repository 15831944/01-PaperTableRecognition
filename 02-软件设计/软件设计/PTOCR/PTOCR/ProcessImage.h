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


	Rect  FindOutBorder2(Mat img);     //���Ҷ�λ�߿�
	void  WipeSheetBorder(Mat &img);  //����������б߿�

	




};

