// CChangeUnitDlg.cpp: 구현 파일
//

#include "pch.h"
#include "DutchPayHelper.h"
#include "CChangeUnitDlg.h"
#include "afxdialogex.h"
#include "CAddSettlementDlg.h"
#include "CViewSettlementDlg.h"


// CChangeUnitDlg 대화 상자

IMPLEMENT_DYNAMIC(CChangeUnitDlg, CDialogEx)

CChangeUnitDlg::CChangeUnitDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CHANGE_UNIT, pParent)
	, m_strChangeUnit(_T(""))
	, m_nChangeValue(0)
	, m_dExchangeRate(0)
	, m_strPresentUnit(_T(""))
	, m_nPresentValue(0)
	, m_strUnit(_T(""))
{

}

CChangeUnitDlg::~CChangeUnitDlg()
{
}

void CChangeUnitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CHANGE_UNIT, m_strChangeUnit);
	DDX_Text(pDX, IDC_EDIT_CHANGE_VALUE, m_nChangeValue);
	DDX_Text(pDX, IDC_EDIT_EXCHANGE_RATE, m_dExchangeRate);
	DDX_Text(pDX, IDC_EDIT_PRESENT_UNIT, m_strPresentUnit);
	DDX_Text(pDX, IDC_EDIT_PRESENT_VALUE, m_nPresentValue);
	DDX_Text(pDX, IDC_EDIT_UNIT, m_strUnit);
}


BEGIN_MESSAGE_MAP(CChangeUnitDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CChangeUnitDlg::OnClickedButtonChange)
END_MESSAGE_MAP()


// CChangeUnitDlg 메시지 처리기


void CChangeUnitDlg::SetAddDlg(CAddSettlementDlg* dlg)
{
	// TODO: 여기에 구현 코드 추가.
	m_addDlg = dlg;
}


BOOL CChangeUnitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	if (m_addDlg != NULL) {		// Add에서 생성했을 떄
		m_strPresentUnit = m_addDlg->m_strPresnetUnit;
		m_strChangeUnit = m_addDlg->m_strUnit;
		m_nPresentValue = m_addDlg->m_nAmount;
	}
	else if (m_viewDlg != NULL && m_isAmount == 1) {	// View에서 생성했을 때, 전체 금액 조회일 때
		m_strPresentUnit = m_viewDlg->m_strAmountPresentUnit;
		m_strChangeUnit = m_viewDlg->m_strAmountChangeUnit;
		m_nPresentValue = m_viewDlg->m_nAmount;
	}
	else if (m_viewDlg != NULL && m_isAmount == 0) {	// View에서 생성했을 때, 잔돈 조회일 때
		m_strPresentUnit = m_viewDlg->m_strBalancePresentUnit;
		m_strChangeUnit = m_viewDlg->m_strBalanceChangeUnit;
		m_nPresentValue = m_viewDlg->m_nBalance;
	}
	m_dExchangeRate = 0;

	// 단위 초기화
	CString strPresentValue;
	strPresentValue.Format(_T("%d"), m_nPresentValue);
	m_strUnit = strPresentValue + m_strPresentUnit + _T(" -> ? ") + m_strChangeUnit;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CChangeUnitDlg::OnClickedButtonChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 우선순위 - 1달러 > 100 엔 > 1000원 기준으로
	UpdateData(TRUE);

	if (m_dExchangeRate)
	{
		if (m_strPresentUnit == "원" && m_strChangeUnit == "달러")
			m_nChangeValue = m_nPresentValue / m_dExchangeRate;
		else if (m_strPresentUnit == "원" && m_strChangeUnit == "엔")
			m_nChangeValue = m_nPresentValue / m_dExchangeRate * 100;
		else if (m_strPresentUnit == "달러" && m_strChangeUnit == "원")
			m_nChangeValue = m_nPresentValue * m_dExchangeRate;
		else if (m_strPresentUnit == "달러" && m_strChangeUnit == "엔")
			m_nChangeValue = m_nPresentValue * m_dExchangeRate;
		else if (m_strPresentUnit == "엔" && m_strChangeUnit == "원")
			m_nChangeValue = m_nPresentValue * m_dExchangeRate / 100;
		else if (m_strPresentUnit == "엔" && m_strChangeUnit == "달러")
			m_nChangeValue = m_nPresentValue * m_dExchangeRate;

		// 단위 업데이트
		CString strPresentValue, strChangeValue;
		strPresentValue.Format(_T("%d"), m_nPresentValue);
		strChangeValue.Format(_T("%d"), m_nChangeValue);
		m_strUnit = strPresentValue + m_strPresentUnit + _T(" -> ") + strChangeValue + m_strChangeUnit;

		UpdateData(FALSE);
	}
	else {
		MessageBox(_T("환율을 입력해주세요."));
	}
}


void CChangeUnitDlg::SetViewDlg(CViewSettlementDlg* dlg)
{
	// TODO: 여기에 구현 코드 추가.
	m_viewDlg = dlg;
}


void CChangeUnitDlg::SetAmountOrBalance(bool isAmount)
{
	// TODO: 여기에 구현 코드 추가.
	m_isAmount = isAmount;
}
