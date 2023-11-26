
// DutchPayHelperDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "DutchPayHelper.h"
#include "DutchPayHelperDlg.h"
#include "afxdialogex.h"
#include "CAddSettlementDlg.h"
#include "CViewSettlementDlg.h"
#include <atlstr.h>

MYSQL Connect;
MYSQL_RES* sql_result;
MYSQL_ROW sql_row;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CDutchPayHelperDlg 대화 상자



CDutchPayHelperDlg::CDutchPayHelperDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DUTCHPAYHELPER_DIALOG, pParent)
	, m_timeDT(COleDateTime::GetCurrentTime())
	, m_timeMC(COleDateTime::GetCurrentTime())
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDutchPayHelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER, m_timeDT);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR, m_timeMC);
	DDX_Control(pDX, IDC_LIST_DUTCHPAY, m_listDutchPay);
	DDX_Control(pDX, IDC_MONTHCALENDAR, m_calendarMC);
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_pickerDT);
}

BEGIN_MESSAGE_MAP(CDutchPayHelperDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, &CDutchPayHelperDlg::OnMcnSelchangeMonthcalendar1)
	ON_LBN_SELCHANGE(IDC_LIST_DUTCHPAY, &CDutchPayHelperDlg::OnLbnSelchangeListDutchpay)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDutchPayHelperDlg::OnBnClickedButtonAdd)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR, &CDutchPayHelperDlg::OnSelchangeMonthcalendar)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER, &CDutchPayHelperDlg::OnDatetimechangeDatetimepicker)
	ON_BN_CLICKED(IDC_BUTTON_PICK_DATE, &CDutchPayHelperDlg::OnClickedButtonPickDate)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDutchPayHelperDlg::OnClickedButtonDelete)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_DUTCHPAY, &CDutchPayHelperDlg::OnLvnItemchangedListDutchpay)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_DETAILS, &CDutchPayHelperDlg::OnClickedButtonViewDetails)
END_MESSAGE_MAP()


// CDutchPayHelperDlg 메시지 처리기

BOOL CDutchPayHelperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// mysql 객체 초기화
	mysql_init(&Connect);
	// mysql 서버와 연결
	if (!mysql_real_connect(&Connect, CON_IP, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0))
	{
		CString s = _T("");
		s = mysql_error(&Connect);
		MessageBox(s, MB_OK);
	}
	else
	{
		mysql_query(&Connect, "set session character_set_connection=euckr;");
		mysql_query(&Connect, "set session character_set_results=euckr;");
		mysql_query(&Connect, "set session character_set_client=euckr;");

		DisplayUnCompletedSettlements();
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CDutchPayHelperDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDutchPayHelperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDutchPayHelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDutchPayHelperDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDutchPayHelperDlg::OnMcnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CDutchPayHelperDlg::OnLbnSelchangeListDutchpay()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDutchPayHelperDlg::OnBnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CAddSettlementDlg* pdlgAdd = new CAddSettlementDlg;
	pdlgAdd->SetParentDlg(this);
	if (pdlgAdd->DoModal() == IDOK) {

	}
}


void CDutchPayHelperDlg::OnSelchangeMonthcalendar(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	*pResult = 0;
}


void CDutchPayHelperDlg::OnDatetimechangeDatetimepicker(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// Date Time Picker에서 선택된 날짜 가져오기
	SYSTEMTIME selectedDate;
	m_pickerDT.GetTime(&selectedDate);

	// COleDateTime에 선택된 날짜 설정
	m_timeDT = COleDateTime(selectedDate);

	// DutchPay List 출력
	CString formattedDate = m_timeDT.Format(_T("%Y-%m-%d"));
	DisplaySelectedDateSettlements(formattedDate);

	*pResult = 0;
}


void CDutchPayHelperDlg::OnClickedButtonPickDate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMonthCalCtrl* pCalendar = (CMonthCalCtrl*)GetDlgItem(IDC_MONTHCALENDAR);
	pCalendar->SetCurSel(m_timeDT);
}


void CDutchPayHelperDlg::DisplayUnCompletedSettlements()
{
	// TODO: 여기에 구현 코드 추가.
	// IDC_LIST_DUTCHPAY에 연결된 CListCtrl 가져오기
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_DUTCHPAY);

	// CListCtrl 초기화
	pListCtrl->DeleteAllItems();
	pListCtrl->InsertColumn(0, _T("번호"), LVCFMT_CENTER, 40);
	pListCtrl->InsertColumn(1, _T("날짜"), LVCFMT_CENTER, 95);
	pListCtrl->InsertColumn(2, _T("모임 이름"), LVCFMT_CENTER, 82);
	pListCtrl->InsertColumn(3, _T("총무"), LVCFMT_CENTER, 70);
	pListCtrl->InsertColumn(4, _T("완료"), LVCFMT_CENTER, 50);
	pListCtrl->SetExtendedStyle(pListCtrl->GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// settlement 테이블에서 is_completed가 false인 항목 검색
	if (mysql_query(&Connect, "SELECT * FROM settlement WHERE is_completed = 0") == 0) {
		sql_result = mysql_store_result(&Connect);
		if (sql_result != NULL) {
			// 결과를 CListCtrl에 추가
			int row = 0;
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				// 각 컬럼의 데이터를 가져와서 CListCtrl에 추가
				CString index, date, name, affairs, is_completed;
				index = sql_row[0];
				date = sql_row[1];
				name = sql_row[2];
				affairs = sql_row[3];
				is_completed = "X";

				pListCtrl->InsertItem(row, index);
				pListCtrl->SetItem(row, 1, LVIF_TEXT, date, 0, 0, 0, 0);
				pListCtrl->SetItem(row, 2, LVIF_TEXT, name, 0, 0, 0, 0);
				pListCtrl->SetItem(row, 3, LVIF_TEXT, affairs, 0, 0, 0, 0);
				pListCtrl->SetItem(row, 4, LVIF_TEXT, is_completed, 0, 0, 0, 0);

				row++;
			}
			mysql_free_result(sql_result);
			
			UpdateData(FALSE);
		}
	}
}


void CDutchPayHelperDlg::DisplaySelectedDateSettlements(CString selectedDate)
{
	// TODO: 여기에 구현 코드 추가.
	// IDC_LIST_DUTCHPAY에 연결된 CListCtrl 가져오기
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_DUTCHPAY);

	// CListCtrl 초기화
	pListCtrl->DeleteAllItems();

	CString query;
	query.Format(_T("SELECT * FROM settlement WHERE settlement_date = '%s'"), selectedDate);

	CStringA cstrA(query);
	const char* cstr = cstrA;

	// settlement 테이블에서 settlement_date가 selectedDate인 항목 검색
	if (mysql_query(&Connect, cstr) == 0) {
		sql_result = mysql_store_result(&Connect);
		if (sql_result != NULL) {
			// 결과를 CListCtrl에 추가
			int row = 0;
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				// 각 컬럼의 데이터를 가져와서 CListCtrl에 추가
				CString index, date, name, affairs, is_completed;
				index = sql_row[0];
				date = sql_row[1];
				name = sql_row[2];
				affairs = sql_row[3];
				is_completed = sql_row[6];

				int completedValue = _ttoi(is_completed);
				is_completed = (completedValue == 0) ? _T("X") : _T("O");


				pListCtrl->InsertItem(row, index);
				pListCtrl->SetItem(row, 1, LVIF_TEXT, date, 0, 0, 0, 0);
				pListCtrl->SetItem(row, 2, LVIF_TEXT, name, 0, 0, 0, 0);
				pListCtrl->SetItem(row, 3, LVIF_TEXT, affairs, 0, 0, 0, 0);
				pListCtrl->SetItem(row, 4, LVIF_TEXT, is_completed, 0, 0, 0, 0);

				row++;
			}
			mysql_free_result(sql_result);

			UpdateData(FALSE);
		}
	}
	else {
		// 쿼리 실행이 실패함
			// 에러 처리 코드 추가
		CString error(mysql_error(&Connect));
		// 에러 메시지를 출력하거나 로그에 기록
		AfxMessageBox(_T("Error executing query: ") + query);
		AfxMessageBox(_T("Error executing query: ") + error);
	}
}


void CDutchPayHelperDlg::OnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_nSelectedPay >= 0) {

		CString index = m_listDutchPay.GetItemText(m_nSelectedPay, 0);
		int nIndex = _ttoi(index);

		// settlement 삭제
		CString query;
		query.Format(_T("DELETE FROM settlement WHERE seq = %d"), nIndex);
		CStringA settlementA(query);
		const char* cstr = settlementA;
		if (mysql_query(&Connect, cstr) != 0) {
			CString error(mysql_error(&Connect));
			AfxMessageBox(_T("Error executing query: ") + error);
		}

		// content 삭제
		query.Format(_T("SELECT content_seq FROM content WHERE  settlement_seq = %d"), nIndex);
		CStringA contentA(query);
		cstr = contentA;
		mysql_query(&Connect, cstr);
		sql_result = mysql_store_result(&Connect);
		sql_row = mysql_fetch_row(sql_result);
		CString strIndex;
		strIndex = sql_row[0];
		mysql_free_result(sql_result);

		query.Format(_T("DELETE FROM content WHERE settlement_seq = %d"), nIndex);
		CStringA content(query);
		cstr = content;
		if (mysql_query(&Connect, cstr) != 0) {
			CString error(mysql_error(&Connect));
			AfxMessageBox(_T("Error executing query: ") + error);
		}

		
		query.Format(_T("DELETE FROM participants WHERE content_seq = %d"), _ttoi(strIndex));
		CStringA participantsA(query);
		cstr = participantsA;
		if (mysql_query(&Connect, cstr) != 0) {
			CString error(mysql_error(&Connect));
			AfxMessageBox(_T("Error executing query: ") + error);
		}

		m_listDutchPay.DeleteItem(m_nSelectedPay);

		UpdateData(FALSE);
	}
	else {
		MessageBox(_T("삭제할 내용을 선택하지 않았습니다."), MB_OK);
	}
}


void CDutchPayHelperDlg::OnLvnItemchangedListDutchpay(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelectedPay = pNMLV->iItem;

	*pResult = 0;
}


void CDutchPayHelperDlg::OnClickedButtonViewDetails()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_nSelectedPay >= 0) {
		CViewSettlementDlg* pdlgView = new CViewSettlementDlg;
		pdlgView->SetViewParentDlg(this);
		pdlgView->DoModal();
	}
	else {
		MessageBox(_T("조회할 내용을 선택하지 않았습니다."), MB_OK);
	}
}
