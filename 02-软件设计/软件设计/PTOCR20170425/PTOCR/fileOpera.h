/*************************************************************

������ʹ��MFC�ļ����в���
	����Ŀ¼�ļ�����
	Ŀ¼�ļ�����

���ߣ�������
���ڣ�20170425
�汾��v1.0
**************************************************************/

#ifndef FILEOPERA_H
#define FILEOPERA_H


#include<iostream>
#include<vector>
using namespace std;



class FileOpera
{

public:
	CString FindFilePath(CString strDir, CString fileName, int nDepth);
	void TravelFolder(CString strDir, int nDepth);

};



#endif