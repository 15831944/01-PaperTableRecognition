

#include "stdafx.h"
#include "readXML.h"




Border border;     //���嶨λ�߿�ı߽�ṹ��
vector<Cell> vecCell;

string dumpNode(TiXmlNode * pNode, int flag)
{
	string msg = "";

	if (pNode == NULL)
	{
		return "";
	}
	TiXmlText * pText = NULL;
	TiXmlNode * pChildNode = NULL;

	int t = pNode->Type();
	if (t == TiXmlText::TINYXML_TEXT)  //�ڵ�������text�ڵ� 
	{

		pText = pNode->ToText();
		string pNodeText = pText->Value();
		string pNodePText = pNode->Parent()->Value();
		string pNodePPText = pNode->Parent()->Parent()->Value();
		string pNodePPPText = pNode->Parent()->Parent()->Parent()->Value();

		//����λ�߿����ݴ�XML�н��������������Border��
		if (pNodePPText == "border")
		{
			if (pNodePText == "x")
				border.x = atoi(pNodeText.c_str());
			else if (pNodePText == "y")
				border.y = atoi(pNodeText.c_str());
			else if (pNodePText == "width")
				border.width = atoi(pNodeText.c_str());
			else if (pNodePText == "height")
				border.height = atoi(pNodeText.c_str());

		}

		//����Ԫ�����ݴ�XML�н��������������Cell��
		if (pNodePPPText == "cells")
		{
			if (pNodePText == "x")
				vecCell.back().x = atoi(pNodeText.c_str());
			else if (pNodePText == "y")
				vecCell.back().y = atoi(pNodeText.c_str());
			else if (pNodePText == "width")
				vecCell.back().width = atoi(pNodeText.c_str());
			else if (pNodePText == "height")
				vecCell.back().height = atoi(pNodeText.c_str());
			else if (pNodePText == "cellNum")
				vecCell.back().cellNum = pNodeText;

		}


		if (!pNodeText.empty())
		{
			msg = msg + "=" + pNodeText;

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
		string pNodeText = pNode->Value();
		string pNodePText = pNode->Parent()->Value();
		string pNodePPText = pNode->Parent()->Parent()->Value();

		//���뵥Ԫ��ڵ�
		if (pNodePText == "cells")
		{
			vecCell.push_back(Cell());//����һ���հ׵ĵ�Ԫ��ڵ�

		}

		msg = msg + pNodeText;

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


void readXML()
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


	for (pNode = RootElement->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())  //��ͬһ������ѭ��
	{
		dumpNode(pNode, 0);

	}
}

void printXML()
{
	//��ӡ�߿�����
	cout << "border" << endl;
	cout << "\t" << "border.x: " << border.x << endl;
	cout << "\t" << "border.y: " << border.y << endl;
	cout << "\t" << "border.width: " << border.width << endl;
	cout << "\t" << "border.height: " << border.height << endl;
	//��ӡ��Ԫ������
	cout << "cells: " << vecCell.size() << endl;

	for (auto i = 0; i < vecCell.size(); i++)
	{
		cout << "\t" << "cell_" << i << ".x: " << vecCell.at(i).x << endl;
		cout << "\t" << "cell_" << i << ".y: " << vecCell.at(i).y << endl;
		cout << "\t" << "cell_" << i << ".width: " << vecCell.at(i).width << endl;
		cout << "\t" << "cell_" << i << ".height: " << vecCell.at(i).height << endl;
		cout << "\t" << "cell_" << i << ".cellNum: " << vecCell.at(i).cellNum << endl;
		cout << endl;
	}
}