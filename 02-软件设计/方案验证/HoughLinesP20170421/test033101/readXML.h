
#ifndef READXML_H
#define READXML_H

#include "tinystr.h" 
#include "tinyxml.h" 

#include <iostream>
#include <string>
#include <vector>

using namespace std;


#pragma comment(lib,"tinyxml.lib") 
#pragma comment(lib,"tinyxmlSTL.lib") 


//��Ŷ�λ�߿�����
typedef struct
{
	int x;
	int y;
	int width;
	int height;
}Border;


//��ŵ�Ԫ������
typedef struct
{
	int x;
	int y;
	int width;
	int height;
	string cellNum;
}Cell;


extern Border border;     //���嶨λ�߿�ı߽�ṹ��
extern vector<Cell> vecCell;

string dumpNode(TiXmlNode * pNode, int flag);
void readXML();
void printXML();


#endif