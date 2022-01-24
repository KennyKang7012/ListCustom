
// ListCustomDlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "ListCustom.h"
#include "ListCustomDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CListCustomDlg 對話方塊



CListCustomDlg::CListCustomDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LISTCUSTOM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListCustomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CListCustomDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST1, &CListCustomDlg::OnLvnEndlabeleditList1)
END_MESSAGE_MAP()


// CListCustomDlg 訊息處理常式
#define ROW		3
#define COL		4
#define STRLEN	64

int LIST_HEADER_SIZE[COL] = { 55, 60, 60, 120 };
wchar_t *LIST_HEADER[] = { _T("名字"), _T("身高"), _T("體重"), _T("測量時間") };
//wchar_t *LIST_ITEM[ROW][COL] = { { _T("張三"), _T("182cm"), _T("81kg"), _T("2022/01/20") },
//							       { _T("李四"), _T("175cm"), _T("75kg"), _T("2022/01/21") },
//							       { _T("王五"), _T("191cm"), _T("90kg"), _T("2022/01/22") }, };

wchar_t LIST_ITEM_3D[ROW][COL][STRLEN] = {
										 { {(L"張三")}, {L"182cm"}, {L"81kg"}, {L"2022/01/20"} },
										 { {(L"李四")}, {L"175cm"}, {L"75kg"}, {L"2022/01/21"} },
										 { {(L"王五")}, {L"191cm"}, {L"90kg"}, {L"2022/01/22"} },
									 };

wchar_t *LIST_ITEM[ROW][COL] = { 0 };

typedef struct _LIST_ITEM_TEXT {
	LPCTSTR NameText;
	LPCTSTR HeightText;
	LPCTSTR WeightText;
	LPCTSTR DataTimeText;
} LIST_ITEM_TEXT, *PLIST_ITEM_TEXT;

static const LIST_ITEM_TEXT g_ListItemText[] = {
		{ (L"張三"), (L"182cm"), (L"81kg"), (L"2022/01/20") },
		{ (L"李四"), (L"175cm"), (L"75kg"), (L"2022/01/21") },
		{ (L"王五"), (L"191cm"), (L"90kg"), (L"2022/01/22") },
};

// k_ListItemTextSize = 3
static const SIZE_T k_ListItemTextSize = sizeof(g_ListItemText) / sizeof(LIST_ITEM_TEXT);

BOOL CListCustomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	TRACE("k_ListItemTextSize = %d\r\n", k_ListItemTextSize);
	for (int i = 0; i < k_ListItemTextSize; i++)
	{
		TRACE(L"Name is %s\r\n", g_ListItemText[i].NameText);
		TRACE(L"Height is %s\r\n", g_ListItemText[i].HeightText);
		TRACE(L"Weight is %s\r\n", g_ListItemText[i].WeightText);
		TRACE(L"DataTime is %s\r\n", g_ListItemText[i].DataTimeText);
	}

	CreateListMemory();

	SetListData();

	CreateListCtrl(COL, ROW);

	FreeListMemory();

	Print3DList();

#if 0
	m_list.InsertColumn(0, _T("名字"), LVCFMT_LEFT, 55);
	m_list.InsertColumn(1, _T("身高"), LVCFMT_LEFT, 60);
	m_list.InsertColumn(2, _T("體重"), LVCFMT_LEFT, 60);
	m_list.InsertColumn(3, _T("測量時間"), LVCFMT_LEFT, 120);

	int nCols = 0;
	nCols = m_list.InsertItem(0, L"張三");
	TRACE("nCols = %d\r\n", nCols);
	m_list.SetItemText(nCols, 1, L"182cm");
	m_list.SetItemText(nCols, 2, L"81kg");
	m_list.SetItemText(nCols, 3, L"2022/01/20");

	nCols = m_list.InsertItem(1, L"李四");
	TRACE("nCols = %d\r\n", nCols);
	m_list.SetItemText(nCols, 1, L"175cm");
	m_list.SetItemText(nCols, 2, L"75kg");
	m_list.SetItemText(nCols, 3, L"2022/01/21");

	nCols = m_list.InsertItem(2, L"王五");
	TRACE("nCols = %d\r\n", nCols);
	m_list.SetItemText(nCols, 1, L"191cm");
	m_list.SetItemText(nCols, 2, L"90kg");
	m_list.SetItemText(nCols, 3, L"2022/01/22");
#endif

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CListCustomDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CListCustomDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CListCustomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CListCustomDlg::OnLvnEndlabeleditList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	*pResult = TRUE;
}

void CListCustomDlg::CreateListMemory(void)
{
	for (int j = 0; j < ROW; j++)
	{
		for (int i = 0; i < COL; i++)
		{
			if (LIST_ITEM[j][i] == NULL)
			{
				LIST_ITEM[j][i] = (wchar_t *)malloc(sizeof(wchar_t) * STRLEN);
				wmemset(LIST_ITEM[j][i], 0, STRLEN);
				TRACE(L"LIST_ITEM[%d][%d] = %ls\n", j, i, LIST_ITEM[j][i]);
			}
		}
	}
}

void CListCustomDlg::FreeListMemory(void)
{
	for (int j = 0; j < ROW; j++)
	{
		for (int i = 0; i < COL; i++)
		{
			if (LIST_ITEM[j][i] != NULL)
			{
				TRACE(L"LIST_ITEM[%d][%d] = Not NULL\n", j, i);
				free(LIST_ITEM[j][i]);
				LIST_ITEM[j][i] = NULL;
			}
		}
	}
}

void CListCustomDlg::SetListData(void)
{
	int Idx = 0;
	
	for (int j = 0; j < ROW; j++)
	{
		wcscpy(LIST_ITEM[j][0], g_ListItemText[j].NameText);
		wcscpy(LIST_ITEM[j][1], g_ListItemText[j].HeightText);
		wcscpy(LIST_ITEM[j][2], g_ListItemText[j].WeightText);
		wcscpy(LIST_ITEM[j][3], g_ListItemText[j].DataTimeText);
		for (int i = 0; i < COL; i++)
		{
			Idx = j * COL + i;
			TRACE(L"(%d, %d) = %d ==> LIST_ITEM[%d][%d] = %ws\n", j, i, Idx, j, i, LIST_ITEM[j][i]);
		}
	}
}

void CListCustomDlg::Print3DList(void)
{
	int Idx = 0;
	for (int j = 0; j < ROW; j++)
	{
		for (int i = 0; i < COL; i++)
		{
			TRACE(L"LIST_ITEM_3D[%d][%d] = %ws\r\n", j, i, LIST_ITEM_3D[j][i]);
		}
	}
}

void CListCustomDlg::CreateListCtrl(int nCol, int nRow)
{
	//Header
	for (int i = 0; i < nCol; i++)
		m_list.InsertColumn(i, LIST_HEADER[i], LVCFMT_LEFT, LIST_HEADER_SIZE[i]);

	//Iteam Data
	int nItem = 0;
	for (int j = 0; j < nRow; j++)
	{
		nItem = m_list.InsertItem(j, LIST_ITEM[j][0]);
		TRACE(L"nItem = %d\r\n", nItem);
		for (int i = 1; i < nCol; i++)
		{
			m_list.SetItemText(nItem, i, LIST_ITEM[j][i]);
		}
	}
}
