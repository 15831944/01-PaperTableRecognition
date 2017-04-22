// C++_XML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tinystr.h" 
#include "tinyxml.h" 
#include <iostream>
#include <string>

using namespace std;


#pragma comment(lib,"tinyxml.lib") 
#pragma comment(lib,"tinyxmlSTL.lib") 


int count123 = 0;

string dumpNode(TiXmlNode * pNode, int flag);


int  _tmain(int argc, _TCHAR* argv[])
{


	TiXmlDocument *myDocument = new TiXmlDocument("1521611168303.xml");
	myDocument->LoadFile();

	//���xml��ͷ������������ 
	TiXmlDeclaration* decl = myDocument->FirstChild()->ToDeclaration();

	cout << "xml�ļ��İ汾��:" << decl->Version() << endl;
	cout << "xml�ı����ʽ�ǣ�" << decl->Encoding() << endl;

	//��ø�Ԫ�� 
	TiXmlElement *RootElement = myDocument->RootElement();

	//�����Ԫ������ 
	cout << RootElement->Value() << endl;
	TiXmlNode* pNode = NULL;
	string msg = "";
	
	for (pNode = RootElement->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())  //��ͬһ������ѭ��
	{
		msg = dumpNode(pNode, 0);
		cout << msg << endl;
	}	

	system("pause");

	return 0;
}



string dumpNode(TiXmlNode * pNode, int flag)
{
	string msg = "";

	if (pNode == NULL)
	{
		return "";
	}
	TiXmlText * pText = NULL;
	TiXmlNode * pChildNode = NULL;
	count123++;
	int t = pNode->Type();
	if (t == TiXmlText::TINYXML_TEXT)  //�ڵ�������text�ڵ� 
	{
		pText = pNode->ToText();
		string text = pText->Value();
		if (!text.empty())
		{
			msg = msg + "=" + text;
			
		}

		
	}
	else if (t == TiXmlText::TINYXML_ELEMENT) //�ڵ�������Element 
	{
		msg = msg + "\r\n";
		int num = flag;
		while (num >= 1)
		{
			msg = msg + "\t";
			num--;
		}
		msg = msg + pNode->Value();		

		//������� 
		TiXmlElement * pElement = pNode->ToElement();
		TiXmlAttribute * pAttr = pElement->FirstAttribute();
		TiXmlAttribute * pNextAttr = NULL;
		string tmpAttrMsg = "[";
		if (pAttr != NULL)
		{
			string tmpAttrVal = "";
			string tmpAttrName = "";
			do
			{
				tmpAttrVal = pAttr->Value();
				tmpAttrName = pAttr->Name();
				tmpAttrMsg += tmpAttrName + "=" + tmpAttrVal + ","; //��������֮���ö��ŷָ� 

			} while (pAttr = pAttr->Next());
			tmpAttrMsg = tmpAttrMsg.erase(tmpAttrMsg.find_last_of(","));
		}
		tmpAttrMsg += "]";
		msg += tmpAttrMsg;
	}

	//ѭ����������ÿһ��Ԫ�� 
	for (pChildNode = pNode->FirstChild(); pChildNode != 0; pChildNode = pChildNode->NextSibling())  //��ͬһ������ѭ��
	{
		msg = msg + dumpNode(pChildNode, flag + 1);
	}

	return msg;
}