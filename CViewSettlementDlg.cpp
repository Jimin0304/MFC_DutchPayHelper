// CViewSettlementDlg.cpp: 구현 파일
//

#include "pch.h"
#include "DutchPayHelper.h"
#include "CViewSettlementDlg.h"
#include "afxdialogex.h"
#include "DutchPayHelperDlg.h"


// CViewSettlementDlg 대화 상자

IMPLEMENT_DYNAMIC(CViewSettlementDlg, CDialogEx)

CViewSettlementDlg::CViewSettlementDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_VIEW, pParent)
	, m_strDate(_T(""))
	, m_strCalcName(_T(""))
	, m_strGeneralAffairs(_T(""))
	, m_strMemo(_T(""))
	, m_strAccountNum(_T(""))
	, m_bChecked(FALSE)
	, m_nUnsettledNum(0)
	, m_nBalance(0)
	, m_strDegree(_T(""))
	, m_strName(_T(""))
	, m_nAmount(0)
{

}

CViewSettlementDlg::~CViewSettlementDlg()
{
}

void CViewSettlementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_VIEW_DATE, m_strDate);
	DDX_Text(pDX, IDC_EDIT_CALCULATE_NAME, m_strCalcName);
	DDX_Text(pDX, IDC_EDIT_GENERAL_AFFAIRS, m_strGeneralAffairs);
	DDX_Text(pDX, IDC_EDIT_MEMO, m_strMemo);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT_NUMBER, m_strAccountNum);
	DDX_Control(pDX, IDC_TREE_CONTROL, m_treeControl);
	DDX_Check(pDX, IDC_CHECK_FINISH, m_bChecked);
	//  DDX_CBString(pDX, IDC_COMBO_BALANCE_UNIT, m_strUnit);
	DDX_Control(pDX, IDC_COMBO_UNIT, m_cbUnit);
	DDX_Control(pDX, IDC_COMBO_BALANCE_UNIT, m_cbBalanceUnit);
	//  DDX_Text(pDX, IDC_EDIT_BALANCE, m_strBalance);
	DDX_Text(pDX, IDC_EDIT_UNSETTLED_NUM, m_nUnsettledNum);
	DDX_Text(pDX, IDC_EDIT_BALANCE, m_nBalance);
	DDX_Text(pDX, IDC_EDIT_DEGREE, m_strDegree);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	//  DDX_Text(pDX, IDC_EDIT_AMOUNT, m_strAmount);
	DDX_Text(pDX, IDC_EDIT_AMOUNT, m_nAmount);
}


BEGIN_MESSAGE_MAP(CViewSettlementDlg, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_CONTROL, &CViewSettlementDlg::OnSelchangedTreeControl)
	ON_BN_CLICKED(IDOK, &CViewSettlementDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CViewSettlementDlg 메시지 처리기


void CViewSettlementDlg::SetViewParentDlg(CDutchPayHelperDlg* dlg)
{
	// TODO: 여기에 구현 코드 추가.
	m_pDlg = dlg;
}


BOOL CViewSettlementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	// 날짜 
	CString index = m_pDlg->m_listDutchPay.GetItemText(m_pDlg->m_nSelectedPay, 0);
	m_nIndex = _ttoi(index);
	m_strDate = m_pDlg->m_listDutchPay.GetItemText(m_pDlg->m_nSelectedPay, 1);
	CFont g_editFont;
	g_editFont.CreatePointFont(150, TEXT("굴림"));
	GetDlgItem(IDC_EDIT_VIEW_DATE)->SetFont(&g_editFont);

	CString query;
	query.Format(_T("SELECT * FROM settlement WHERE seq = %d"), m_nIndex);
	CStringA cstrA(query);
	const char* cstr = cstrA;
	mysql_query(&Connect, cstr);
	sql_result = mysql_store_result(&Connect);
	sql_row = mysql_fetch_row(sql_result);

	// 정산 정보
	m_strCalcName = sql_row[2];
	m_strGeneralAffairs = sql_row[3];
	m_strAccountNum = sql_row[4];
	m_strMemo = sql_row[5];
	m_bChecked = FALSE;
	
	// 트리 최상위 노드
	CString hRootNode = m_strDate;
	if (!m_strCalcName.IsEmpty()) {
		hRootNode += _T(" (") + m_strCalcName + _T(")");
	}

	m_hRoot = m_treeControl.InsertItem(hRootNode, 0, TVI_LAST);
	m_treeControl.Expand(m_hRoot, TVE_EXPAND);

	CString isComplete;
	isComplete = sql_row[6];
	m_treeControl.ModifyStyle(TVS_CHECKBOXES, 0);
	m_treeControl.ModifyStyle(0, TVS_CHECKBOXES);
	if (_ttoi(isComplete) == 1) {
		m_treeControl.SetCheck(m_hRoot, true);
		m_bChecked = TRUE;
	}
	mysql_free_result(sql_result);

	// 자식 노드 (차수)
	query.Format(_T("SELECT * FROM content WHERE settlement_seq = %d ORDER BY degree ASC"), m_nIndex);
	CStringA contentA(query);
	cstr = contentA;
	mysql_query(&Connect, cstr);
	sql_result = mysql_store_result(&Connect);
	int indexCount = 0;
	HTREEITEM hChild[100][100];
	CString listContentSeq[100][2];
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		CString degree, place, node;
		degree = sql_row[2];
		place = sql_row[5];
		listContentSeq[indexCount][0] = sql_row[0];	// content_seq
		listContentSeq[indexCount][1] = sql_row[4];	// unit
		
		node = degree;
		if (!place.IsEmpty()) {
			node += _T(" (") + place + _T(")");
		}
		hChild[indexCount++][0] = m_treeControl.InsertItem(node, m_hRoot);
	}

	// unit 콤보 박스 초기설정
	if (listContentSeq[0][1] == "원")
	{
		m_cbUnit.SetCurSel(0);
		m_cbBalanceUnit.SetCurSel(0);
	}
	else if (listContentSeq[0][1] == "달러") {
		m_cbUnit.SetCurSel(1);
		m_cbBalanceUnit.SetCurSel(1);
	}
	else if (listContentSeq[0][1] == "엔") {
		m_cbUnit.SetCurSel(2);
		m_cbBalanceUnit.SetCurSel(2);
	}
	mysql_free_result(sql_result);

	// 참여자 트리
	int unpaidTotalCount = 0;	// 미정산 인원
	int unpaidAmount = 0;		// 미정산 금액
	for (int i = 0; i < indexCount; i++) {
		query.Format(_T("SELECT * FROM participants WHERE content_seq = %d ORDER BY name ASC"), _ttoi(listContentSeq[i][0]));
		CStringA participantA(query);
		cstr = participantA;
		mysql_query(&Connect, cstr);
		sql_result = mysql_store_result(&Connect);
		int j = 1;
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			CString name, moneyToPay, item;
			name = sql_row[2];
			moneyToPay = sql_row[4];
			item = name + _T(", ") + moneyToPay + listContentSeq[i][1];
			hChild[i][j] = m_treeControl.InsertItem(item, hChild[i][0]);
			m_treeControl.Expand(hChild[i][j], TVE_EXPAND);

			CString isPaid;
			isPaid = sql_row[3];
			if (_ttoi(isPaid) == 1) {	// 정산일 때 체크 표시
				m_treeControl.SetCheck(hChild[i][j], true);
			}
			else {		// 미정산 상태일 때 정산 현황 정보
				unpaidTotalCount++;		
				unpaidAmount += _ttoi(moneyToPay);
			}
			j++;
		}
		mysql_free_result(sql_result);
	}
	m_nBalance = unpaidAmount;
	m_nUnsettledNum = unpaidTotalCount;

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CViewSettlementDlg::OnSelchangedTreeControl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_hSelectNode = pNMTreeView->itemNew.hItem;

	HTREEITEM hParentItem = m_treeControl.GetParentItem(m_hSelectNode);
	if (hParentItem == m_hRoot)	{	// 차수 노드를 선택했을 때
		// 차수
		CString degree = m_treeControl.GetItemText(m_hSelectNode);
		AfxExtractSubString(m_strDegree, degree, 0, _T('차'));
		m_strDegree += _T("차");
		
		// 참여자 이름
		// 첫 번째 자식 항목(노드) 가져오기
		HTREEITEM hChildItem = m_treeControl.GetChildItem(m_hSelectNode);
		CString nameList;

		// 자식 항목이 유효한지 확인 후 사용
		while (hChildItem != NULL) {
			// 자식 항목의 데이터 처리
			CString childText;
			AfxExtractSubString(childText, m_treeControl.GetItemText(hChildItem), 0, _T(','));
			nameList += childText + _T(", ");

			// 다음 자식 항목(노드) 가져오기
			hChildItem = m_treeControl.GetNextItem(hChildItem, TVGN_NEXT);
		}
		int len = nameList.GetLength() - 2;
		m_strName = nameList.Left(len);

		// 금액
		sql_row = GetContentByDegree(m_strDegree);
		CString strAmount;
		strAmount = sql_row[3];
		m_nAmount = _ttoi(strAmount);
	}
	else if (hParentItem !=  NULL) {	// 참여자 노드를 선택했을 때
		CString text = m_treeControl.GetItemText(m_hSelectNode);
		AfxExtractSubString(m_strName, text, 0, _T(','));

		// 모든 참여자 노드 돌면서 m_strName의 지불 금액 구하기
		HTREEITEM hChildItem = m_treeControl.GetChildItem(m_hRoot);
		int totalAmount = 0;
		m_strDegree = "";
		bool isAttend = FALSE;
		HTREEITEM hParticipantsItem;
		while (hChildItem != NULL) {	// 차수 노드 루프
			hParticipantsItem = m_treeControl.GetChildItem(hChildItem);
			while (hParticipantsItem != NULL) {		// 각 차수 노드의 참여자 노드 루프
				CString part = m_treeControl.GetItemText(hParticipantsItem);
				if (part.Find(m_strName) != -1) { // m_strName이 포함되어 있을 때
					int retval = 0;
					retval = part.Find(',');
					CString amount = part.Mid(retval + 2);
					if (amount.Find(_T("달러")))		// 끝에 unit 자르기
						amount = amount.Mid(0, amount.GetLength() - 1);
					else 
						amount = amount.Mid(0, amount.GetLength());
					totalAmount += _ttoi(amount);
					isAttend = TRUE;
				}
				hParticipantsItem = m_treeControl.GetNextItem(hParticipantsItem, TVGN_NEXT);	// 다음 참여자 노드
			}
			if (isAttend == TRUE) {
				CString degree;
				AfxExtractSubString(degree, m_treeControl.GetItemText(hChildItem), 0, _T('차'));
				m_strDegree += degree + _T(", ");
			}
			isAttend = FALSE;
			hChildItem = m_treeControl.GetNextItem(hChildItem, TVGN_NEXT);	// 다음 차수 노드
		}
		m_strDegree = m_strDegree.Mid(0, m_strDegree.GetLength() - 2);
		m_strDegree += _T("차");
		m_nAmount = totalAmount;
	}

	UpdateData(FALSE);
	*pResult = 0;
}

void CViewSettlementDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	// 모든 참여자 노드 돌면서 paid 상태 저장
	HTREEITEM hChildItem = m_treeControl.GetChildItem(m_hRoot);
	HTREEITEM hParticipantsItem;
	CString query;
	while (hChildItem != NULL) {	// 차수 노드 루프
		CString degree, content_seq;
		AfxExtractSubString(degree, m_treeControl.GetItemText(hChildItem), 0, _T('차'));
		degree += _T("차");
		sql_row = GetContentByDegree(degree);
		content_seq = sql_row[0];
		hParticipantsItem = m_treeControl.GetChildItem(hChildItem);
		while (hParticipantsItem != NULL) {		// 각 차수 노드의 참여자 노드 루프
			CString part = m_treeControl.GetItemText(hParticipantsItem);
			CString name;
			AfxExtractSubString(name, part, 0, _T(','));
			query.Format(_T("UPDATE participants SET paid = %d WHERE content_seq = %d AND name = '%s'")
				, m_treeControl.GetCheck(hParticipantsItem), _ttoi(content_seq), name);
			CStringA queryA(query);
			const char* cstr = queryA;
			mysql_query(&Connect, cstr);

			hParticipantsItem = m_treeControl.GetNextItem(hParticipantsItem, TVGN_NEXT);	// 다음 참여자 노드
		}
		hChildItem = m_treeControl.GetNextItem(hChildItem, TVGN_NEXT);	// 다음 차수 노드
	}

	// 정산 완료 상태, 정산 정보 수정
	query.Format(_T("UPDATE settlement SET is_completed = %d, settlement_name = '%s', general_affairs = '%s', account_num = '%s', memo = '%s' WHERE seq = %d"),
		m_bChecked, m_strCalcName, m_strGeneralAffairs, m_strAccountNum, m_strMemo, m_nIndex);
	CStringA queryA(query);
	const char* cstr = queryA;
	mysql_query(&Connect, cstr);

	CDialogEx::OnOK();
}


MYSQL_ROW CViewSettlementDlg::GetContentByDegree(CString degree)
{
	// TODO: 여기에 구현 코드 추가.
	CString query;
	query.Format(_T("SELECT * FROM content WHERE settlement_seq = %d AND degree = '%s'"), m_nIndex, degree);
	CStringA strA(query);
	const char* cstr = strA;
	mysql_query(&Connect, cstr);
	sql_result = mysql_store_result(&Connect);
	sql_row = mysql_fetch_row(sql_result);
	if (sql_row == NULL)
		AfxMessageBox(_T("조회된 sql_row가 없습니다."));
	mysql_free_result(sql_result);

	return sql_row;
}
