// ZbarTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "recognizeBar.h"





int main(int argc, char*argv[])
{
	Mat image = imread("zBarSample.jpg");
	if (!image.data)
	{
		cout << "��ȷ��ͼƬ" << endl;
		system("pause");
		return 0;
	}
	//ʶ��������
	recBar(image);

	imshow("Source Image", image);
	waitKey(0);
	return 0;
}






