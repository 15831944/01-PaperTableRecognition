
/*************************************************************

������ʹ��MFC����Excel�ļ���
	�����ļ��������ļ��򿪣��ļ��༭���ļ����棬���̹رգ���̨����
���ߣ�������
���ڣ�20170425
�汾��v1.0
**************************************************************/

#pragma once

#include"CApplication.h"
#include"CFont0.h"
#include"CRange.h"
#include"CRanges.h"
#include"CWorkbook.h"
#include"CWorkbooks.h"
#include"CWorksheet.h"
#include"CWorksheets.h"

#include<iostream>
#include<string>

using namespace std;

class ExcelOpera
{
public:
	ExcelOpera();
	~ExcelOpera();

	void CreateExcelFile();
	void OpenExistExcelFile(CString filePath);
	void ExitExcel();
	void ShowExcel();
	void EditExcel(const string cellNum, const string str);

private:
	//����ӿ������ 
	CApplication app;
	CWorkbook book;
	CWorkbooks books;
	CWorksheet sheet;
	CWorksheets sheets;
	CRange range;
	CFont0 font;
	CRange cols;
	LPDISPATCH lpDisp;

	bool isOpened;


};

