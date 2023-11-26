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
}


BEGIN_MESSAGE_MAP(CViewSettlementDlg, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_CONTROL, &CViewSettlementDlg::OnSelchangedTreeControl)
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
	HTREEITEM hChild[100];
	CString listContentSeq[100];
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		CString degree, place, node;
		degree = sql_row[2];
		place = sql_row[5];
		listContentSeq[indexCount] = sql_row[0];

		node = degree;
		if (!place.IsEmpty()) {
			node += _T(" (") + place + _T(")");
		}
		hChild[indexCount++] = m_treeControl.InsertItem(node, m_hRoot);
	}
	mysql_free_result(sql_result);

	// 참여자 트리
	for (int i = 0; i < indexCount; i++) {
		query.Format(_T("SELECT * FROM participants WHERE content_seq = %d ORDER BY name ASC"), _ttoi(listContentSeq[i]));
		CStringA participantA(query);
		cstr = participantA;
		mysql_query(&Connect, cstr);
		sql_result = mysql_store_result(&Connect);
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			CString name;
			name = sql_row[2];
			m_treeControl.InsertItem(name, hChild[i]);
			m_treeControl.Expand(hChild[i], TVE_EXPAND);
		}
		mysql_free_result(sql_result);
	}

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CViewSettlementDlg::OnSelchangedTreeControl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_hSelectNode = pNMTreeView->itemNew.hItem;
	*pResult = 0;
}
