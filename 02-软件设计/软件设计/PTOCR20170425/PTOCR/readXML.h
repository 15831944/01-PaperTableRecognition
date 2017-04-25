
/*************************************************************

��������ȡXML�ļ�������TinyXML������
	��������XML��������Ч�ڵ����ݴ洢��C++�ṹ����
���ߣ�������
���ڣ�20170425
�汾��v1.0
**************************************************************/

#ifndef READXML_H
#define READXML_H

#include "tinystr.h" 
#include "tinyxml.h" 

#include <iostream>
#include <string>
#include <vector>

using namespace std;




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

class ReadXML
{
public:
	ReadXML();
	~ReadXML();

	
	void readXMLFile(const string fileName);
	void print();

private:
	string dumpNode(TiXmlNode * pNode, int flag);

public:
	Border border;     //���嶨λ�߿�ı߽�ṹ��
	vector<Cell> vecCell;

};






#endif