

#include "stdafx.h"
#include "recognizeBar.h"


void recBar(Mat img)
{
	ImageScanner scanner;
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

	Mat imageGray;
	cvtColor(img, imageGray, CV_RGB2GRAY);
	int width = imageGray.cols;
	int height = imageGray.rows;
	uchar *raw = (uchar *)imageGray.data;
	Image imageZbar(width, height, "Y800", raw, width * height);
	scanner.scan(imageZbar); //ɨ������      
	Image::SymbolIterator symbol = imageZbar.symbol_begin();
	if (imageZbar.symbol_begin() == imageZbar.symbol_end())
	{
		cout << "��ѯ����ʧ�ܣ�����ͼƬ��" << endl;
	}
	for (; symbol != imageZbar.symbol_end(); ++symbol)
	{
		cout << "���ͣ�" << endl << symbol->get_type_name() << endl << endl;
		cout << "���룺" << endl << symbol->get_data() << endl << endl;
		cout << "���볤�ȣ� " << endl << sizeof(symbol->get_data()) << endl;
	}

	imageZbar.set_data(NULL, 0);
}