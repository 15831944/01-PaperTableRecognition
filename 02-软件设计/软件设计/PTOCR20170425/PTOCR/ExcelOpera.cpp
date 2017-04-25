
/*************************************************************

������ʹ��MFC����Excel�ļ���
�����ļ��������ļ��򿪣��ļ��༭���ļ����棬���̹رգ���̨����
���ߣ�������
���ڣ�20170425
�汾��v1.0
**************************************************************/

#include "stdafx.h"
#include "ExcelOpera.h"


ExcelOpera::ExcelOpera()
{
	//��ʼ��OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(_T("��ʼ��Ole����"));
		return ;
	}
	isOpened = false;

}


ExcelOpera::~ExcelOpera()
{
}


/*********************************************************
˵��������Excel�ļ�
���룺��

���أ���
***********************************************************/
void ExcelOpera::CreateExcelFile()
{
	//����
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		//this->MessageBox(_T("�޷�����ExcelӦ�ã�"));
		return;
	}
	books = app.get_Workbooks();
	//��Excel������pathnameΪExcel���·����  

	book = books.Add(covOptional);
	sheets = book.get_Worksheets();
	sheet = sheets.get_Item(COleVariant((short)1));
	//�������Ϊ��A��1���ͣ�B��1����������Ԫ�� 
	range = sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("B1")));
	//���õ�Ԫ������ΪHello Exce
	range.put_Value2(COleVariant(_T("Hello Excel")));
	//ѡ�����У������ÿ��Ϊ����Ӧ 
	cols = range.get_EntireColumn();
	cols.AutoFit();
	//��������Ϊ���� 
	font = range.get_Font();
	font.put_Bold(COleVariant((short)TRUE));
	//�������Ϊ��C��2����Ԫ�� 
	range = sheet.get_Range(COleVariant(_T("C2")), COleVariant(_T("C5")));
	//���ù�ʽ��=RAND()*100000��
	range.put_Formula(COleVariant(_T("=RAND()*100000")));
	//�������ָ�ʽΪ������  
	range.put_NumberFormat(COleVariant(_T("$0.00")));
	//ѡ�����У������ÿ��Ϊ����Ӧ  
	cols = range.get_EntireColumn();
	cols.AutoFit();


	//��ʾExcel��
	//app.put_Visible(TRUE);
	//app.put_UserControl(TRUE);


	TCHAR FilePath[MAX_PATH];
	GetModuleFileName(NULL, FilePath, MAX_PATH);
	(_tcsrchr(FilePath, '\\'))[1] = 0;
	lstrcat(FilePath, _T("MFC_ExcelTest.xlsx"));

	//CString szFilePath;
	//szFilePath.Format(_T("%s"), FilePath);


	//����Excel
	//book.SaveAs(_T("./MFC_ExcelTest"));
	book.SaveAs(COleVariant(FilePath), covOptional,
		covOptional, covOptional,
		covOptional, covOptional, (long)0,
		covOptional, covOptional, covOptional,
		covOptional, covOptional); //��Ĳ�ͬ���Ǹ������ģ�ֱ���ں����������covOptional�ɹ���



	app.Quit();
	//m_ExlAppһ��Ҫ�ͷţ������������󻹻���һ��Excel����פ�����ڴ��У����ҳ����ظ����е�ʱ������   
	app.ReleaseDispatch();
}

/*********************************************************
˵������ָ��Excel�ļ�
���룺filePath���ļ�ȫ·��

���أ���
***********************************************************/
void ExcelOpera::OpenExistExcelFile(CString filePath)
{
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		//this->MessageBox(_T("�޷�����ExcelӦ�ã�"));
		return;
	}
	
	

	books = app.get_Workbooks();

	LPDISPATCH lpDisp;  //�ӿ�ָ��  
	//books = app.get_Workbooks();
	lpDisp = books.Open(filePath,
		covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional
		);                  //��Ĳ�ͬ���Ǹ������ģ�ֱ���ں����������covOptional�ɹ���  
	book.AttachDispatch(lpDisp);

	isOpened = true;

	//�������д����
	sheets = book.get_Worksheets();
	sheet = sheets.get_Item(COleVariant((short)1));




}

/*********************************************************
˵�����༭excel
���룺const string cellNum��Ԫ����,const string str�ַ���
���أ�void
***********************************************************/
void ExcelOpera::EditExcel(const string cellNum, const string str)
{
	if (!isOpened)
		return;
	if (str == "")
		return;

	//�������Ϊ��A��1���ͣ�B��1����������Ԫ�� 
	range = sheet.get_Range(COleVariant(CString(cellNum.c_str())), COleVariant(CString(cellNum.c_str())));
	//���õ�Ԫ������ΪHello Exce
	range.put_Value2(COleVariant(CString(str.c_str())));
}

/*********************************************************
˵����ǰ̨��ʾ�򿪵�Excel�ļ�
���룺void 
���أ�void 
***********************************************************/
void ExcelOpera::ShowExcel()
{

	//��ʾExcel��
	app.put_Visible(TRUE);
	app.put_UserControl(TRUE);
}

/*********************************************************
˵��������򿪵�excel�ļ������ر�excel����
���룺void
���أ�void
***********************************************************/
void ExcelOpera::ExitExcel()
{

	book.Save();

	app.Quit();
	//m_ExlAppһ��Ҫ�ͷţ������������󻹻���һ��Excel����פ�����ڴ��У����ҳ����ظ����е�ʱ������   
	app.ReleaseDispatch();

}