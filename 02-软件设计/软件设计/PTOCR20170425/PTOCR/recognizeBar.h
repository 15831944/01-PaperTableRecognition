

#ifndef RECOGNIZEBAR_H
#define RECOGNIZEBAR_H


#include "zbar.h"        
#include "cv.h"
#include "highgui.h"
#include <iostream>

using namespace std;
using namespace zbar;  //���zbar���ƿռ�      
using namespace cv;

class RecBar
{
public:
	void recBar(Mat);
	string getTypeName()const{ return typeName; };
	string getData()const{ return data; };


private:
	string typeName;
	string data;

};



#endif
