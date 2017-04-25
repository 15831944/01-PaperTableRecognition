
// MFC_ExcelTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFC_ExcelTest.h"
#include "MFC_ExcelTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_ExcelTestDlg dialog



CMFC_ExcelTestDlg::CMFC_ExcelTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFC_ExcelTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_ExcelTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC_ExcelTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMFC_ExcelTestDlg message handlers

BOOL CMFC_ExcelTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	OutputDebugString(_T("\n Debug \n"));
//	TRACE(_T(" Debug "));
//	TRACE(_T("\n"));
	CString strDir = _T("D:\\Documents\\Visual Studio 2013\\Projects\\_MFC\\_MFC_File\\FileDataBase");
	//this->TravelFolder(strDir, 0);
	CString fileName = _T("1521611168303.xlsx");
	CString findFilePath;
	findFilePath = FindFilePath(strDir, fileName, 0);
	TRACE(_T("findFilePath = %s\r\n"), findFilePath);
	if (findFilePath)
		CopyFile(findFilePath, strDir+_T("\\")+_T("CopyFile.xlsx"),false);

	OpenExistExcelFile(findFilePath);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

/*********************************************************
˵��������Excel�ļ�
���룺��

���أ���
***********************************************************/
void CMFC_ExcelTestDlg::CreateExcelFile()
{
	//����
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		this->MessageBox(_T("�޷�����ExcelӦ�ã�"));
		return ;
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
	//��ȡ��ǰĿ¼
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
void CMFC_ExcelTestDlg::OpenExistExcelFile(CString filePath)
{
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		this->MessageBox(_T("�޷�����ExcelӦ�ã�"));
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

	//�������д����
	sheets = book.get_Worksheets();
	sheet = sheets.get_Item(COleVariant((short)1));
	//�������Ϊ��A��1���ͣ�B��1����������Ԫ�� 
	range = sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("B1")));
	//���õ�Ԫ������ΪHello Exce
	range.put_Value2(COleVariant(_T("Hello OpenExistExcelFile")));

	book.Save();



	app.Quit();
	//m_ExlAppһ��Ҫ�ͷţ������������󻹻���һ��Excel����פ�����ڴ��У����ҳ����ظ����е�ʱ������   
	app.ReleaseDispatch();

}

/*********************************************************
����Ŀ¼�е��ļ�
���룺strDir����������Ŀ¼
	 nDepth ������Ŀ¼�����
���أ���

//���ļ����ݿ��в���ָ�����ļ��������Ƶ�ǰĿ¼
MoveFile(_T("d://softist.txt"), _T("d://softist2.txt"));

***********************************************************/
void CMFC_ExcelTestDlg::TravelFolder(CString strDir, int nDepth)
{
	CFileFind filefind;                                         //����CFileFind���ͱ���
	CString strWildpath = strDir + _T("\\*.*");     //�����ļ����г���
	vector<CString> fileNameVec;

	if(filefind.FindFile(strWildpath, 0))                    //��ʼ�����ļ�
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
CString CMFC_ExcelTestDlg::FindFilePath(CString strDir, CString fileName, int nDepth)
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
				if (findFileName ==fileName)
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

void CMFC_ExcelTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFC_ExcelTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFC_ExcelTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

