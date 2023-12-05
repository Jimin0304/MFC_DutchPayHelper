// CAddSettlementDlg.cpp: 구현 파일
//

#include "pch.h"
#include "DutchPayHelper.h"
#include "CAddSettlementDlg.h"
#include "afxdialogex.h"
#include "DutchPayHelperDlg.h"
#include "CChangeUnitDlg.h"


// CAddSettlementDlg 대화 상자

IMPLEMENT_DYNAMIC(CAddSettlementDlg, CDialogEx)

CAddSettlementDlg::CAddSettlementDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD, pParent)
	, m_nAmount(0)
	, m_strDate(_T(""))
	, m_strPlace(_T(""))
	, m_strFriend(_T(""))
	, m_strCalculateName(_T(""))
	, m_strAccountNum(_T(""))
	, m_strGeneralAffairs(_T(""))
	, m_strMemo(_T(""))
{

}

CAddSettlementDlg::~CAddSettlementDlg()
{
}

void CAddSettlementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FRIEND, m_listFriend);
	DDX_Text(pDX, IDC_EDIT_AMOUNT, m_nAmount);
	DDX_Text(pDX, IDC_EDIT_DATE, m_strDate);
	DDX_Control(pDX, IDC_COMBO_UNIT, m_cbUnit);
	DDX_Text(pDX, IDC_EDIT_PLACE, m_strPlace);
	DDX_Text(pDX, IDC_EDIT_FRIEND, m_strFriend);
	DDX_Text(pDX, IDC_EDIT_CALCULATE_NAME, m_strCalculateName);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT_NUMBER, m_strAccountNum);
	DDX_Text(pDX, IDC_EDIT_GENERAL_AFFAIRS, m_strGeneralAffairs);
	DDX_Text(pDX, IDC_EDIT_MEMO, m_strMemo);
	DDX_Control(pDX, IDC_LIST_CALCULATE, m_listCalculate);
	DDX_Control(pDX, IDC_COMBO_SELECTED_UNIT, m_cbSelectedUnit);
}


BEGIN_MESSAGE_MAP(CAddSettlementDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CALCULATE_ADD, &CAddSettlementDlg::OnBnClickedButtonCalculateAdd)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CALCULATE, &CAddSettlementDlg::OnLvnItemchangedListCalculate)
	ON_BN_CLICKED(IDC_BUTTON_CALCULATE_DELETE, &CAddSettlementDlg::OnClickedButtonCalculateDelete)
	ON_BN_CLICKED(IDC_BUTTON_FRIEND_ADD, &CAddSettlementDlg::OnClickedButtonFriendAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_FRIENDS, &CAddSettlementDlg::OnClickedButtonEditFriends)
	ON_BN_CLICKED(IDC_BUTTON_FRIEND_DELETE, &CAddSettlementDlg::OnClickedButtonFriendDelete)
	ON_BN_CLICKED(IDOK, &CAddSettlementDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddSettlementDlg 메시지 처리기

void CAddSettlementDlg::OnBnClickedButtonCalculateAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_cbUnit.GetCurSel();
	int nCount = m_listCalculate.GetItemCount();
	CString strSettlement;
	CString strAmount;

	UpdateData(TRUE);
	if (m_nAmount) {	// 금액에 입력했을 때만
		strSettlement.Format(_T("%d차"), nCount + 1);	//차수 추가
		strAmount.Format(_T("%d"), m_nAmount);
		if (index == 0)	// 금액 뒤에 단위 추가
			strAmount += _T("원");
		else if (index == 1)
			strAmount += _T("달러");
		else if (index == 2)
			strAmount += _T("엔");

		m_listCalculate.InsertItem(nCount, strSettlement);
		m_listCalculate.SetItem(nCount, 1, LVIF_TEXT, strAmount, 0, 0, 0, 0);
		m_listCalculate.SetItem(nCount, 2, LVIF_TEXT, m_strPlace, 0, 0, 0, 0);

		// 금액, 장소 변수 초기화
		m_nAmount = 0;
		m_strPlace.Empty();

		// 차수 총 개수 계속 업데이트
		m_nCountCal = nCount + 1;

		UpdateData(FALSE);
	}
	else {
		MessageBox(_T("금액을 입력해주세요."), MB_OK);
	}
}

BOOL CAddSettlementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// m_listCalculate 초기화
	m_listCalculate.InsertColumn(0, _T("차수"), LVCFMT_CENTER, 40);
	m_listCalculate.InsertColumn(1, _T("금액"), LVCFMT_CENTER, 95);
	m_listCalculate.InsertColumn(2, _T("장소"), LVCFMT_CENTER, 85);
	m_listCalculate.InsertColumn(3, _T("참여자"), LVCFMT_CENTER, 120);
	m_listCalculate.SetExtendedStyle(m_listCalculate.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->SetCurSel(0);				// '원'으로 초기화
	((CComboBox*)GetDlgItem(IDC_COMBO_SELECTED_UNIT))->SetCurSel(0);	// '원'으로 초기화
	
	// 상단에 날짜 제목
	m_strDate = m_pDlg->m_timeDT.Format(L"%Y-%m-%d");
	CFont g_editFont;
	g_editFont.CreatePointFont(150, TEXT("굴림"));	// 크기 및 폰트 변경
	GetDlgItem(IDC_EDIT_DATE)->SetFont(&g_editFont);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAddSettlementDlg::OnLvnItemchangedListCalculate(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelectedItem = pNMLV->iItem;

	*pResult = 0;
}


void CAddSettlementDlg::OnClickedButtonCalculateDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_nSelectedItem >= 0) {
		m_listCalculate.DeleteItem(m_nSelectedItem);

		// 중간에 삭제된 차수 앞으로 당겨서 채워주기
		for (int i = m_nSelectedItem - 1; i < m_listCalculate.GetItemCount(); i++) {
			CString strIndex;

			strIndex.Format(_T("%d차"), i + 1);
			m_listCalculate.SetItemText(i, 0, strIndex);
		}

		// 차수 총 개수 하나 감소
		m_nCountCal -= 1;

		UpdateData(FALSE);
	}
	else {
		MessageBox(_T("삭제할 내용을 선택하지 않았습니다."), MB_OK);
	}
}

CString CAddSettlementDlg::ChangeListToString()
{
	// TODO: 여기에 구현 코드 추가.
	int itemCount = m_listFriend.GetCount();
	CString resultString;

	for (int i = 0; i < itemCount; ++i)
	{
		CString itemName;
		m_listFriend.GetText(i, itemName);
		
		// <이름>, <이름>, ... 형태로 만든다.
		if (!resultString.IsEmpty()) {
			resultString += _T(", ");
		}
		resultString += itemName;
	}

	return (resultString);
}


void CAddSettlementDlg::OnClickedButtonFriendAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (m_strFriend.IsEmpty() == FALSE)		// 이름 입력이 안되어있을 때
	{
		m_listFriend.AddString(m_strFriend);
		m_strFriend.Empty();	// 초기화
	}
	else
	{
		MessageBox(_T("참여자 이름을 입력해주세요."));
	}
	UpdateData(FALSE);
}

void CAddSettlementDlg::OnClickedButtonEditFriends()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	int nCount;
	CString strName;

	if (m_nSelectedItem >= 0) {		// 참여자를 편집할 정산을 선택했을 때
		nCount = m_listFriend.GetCount();

		if (nCount) {
			strName = ChangeListToString();	// m_listFriend의 값들을 string 형식으로 변환
			m_listCalculate.SetItem(m_nSelectedItem, 3, LVIF_TEXT, strName, 0, 0, 0, 0);
		}
		else {
			MessageBox(_T("참여자는 1명 이상이어야 합니다."), MB_OK);
		}
	}
	else {
		MessageBox(_T("편집할 내용을 선택하지 않았습니다."), MB_OK);
	}
}


void CAddSettlementDlg::OnClickedButtonFriendDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nIndex = m_listFriend.GetCurSel(); // 현재 선택된 항목의 인덱스 가져오기

	if (nIndex != LB_ERR) // LB_ERR는 선택된 항목이 없는 경우 반환되는 값
	{
		m_listFriend.DeleteString(nIndex);
	}
	else
	{
		MessageBox(_T("삭제할 이름을 선택하지 않았습니다."), MB_OK);
	}
}

void CAddSettlementDlg::SetParentDlg(CDutchPayHelperDlg* dlg)
{
	// TODO: 여기에 구현 코드 추가.
	// 부모 다이얼로그인 CDutchPayHelperDlg 저장
	m_pDlg = dlg;
}


void CAddSettlementDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (m_nCountCal > 0)
	{
		CString settlement;

		// settlement table에 데이터 추가
		settlement = _T("INSERT INTO settlement (settlement_date, settlement_name, general_affairs, account_num, memo, is_completed, amount_unit) VALUES (\'");
		settlement += m_strDate + _T("\'");

		// 정산 정보는 있어도 되고, 없어도 됨. 없으면 NULL로 입력
		if (m_strCalculateName.IsEmpty()) { settlement += _T(", NULL"); }
		else { settlement += _T(", \'") + m_strCalculateName + _T("\'"); }

		if (m_strGeneralAffairs.IsEmpty()) { settlement += _T(", NULL"); }
		else { settlement += _T(", \'") + m_strGeneralAffairs + _T("\'"); }

		if (m_strAccountNum.IsEmpty()) { settlement += _T(", NULL"); }
		else { settlement += _T(", \'") + m_strAccountNum + _T("\'"); }

		if (m_strMemo.IsEmpty()) { settlement += _T(", NULL"); }
		else { settlement += _T(", \'") + m_strMemo + _T("\'"); }

		// 정산 미완료 상태
		settlement += _T(", 0, ");

		// 계산되길 원하는 화폐 단위 저장
		if (m_cbSelectedUnit.GetCurSel() == 0)
		{
			settlement += _T("'원')");
			m_strUnit = _T("원");
		}
		else if (m_cbSelectedUnit.GetCurSel() == 1) {
			settlement += _T("'달러')");
			m_strUnit = _T("달러");
		}
		else if (m_cbSelectedUnit.GetCurSel() == 2) {
			settlement += _T("'엔')");
			m_strUnit = _T("엔");
		}

		CStringA cstrA(settlement);
		const char* cstr = cstrA;

		if (mysql_query(&Connect, cstr) != 0) {
			CString error(mysql_error(&Connect));
			AfxMessageBox(_T("Error executing query: ") + error);
		}

		// content table에 데이터 추가
		CString tmp;

		mysql_query(&Connect, "select MAX(seq) from settlement");
		sql_result = mysql_store_result(&Connect);
		if (sql_result == NULL)
			AfxMessageBox(_T("조회된 settlement가 없습니다."));
		sql_row = mysql_fetch_row(sql_result);
		CString strIndex;
		strIndex = sql_row[0];
		m_nSettlementIndex = _ttoi(strIndex);
		mysql_free_result(sql_result);

		int unitIndex, unitLen;
		CString degree, strAmount, place, nameList;

		for (int i = 0; i < m_nCountCal; i++) {

			degree = m_listCalculate.GetItemText(i, 0);
			strAmount = m_listCalculate.GetItemText(i, 1);
			if (strAmount.Find(_T("원")) != -1) {	// content의 화폐 단위가 '원'일 때
				unitIndex = 0;		// m_cbSelectedUnit와 비교하기 위해 unitIndex 지정
				unitLen = 1;		// 단위 문자열 길이
			}
			else if (strAmount.Find(_T("달러")) != -1) {	// content의 화폐 단위가 '달러'일 때
				unitIndex = 1;
				unitLen = 2;
			}
			else if (strAmount.Find(_T("엔")) != -1) {	// content의 화폐 단위가 '엔'일 때
				unitIndex = 2;
				unitLen = 1;
			}

			// 금액만 추출하기 위하여 뒤에 화폐 단위 제거
			m_nAmount = _ttoi(strAmount.Left(strAmount.GetLength() - unitLen));

			// 계산하기로 지정한 화폐 단위와 content 화폐 단위 다를 때
			if (m_cbSelectedUnit.GetCurSel() != unitIndex) {
				m_cbSelectedUnit.GetLBText(unitIndex, m_strPresnetUnit);	// m_strPresentUnit에 unitIndex번의 데이터 값 저장
				
				// 환율 계산을 하기 위해 CChangeUnitDlg 모달 띄움
				CChangeUnitDlg* pdlgUnit = new CChangeUnitDlg;
				pdlgUnit->SetAddDlg(this);
				if (pdlgUnit->DoModal() == IDOK) {
					m_nAmount = pdlgUnit->m_nChangeValue;	// 환율 적용된 값 가져옴
				}
				pdlgUnit->m_addDlg = nullptr;	// 부모를 헷갈리지 않기 위해 nullptr (view와 같이 사용하기 때문)
			}

			// 장소
			place = m_listCalculate.GetItemText(i, 2);
			if (place.IsEmpty())
				place = _T("NULL");
			else
				place = _T("'") + place + _T("'");

			// 참여자 리스트
			nameList = m_listCalculate.GetItemText(i, 3);

			tmp.Format(_T("INSERT INTO content (settlement_seq, degree, amount, place) VALUES (%d, '%s', %ld, %s)"),
				_ttoi(strIndex), degree, m_nAmount, place);

			CStringA contentA(tmp);
			const char* content = contentA;

			if (mysql_query(&Connect, content) != 0) {
				CString error(mysql_error(&Connect));
				AfxMessageBox(_T("Error executing query: ") + error);

				// 트랜잭션 롤백
				mysql_rollback(&Connect);
			}
			else {
				// 트랜잭션 커밋
				mysql_commit(&Connect);
				InsertParticipants(m_nAmount, nameList);	// participants table에 참여자 리스트 삽입
			}
		}
	}
	else
	{
		MessageBox(_T("정산 내용이 없습니다."));
	}

	CDialogEx::OnOK();
}


void CAddSettlementDlg::InsertParticipants(int amount, CString nameList)
{
	// TODO: 여기에 구현 코드 추가.
	// participants table에 데이터 추가
	mysql_query(&Connect, "select MAX(content_seq) from content");	// 제일 최근에 추가된 content seq 값 가져옴
	sql_result = mysql_store_result(&Connect);
	if (sql_result == NULL)
		AfxMessageBox(_T("조회된 content가 없습니다."));
	sql_row = mysql_fetch_row(sql_result);
	CString strIndex;
	strIndex = sql_row[0];
	mysql_free_result(sql_result);

	CString token;
	int pos = 0;	// 사람 수

	// <이름>, <이름>, .. 형식의 string을 parsing해서 데이터 삽입
	while (AfxExtractSubString(token, nameList, pos, ','))	// ','을 구분자로 데이터 추출
	{
		// 좌우 공백 제거
		token.TrimLeft();
		token.TrimRight();

		int cnt = 0;

		if (!token.IsEmpty()) {
			CString participant;

			participant.Format(_T("INSERT INTO participants (content_seq, name, paid) VALUES (%d, '%s', %d)"),
				_ttoi(strIndex), token, 0);

			CStringA contentA(participant);
			const char* content = contentA;

			if (mysql_query(&Connect, content) != 0) {
				CString error(mysql_error(&Connect));
				AfxMessageBox(_T("Error executing query: ") + error);
				mysql_rollback(&Connect);
			}
			else {
				mysql_commit(&Connect);
			}
		}

		// 다음 토큰을 찾기 위해 위치 업데이트
		pos++;
	}

	// 각 차수 당 내야할 돈 계산하여 저장
	int pay = amount / pos;
	CString moneyToPay;

	moneyToPay.Format(_T("UPDATE participants SET money_to_pay = %d WHERE content_seq = %d"), pay, _ttoi(strIndex));

	CStringA moneyToPayA(moneyToPay);
	const char* payA = moneyToPayA;

	if (mysql_query(&Connect, payA) != 0) {
		CString error(mysql_error(&Connect));
		AfxMessageBox(_T("Error executing query: ") + error);
		mysql_rollback(&Connect);
	}
	else {
		mysql_commit(&Connect);
	}
}
