#pragma once


// CViewSettlementDlg 대화 상자

class CViewSettlementDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CViewSettlementDlg)

public:
	CViewSettlementDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CViewSettlementDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strDate;
	virtual BOOL OnInitDialog();
	//CDutchPayHelperDlg* m_pDlg;
	//void SetViewParentDlg(CDutchPayHelperDlg* dlg);
};
