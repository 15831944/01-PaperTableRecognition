



/*************************************************************

������ʹ��OpenCV��ͼƬ�ļ����в�������
��������������α߿�
�����ۼƸ��ʻ����������߿�
����Tesseractʶ��ROI

���ߣ�������
���ڣ�20170425
�汾��v1.0
**************************************************************/

#include "stdafx.h"
#include "ProcessImage.h"

#include "include\\baseapi.h"
#include "include\\strngs.h"


#pragma  comment(lib,"libtesseract302.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//using namespace std;



ProcessImage::ProcessImage()
{



	srcImage = NULL;
}


ProcessImage::~ProcessImage()
{
}



/*************************************************************
˵��������ԭͼ������еı߿�
���룺Mat img ����
�����void
��ע��
**************************************************************/
void  ProcessImage::WipeSheetBorder()
{
	//����HoughLinesP������Ԫ��߿�

	Mat midImage;  //
	Canny(srcImage, midImage, 50, 100, 3);

	//imshow("��Ե�����ͼ", midImage);

	vector<Vec4i> lines;
	HoughLinesP(midImage, lines, 2, CV_PI / 180, 200, 50, 20);
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(srcImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 255), 2, CV_AA);

	}
}


/*************************************************************
˵�������Ҷ�λ�߿򣬲�����
���룺Mat img ����
�����void
��ע������ͨ��
**************************************************************/
void ProcessImage::FindOutBorder()
{
	vector<vector<Point2i>> contours;
	
	Mat disImage=srcImage.clone();
	Mat srcgray, disgray;
	cvtColor(srcImage, srcgray, COLOR_RGB2GRAY);

	Mat midImage(srcImage.size(), CV_16SC1);
	threshold(srcgray, disgray, 200, 255, CV_THRESH_BINARY_INV);
	findContours(disgray, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	vector<vector<Point2i>> contours2;

	for (int i = 0; i < contours.size(); i++)
	{
		//approxPolyDP(Mat(contours[i]), contours2[i], 3, true);
		if (contours[i].size()>500)
			contours2.push_back(contours[i]);
	}
	
	drawContours(disImage, contours2, -1, Scalar(0), 2);
	imshow("findOutBorder", disImage);

	outBorder = boundingRect(contours2.back());
	TRACE(_T("LocationBorder = %d,%d,%d,%d\r\n"), outBorder.x, outBorder.y, outBorder.width, outBorder.height);
	
}


/*************************************************************
˵��������ͼƬ�ļ�
���룺const string �ļ���
�����void
��ע��
**************************************************************/
void ProcessImage::ReadImage(const string &fileName)
{
	srcImage = imread(fileName);
}

/*************************************************************
˵��������ͼƬ�ļ�
���룺Mat 
�����void
��ע��
**************************************************************/
void ProcessImage::ReadImage(Mat img)
{
	srcImage = img;
}

/*************************************************************
˵����ʶ��ͼƬ��ָ������
���룺int x,int y,int width,int height
�����string
��ע��
**************************************************************/
string ProcessImage::RecROI(int x, int y, int width, int height)
{
	Mat sheetCellROI = srcImage(Rect(x, y, width, height));
	Mat gray;
	cvtColor(sheetCellROI, gray, CV_RGB2GRAY);

	tesseract::TessBaseAPI tessOCR;
	// Pass it to Tesseract API  

	tessOCR.Init(NULL, "num", tesseract::OEM_DEFAULT);
	tessOCR.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
	tessOCR.SetImage((uchar*)gray.data, gray.cols, gray.rows, 1, gray.cols);
	



	imshow("sheetCell", gray);

	 string str = tessOCR.GetUTF8Text();
	 TRACE(str.c_str());
	 return str;
}



