

/*************************************************************

������ʹ��MFC�ļ����в���
	����Ŀ¼�ļ�����
	Ŀ¼�ļ�����

���ߣ�������
���ڣ�20170425
�汾��v1.0
**************************************************************/

#include "stdafx.h"
#include "fileOpera.h"

/*********************************************************
����Ŀ¼�е��ļ�
���룺strDir����������Ŀ¼
nDepth ������Ŀ¼�����
���أ���

***********************************************************/
void FileOpera::TravelFolder(CString strDir, int nDepth)
{
	CFileFind filefind;                                         //����CFileFind���ͱ���
	CString strWildpath = strDir + _T("\\*.*");     //�����ļ����г���
	vector<CString> fileNameVec;

	if (filefind.FindFile(strWildpath, 0))                    //��ʼ�����ļ�
	{
		BOOL bRet = TRUE;

		while (bRet)
		{
			bRet = filefind.FindNextFile();                 //ö��һ���ļ�

			if (filefind.IsDots())                                 //�����. �� .. ����һ��
				continue;

			for (int i = 0; i < nDepth; i++)                 //��οո��ӡ
			{
				TRACE(_T("    "));
			}

			if (!filefind.IsDirectory())                          //������Ŀ¼�����ļ�����ӡ����
			{
				CString strTextOut = strDir + CString(_T("\\")) + filefind.GetFileName();
				//TRACE(_T("file = %s\r\n"), strTextOut);
				fileNameVec.push_back(strTextOut);
			}
			else                                                    //�������Ŀ¼���ݹ���øú���
			{
				CString strTextOut = strDir + CString(_T("\\")) + filefind.GetFileName();
				TRACE(_T("dir = %s\r\n"), strTextOut);
				TravelFolder(strTextOut, nDepth + 1);//�ݹ���øú�����ӡ��Ŀ¼����ļ�
			}
		}
		filefind.Close();
	}
	//��output���� ��ӡ���findfile
	for (auto i : fileNameVec)
	{
		TRACE(_T("file = %s\r\n"), i);
	}
}

/*****************************************************************
˵�����ҵ�ָ�����ļ���
���룺strDir�������ҵ�Ŀ¼
fileName:�����ҵ��ļ���������׺��
nDepth:����Ŀ¼�����
���أ�CString �ҵ��ļ���ȫ·����
******************************************************************/
CString FileOpera::FindFilePath(CString strDir, CString fileName, int nDepth)
{
	CFileFind filefind;                                         //����CFileFind���ͱ���
	CString strWildpath = strDir + _T("\\*.*");     //�����ļ����г���

	if (filefind.FindFile(strWildpath, 0))                    //��ʼ�����ļ�
	{
		BOOL bRet = TRUE;

		while (bRet)
		{
			bRet = filefind.FindNextFile();                 //ö��һ���ļ�

			if (filefind.IsDots())                                 //�����. �� .. ����һ��
				continue;

			for (int i = 0; i < nDepth; i++)                 //��οո��ӡ
			{
				TRACE(_T("    "));
			}

			if (!filefind.IsDirectory())                          //������Ŀ¼�����ļ�����ӡ����
			{
				CString findFileName = filefind.GetFileName();
				TRACE(_T("GetFileName = %s\r\n"), findFileName);
				if (findFileName == fileName)
				{
					CString strTextOut = strDir + CString(_T("\\")) + findFileName;
					return strTextOut;         //�ҵ�ָ���ļ����˳�
				}

			}
			else                                                    //�������Ŀ¼���ݹ���øú���
			{
				CString strTextOut = strDir + CString(_T("\\")) + filefind.GetFileName();
				TRACE(_T("dir = %s\r\n"), strTextOut);
				FindFilePath(strTextOut, fileName, nDepth + 1);//�ݹ���øú�����ӡ��Ŀ¼����ļ�
			}
		}
		filefind.Close();
	}
	return NULL;

}