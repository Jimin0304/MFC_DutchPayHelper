// CAddSettlementDlg.cpp: 구현 파일
//

#include "pch.h"
#include "DutchPayHelper.h"
#include "CAddSettlementDlg.h"
#include "afxdialogex.h"
#include "DutchPayHelperDlg.h"


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
	//  DDX_Control(pDX, IDC_LIST_CALCULATE, m_listCalculate);
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
}


BEGIN_MESSAGE_MAP(CAddSettlementDlg, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST_CALCULATE, &CAddSettlementDlg::OnLbnSelchangeListCalculate)
	ON_LBN_SELCHANGE(IDC_LIST_FRIEND, &CAddSettlementDlg::OnLbnSelchangeListFriend)
	ON_EN_CHANGE(IDC_EDIT_AMOUNT, &CAddSettlementDlg::OnEnChangeEditAmount)
	ON_EN_CHANGE(IDC_EDIT_DATE, &CAddSettlementDlg::OnEnChangeEditDate)
	ON_CBN_SELCHANGE(IDC_COMBO_UNIT, &CAddSettlementDlg::OnCbnSelchangeComboUnit)
	ON_EN_CHANGE(IDC_EDIT_PLACE, &CAddSettlementDlg::OnEnChangeEditPlace)
	ON_BN_CLICKED(IDC_BUTTON_CALCULATE_ADD, &CAddSettlementDlg::OnBnClickedButtonCalculateAdd)
	ON_EN_CHANGE(IDC_EDIT_FRIEND, &CAddSettlementDlg::OnEnChangeEditFriend)
	ON_EN_CHANGE(IDC_EDIT_CALCULATE_NAME, &CAddSettlementDlg::OnEnChangeEditCalculateName)
	ON_EN_CHANGE(IDC_EDIT_GENERAL_AFFAIRS, &CAddSettlementDlg::OnEnChangeEditGeneralAffairs)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CALCULATE, &CAddSettlementDlg::OnLvnItemchangedListCalculate)
	ON_BN_CLICKED(IDC_BUTTON_CALCULATE_DELETE, &CAddSettlementDlg::OnClickedButtonCalculateDelete)
	ON_BN_CLICKED(IDC_BUTTON_FRIEND_ADD, &CAddSettlementDlg::OnClickedButtonFriendAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_FRIENDS, &CAddSettlementDlg::OnClickedButtonEditFriends)
	ON_BN_CLICKED(IDC_BUTTON_FRIEND_DELETE, &CAddSettlementDlg::OnClickedButtonFriendDelete)
	ON_BN_CLICKED(IDOK, &CAddSettlementDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddSettlementDlg 메시지 처리기


void CAddSettlementDlg::OnLbnSelchangeListCalculate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAddSettlementDlg::OnLbnSelchangeListFriend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAddSettlementDlg::OnEnChangeEditAmount()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAddSettlementDlg::OnEnChangeEditDate()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAddSettlementDlg::OnCbnSelchangeComboUnit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAddSettlementDlg::OnEnChangeEditPlace()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAddSettlementDlg::OnBnClickedButtonCalculateAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_cbUnit.GetCurSel();

	int nCount = m_listCalculate.GetItemCount();
	CString strSettlement;
	CString strAmount;

	UpdateData(TRUE);
	if (m_nAmount) {
		strSettlement.Format(_T("%d차"), nCount + 1);
		strAmount.Format(_T("%d"), m_nAmount);
		if (index == 0)
			strAmount += _T("원");
		else if (index == 1)
			strAmount += _T("달러");
		else if (index == 2)
			strAmount += _T("엔");

		m_listCalculate.InsertItem(nCount, strSettlement);
		m_listCalculate.SetItem(nCount, 1, LVIF_TEXT, strAmount, 0, 0, 0, 0);
		m_listCalculate.SetItem(nCount, 2, LVIF_TEXT, m_strPlace, 0, 0, 0, 0);

		m_nAmount = 0;
		m_strPlace.Empty();

		m_nCountCal = nCount + 1;

		UpdateData(FALSE);
	}
	else {
		MessageBox(_T("금액을 입력해주세요."), MB_OK);
	}
}


void CAddSettlementDlg::OnEnChangeEditFriend()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAddSettlementDlg::OnEnChangeEditCalculateName()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAddSettlementDlg::OnEnChangeEditGeneralAffairs()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


BOOL CAddSettlementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_listCalculate.InsertColumn(0, _T("차수"), LVCFMT_CENTER, 40);
	m_listCalculate.InsertColumn(1, _T("금액"), LVCFMT_CENTER, 95);
	m_listCalculate.InsertColumn(2, _T("장소"), LVCFMT_CENTER, 85);
	m_listCalculate.InsertColumn(3, _T("참여자"), LVCFMT_CENTER, 120);

	m_listCalculate.SetExtendedStyle(m_listCalculate.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	((CComboBox*)GetDlgItem(IDC_COMBO_UNIT))->SetCurSel(0);
	
	m_strDate = m_pDlg->m_timeDT.Format(L"%Y-%m-%d");
	CFont g_editFont;
	g_editFont.CreatePointFont(150, TEXT("굴림"));
	GetDlgItem(IDC_EDIT_DATE)->SetFont(&g_editFont);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAddSettlementDlg::OnLvnItemchangedList3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CAddSettlementDlg::OnLvnItemchangedListCalculate(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelectedItem = pNMLV->iItem;

/*	CString strFriends = m_listCalculate.GetItemText(m_nSelectedItem, 3);

	if (m_nSelectedItem >= 0 && strFriends.IsEmpty() == FALSE) {
		UpdateFriendListBox(strFriends);
	}
*/
	*pResult = 0;
}


void CAddSettlementDlg::OnClickedButtonCalculateDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_nSelectedItem >= 0) {
		m_listCalculate.DeleteItem(m_nSelectedItem);

		for (int i = m_nSelectedItem - 1; i < m_listCalculate.GetItemCount(); i++) {
			CString strIndex;

			strIndex.Format(_T("%d차"), i + 1);
			m_listCalculate.SetItemText(i, 0, strIndex);
		}

		UpdateData(FALSE);
	}
	else {
		MessageBox(_T("삭제할 내용을 선택하지 않았습니다."), MB_OK);
	}
	/*
	for (int i = 0; i < m_listCalculate.GetItemCount(); i++) {
		MessageBox(_T("Degree: ") + m_listCalculate.GetItemText(i, 0) + _T("\n"));
		MessageBox(_T("Amount: ") + m_listCalculate.GetItemText(i, 1) + _T("\n"));
		MessageBox(_T("Place: ") + m_listCalculate.GetItemText(i, 2) + _T("\n"));
	}*/
}

CString CAddSettlementDlg::ChangeListToString()
{
	// TODO: 여기에 구현 코드 추가.
	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_FRIEND); // IDC_YOUR_LIST_BOX는 여러분이 사용하는 실제 ID로 변경해야 합니다.

	int itemCount = pListBox->GetCount();
	CString resultString;

	for (int i = 0; i < itemCount; ++i)
	{
		CString itemName;
		pListBox->GetText(i, itemName);

		if (!resultString.IsEmpty())
		{
			resultString += _T(", ");
		}

		resultString += itemName;
	}

	return (resultString);
}

void CAddSettlementDlg::UpdateFriendListBox(CString str)
{
	// TODO: 여기에 구현 코드 추가.
	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_FRIEND); // IDC_YOUR_LIST_BOX는 여러분이 사용하는 실제 ID로 변경해야 합니다.

	pListBox->ResetContent(); // ListBox를 초기화합니다.

	// Tokenize를 사용하여 각 이름을 추출합니다.
	CString delimiter = _T(", ");
	int start = 0;
	int end = str.Find(delimiter);

	while (end != -1)
	{
		CString name = str.Mid(start, end - start);
		pListBox->AddString(name);
		start = end + delimiter.GetLength();
		end = str.Find(delimiter, start);
	}

	// 마지막 이름을 ListBox에 추가합니다.
	CString last_name = str.Mid(start);
	pListBox->AddString(last_name);

	UpdateData(FALSE);
}


void CAddSettlementDlg::OnClickedButtonFriendAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (m_strFriend.IsEmpty() == FALSE)
	{
		m_listFriend.AddString(m_strFriend);
		m_strFriend.Empty();
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

	if (m_nSelectedItem >= 0) {
		nCount = m_listFriend.GetCount();

		if (nCount) {
			strName = ChangeListToString();
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
	m_pDlg = dlg;
}

CListCtrl* CAddSettlementDlg::GetListCtrlPointer()
{
	// TODO: 여기에 구현 코드 추가.
	return &m_listCalculate;;
}


void CAddSettlementDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (m_nCountCal > 0)
	{
		CString settlement;

		// settlement db 추가
		settlement = _T("INSERT INTO settlement (settlement_date, settlement_name, general_affairs, account_num, memo, is_completed) VALUES (\'");
		settlement += m_strDate + _T("\'");

		if (m_strCalculateName.IsEmpty()) { settlement += _T(", NULL"); }
		else { settlement += _T(", \'") + m_strCalculateName + _T("\'"); }

		if (m_strGeneralAffairs.IsEmpty()) { settlement += _T(", NULL"); }
		else { settlement += _T(", \'") + m_strGeneralAffairs + _T("\'"); }

		if (m_strAccountNum.IsEmpty()) { settlement += _T(", NULL"); }
		else { settlement += _T(", \'") + m_strAccountNum + _T("\'"); }

		if (m_strMemo.IsEmpty()) { settlement += _T(", NULL"); }
		else { settlement += _T(", \'") + m_strMemo + _T("\'"); }

		settlement += _T(", 0)");

		CStringA cstrA(settlement);
		const char* cstr = cstrA;

		if (mysql_query(&Connect, cstr) != 0) {
			// 쿼리 실행이 실패함
			// 에러 처리 코드 추가
			CString error(mysql_error(&Connect));
			// 에러 메시지를 출력하거나 로그에 기록
			AfxMessageBox(_T("Error executing query: ") + settlement);
			AfxMessageBox(_T("Error executing query: ") + error);
		}

		// content db 추가
		CString tmp;

		mysql_query(&Connect, "select MAX(seq) from settlement");
		sql_result = mysql_store_result(&Connect);
		if (sql_result == NULL)
			AfxMessageBox(_T("조회된 settlement가 없습니다."));
		sql_row = mysql_fetch_row(sql_result);
		CString strIndex;
		strIndex = sql_row[0];

		long amount;
		CString degree, strAmount, unit, place, nameList;

		for (int i = 0; i < m_nCountCal; i++) {

			degree = m_listCalculate.GetItemText(i, 0);
			strAmount = m_listCalculate.GetItemText(i, 1);
			amount = _ttoi(strAmount.Left(strAmount.GetLength() - 1));
			unit = strAmount.Right(1);
			place = m_listCalculate.GetItemText(i, 2);
			if (place.IsEmpty()) {
				place = _T("NULL");
			}
			else {
				place = _T("'") + place + _T("'");
			}
			nameList = m_listCalculate.GetItemText(i, 3);

			tmp.Format(_T("INSERT INTO content (settlement_seq, degree, amount, unit, place) VALUES (%d, '%s', %ld, '%s', %s)"),
				_ttoi(strIndex), degree, amount, unit, place);

			CStringA contentA(tmp);
			const char* content = contentA;

			if (mysql_query(&Connect, content) != 0) {
				// 쿼리 실행이 실패함
				// 에러 처리 코드 추가
				CString error(mysql_error(&Connect));
				// 에러 메시지를 출력하거나 로그에 기록
				AfxMessageBox(_T("Error executing query: ") + error);

				// 트랜잭션 롤백
				mysql_rollback(&Connect);
				mysql_free_result(sql_result);
			}
			else {
				// 쿼리 실행이 성공함
				// 트랜잭션 커밋
				mysql_commit(&Connect);
				mysql_free_result(sql_result);
				InsertParticipants(nameList);
			}
		}
	}
	else
	{
		MessageBox(_T("정산 내용이 없습니다."));
	}

	CDialogEx::OnOK();
}


void CAddSettlementDlg::InsertParticipants(CString nameList)
{
	// TODO: 여기에 구현 코드 추가.
	// participants db
	mysql_query(&Connect, "select MAX(content_seq) from content");
	sql_result = mysql_store_result(&Connect);
	if (sql_result == NULL)
		AfxMessageBox(_T("조회된 content가 없습니다."));
	CString strIndex;
	strIndex = sql_row[0];

	CString token;
	int pos = 0;

	while (AfxExtractSubString(token, nameList, pos, ','))
	{
		// 좌우 공백 제거
		token.TrimLeft();
		token.TrimRight();

		// 결과 DB에 추가
		if (!token.IsEmpty()) {
			CString participant;

			participant.Format(_T("INSERT INTO participants (content_seq, name, paid) VALUES (%d, '%s', %d)"),
				_ttoi(strIndex), token, 0);

			CStringA contentA(participant);
			const char* content = contentA;

			if (mysql_query(&Connect, content) != 0) {
				// 쿼리 실행이 실패함
				// 에러 처리 코드 추가
				CString error(mysql_error(&Connect));
				// 에러 메시지를 출력하거나 로그에 기록
				AfxMessageBox(_T("Error executing query: ") + error);

				// 트랜잭션 롤백
				mysql_rollback(&Connect);
			}
			else {
				// 쿼리 실행이 성공함
				// 트랜잭션 커밋
				mysql_commit(&Connect);
			}
			mysql_free_result(sql_result);
		}

		// 다음 토큰을 찾기 위해 위치 업데이트
		pos++;
	}
}
