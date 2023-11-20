// CChangeUnitDlg.cpp: 구현 파일
//

#include "pch.h"
#include "DutchPayHelper.h"
#include "CChangeUnitDlg.h"
#include "afxdialogex.h"


// CChangeUnitDlg 대화 상자

IMPLEMENT_DYNAMIC(CChangeUnitDlg, CDialogEx)

CChangeUnitDlg::CChangeUnitDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CHANGE_UNIT, pParent)
{

}

CChangeUnitDlg::~CChangeUnitDlg()
{
}

void CChangeUnitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChangeUnitDlg, CDialogEx)
END_MESSAGE_MAP()


// CChangeUnitDlg 메시지 처리기
