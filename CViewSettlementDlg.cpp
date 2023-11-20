// CViewSettlementDlg.cpp: 구현 파일
//

#include "pch.h"
#include "DutchPayHelper.h"
#include "CViewSettlementDlg.h"
#include "afxdialogex.h"


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
