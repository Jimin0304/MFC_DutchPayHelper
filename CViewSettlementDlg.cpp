﻿// CViewSettlementDlg.cpp: 구현 파일
//

#include "pch.h"
#include "DutchPayHelper.h"
#include "CViewSettlementDlg.h"
#include "afxdialogex.h"
#include "DutchPayHelperDlg.h"
#include "CChangeUnitDlg.h"


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
	DDX_Control(pDX, IDC_COMBO_UNIT, m_cbUnit);
	DDX_Control(pDX, IDC_COMBO_BALANCE_UNIT, m_cbBalanceUnit);
	DDX_Text(pDX, IDC_EDIT_UNSETTLED_NUM, m_nUnsettledNum);
	DDX_Text(pDX, IDC_EDIT_BALANCE, m_nBalance);
	DDX_Text(pDX, IDC_EDIT_DEGREE, m_strDegree);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_AMOUNT, m_nAmount);
}


BEGIN_MESSAGE_MAP(CViewSettlementDlg, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_CONTROL, &CViewSettlementDlg::OnSelchangedTreeControl)
	ON_BN_CLICKED(IDOK, &CViewSettlementDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_BALANCE_UNIT, &CViewSettlementDlg::OnSelchangeComboBalanceUnit)
	ON_CBN_SELCHANGE(IDC_COMBO_UNIT, &CViewSettlementDlg::OnSelchangeComboUnit)
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
	// 상단 날짜 
	if (m_nIndex <= 0) {
		CString index = m_pDlg->m_listDutchPay.GetItemText(m_pDlg->m_nSelectedPay, 0);
		m_nIndex = _ttoi(index);
		m_strDate = m_pDlg->m_listDutchPay.GetItemText(m_pDlg->m_nSelectedPay, 1);
	}
	CFont g_editFont;
	g_editFont.CreatePointFont(150, TEXT("굴림"));
	GetDlgItem(IDC_EDIT_VIEW_DATE)->SetFont(&g_editFont);

	// db에서 settlement 가져옴
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
	m_strBalancePresentUnit = m_strAmountPresentUnit = sql_row[7];

	// 정산 완료 체크 박스 초기화
	m_bChecked = FALSE;
	
	// 트리 최상위 노드
	CString hRootNode = m_strDate;
	if (!m_strCalcName.IsEmpty()) {	// m_strCalcName이 있으면 뒤에 추가
		hRootNode += _T(" (") + m_strCalcName + _T(")");
	}

	// 루트 트리
	m_hRoot = m_treeControl.InsertItem(hRootNode, 0, TVI_LAST);
	m_treeControl.Expand(m_hRoot, TVE_EXPAND);

	// 정산 완료일 때 트리 확인란, m_bChecked 세팅
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
	HTREEITEM hChild[100][100];		// 행은 차수 노드, 열은 각 차수의 자식(참여자 노드)
	CString listContentSeq[100];	// content_seq 저장 리스트
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {	// content가 있을 때까지
		CString degree, place, node;
		degree = sql_row[2];
		place = sql_row[4];
		listContentSeq[indexCount] = sql_row[0];	// content_seq는 저장해놨다가 참여자 노드 만드는 데에 사용해야 함
		
		node = degree;
		if (!place.IsEmpty()) {		// 장소 있으면 뒤에 추가
			node += _T(" (") + place + _T(")");
		}
		hChild[indexCount++][0] = m_treeControl.InsertItem(node, m_hRoot);
	}

	// unit 콤보 박스 초기설정
	if (m_strAmountPresentUnit == "원")
	{
		m_cbUnit.SetCurSel(0);			// 전체 금액
		m_cbBalanceUnit.SetCurSel(0);	// 남은 금액
	}
	else if (m_strAmountPresentUnit == "달러") {
		m_cbUnit.SetCurSel(1);
		m_cbBalanceUnit.SetCurSel(1);
	}
	else if (m_strAmountPresentUnit == "엔") {
		m_cbUnit.SetCurSel(2);
		m_cbBalanceUnit.SetCurSel(2);
	}
	mysql_free_result(sql_result);

	// 참여자 트리
	int unpaidTotalCount = 0;	// 미정산 인원
	int unpaidAmount = 0;		// 미정산 금액
	for (int i = 0; i < indexCount; i++) {	// 차수 노드가 존재할 때까지
		query.Format(_T("SELECT * FROM participants WHERE content_seq = %d ORDER BY name ASC"), _ttoi(listContentSeq[i]));
		CStringA participantA(query);
		cstr = participantA;
		mysql_query(&Connect, cstr);
		sql_result = mysql_store_result(&Connect);

		int j = 1;
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {	// 참여자가 존재할 때 까지
			CString name, moneyToPay, item;
			name = sql_row[2];
			moneyToPay = sql_row[4];
			item = name + _T(", ") + moneyToPay + m_strAmountPresentUnit;	// <이름, 금액> 형식
			hChild[i][j] = m_treeControl.InsertItem(item, hChild[i][0]);
			m_treeControl.Expand(hChild[i][j], TVE_EXPAND);

			CString isPaid;
			isPaid = sql_row[3];
			if (_ttoi(isPaid) == 1) {	// 정산일 때 확인란 체크 표시
				m_treeControl.SetCheck(hChild[i][j], true);
			}
			else {		// 미정산 상태일 때 정산 현황 정보 업데이트
				unpaidTotalCount++;		
				unpaidAmount += _ttoi(moneyToPay);
			}
			j++;
		}
		mysql_free_result(sql_result);
	}
	m_nBalance = unpaidAmount;			// 미정산 총 금액
	m_nUnsettledNum = unpaidTotalCount;	// 미정산 총 인원

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CViewSettlementDlg::OnSelchangedTreeControl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_hSelectNode = pNMTreeView->itemNew.hItem;

	// 선택한 노드의 부모 노드
	HTREEITEM hParentItem = m_treeControl.GetParentItem(m_hSelectNode);
	if (hParentItem == m_hRoot)	{	// 차수 노드를 선택했을 때
									// 해당 차수 참여자들 리스트, 해당 차수 금액이 보여진다.
		// 차수
		CString degree = m_treeControl.GetItemText(m_hSelectNode);
		AfxExtractSubString(m_strDegree, degree, 0, _T('차'));
		m_strDegree += _T("차");
		
		// 참여자 이름
		// 첫 번째 자식 항목(노드) 가져오기
		HTREEITEM hChildItem = m_treeControl.GetChildItem(m_hSelectNode);
		CString nameList;	// 해당 차수에 참여한 사람들 리스트

		// 자식 항목이 유효한지 확인 후 사용
		while (hChildItem != NULL) {
			// 자식 항목의 데이터 처리
			CString childText;
			AfxExtractSubString(childText, m_treeControl.GetItemText(hChildItem), 0, _T(','));	// 이름만 추출
			nameList += childText + _T(", ");

			// 다음 자식 항목(노드) 가져오기
			hChildItem = m_treeControl.GetNextItem(hChildItem, TVGN_NEXT);
		}
		int len = nameList.GetLength() - 2;	// 마지막 ", " 삭제
		m_strName = nameList.Left(len);

		// 금액
		sql_row = GetContentByDegree(m_strDegree);	// 해당 차수의 content 결과 가져오기
		CString strAmount;
		strAmount = sql_row[3];
		m_nAmount = _ttoi(strAmount);
	}
	else if (hParentItem !=  NULL) {	// 참여자 노드를 선택했을 때
										// 해당 참여자가 참여한 차수와 총 지불 금액을 보여준다.
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
					totalAmount += _ttoi(amount);	// 총 지불 금액에 추가
					isAttend = TRUE;	// 해당 차수에 참여
				}
				hParticipantsItem = m_treeControl.GetNextItem(hParticipantsItem, TVGN_NEXT);	// 다음 참여자 노드
			}
			if (isAttend == TRUE) {
				CString degree;
				AfxExtractSubString(degree, m_treeControl.GetItemText(hChildItem), 0, _T('차'));
				m_strDegree += degree + _T(", ");	// 참여한 차수에 추가
			}
			isAttend = FALSE;
			hChildItem = m_treeControl.GetNextItem(hChildItem, TVGN_NEXT);	// 다음 차수 노드
		}
		m_strDegree = m_strDegree.Mid(0, m_strDegree.GetLength() - 2);	// 마지막에 ", " 삭제
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
	while (hChildItem != NULL) {	// 차수가 존재할 때까지
		CString degree, content_seq;
		AfxExtractSubString(degree, m_treeControl.GetItemText(hChildItem), 0, _T('차'));
		degree += _T("차");
		sql_row = GetContentByDegree(degree);
		content_seq = sql_row[0];

		hParticipantsItem = m_treeControl.GetChildItem(hChildItem);
		while (hParticipantsItem != NULL) {		// 각 차수의 참여자가 존재할 때까지
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


void CViewSettlementDlg::OnSelchangeComboBalanceUnit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 현재 선택된 셀의 인덱스를 가져온다.
	int selectedIndex = m_cbBalanceUnit.GetCurSel();

	// 선택된 셀의 텍스트를 가져온다.
	m_cbBalanceUnit.GetLBText(selectedIndex, m_strBalanceChangeUnit);

	// CChangeUnitDlg에 선택된 셀의 텍스트를 전달하기 위해 인스턴스를 생성한다.
	CChangeUnitDlg* pdlgUnit = new CChangeUnitDlg;
	pdlgUnit->SetViewDlg(this);
	pdlgUnit->SetAmountOrBalance(0);	// m_cbUnit인지, m_cbBalanceUnit인지 구분하기 위하여
	if (pdlgUnit->DoModal() == IDOK) {
		m_nBalance = pdlgUnit->m_nChangeValue;
		m_strBalancePresentUnit = pdlgUnit->m_strChangeUnit;

		UpdateData(FALSE);
	}
}


void CViewSettlementDlg::OnSelchangeComboUnit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 현재 선택된 셀의 인덱스를 가져온다.
	int selectedIndex = m_cbUnit.GetCurSel();

	// 선택된 셀의 텍스트를 가져온다.
	m_cbBalanceUnit.GetLBText(selectedIndex, m_strAmountChangeUnit);

	// CChangeUnitDlg에 선택된 셀의 텍스트를 전달하기 위해 인스턴스를 생성한다.
	CChangeUnitDlg* pdlgUnit = new CChangeUnitDlg;
	pdlgUnit->SetViewDlg(this);
	pdlgUnit->SetAmountOrBalance(1);	// m_cbUnit인지, m_cbBalanceUnit인지 구분하기 위하여
	if (pdlgUnit->DoModal() == IDOK) {
		m_nAmount = pdlgUnit->m_nChangeValue;
		m_strAmountPresentUnit = pdlgUnit->m_strChangeUnit;

		UpdateData(FALSE);
	}

}


void CViewSettlementDlg::SetSettlementIndex(int index)
{
	// TODO: 여기에 구현 코드 추가.
	m_nIndex = index;
}


void CViewSettlementDlg::SetStrDate(CString date)
{
	// TODO: 여기에 구현 코드 추가.
	m_strDate = date;
}
