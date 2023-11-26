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
{

}

CViewSettlementDlg::~CViewSettlementDlg()
{
}

void CViewSettlementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CViewSettlementDlg, CDialogEx)
END_MESSAGE_MAP()


// CViewSettlementDlg 메시지 처리기


/*void CViewSettlementDlg::SetViewParentDlg(CDutchPayHelperDlg* dlg)
{
	// TODO: 여기에 구현 코드 추가.
	m_pDlg = dlg;
}*/


BOOL CViewSettlementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	/*CString index = m_pDlg->m_listDutchPay.GetItemText(m_pDlg->m_nSelectedPay, 0);
	m_strDate = m_pDlg->m_listDutchPay.GetItemText(m_pDlg->m_nSelectedPay, 1);
	m_strDate.Format(L"%Y-%m-%d");
	CFont g_editFont;
	g_editFont.CreatePointFont(150, TEXT("굴림"));
	GetDlgItem(IDC_EDIT_DATE)->SetFont(&g_editFont);

	UpdateData(FALSE);
	*/
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
