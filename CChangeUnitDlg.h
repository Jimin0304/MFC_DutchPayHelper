#pragma once

class CAddSettlementDlg;
class CViewSettlementDlg;
// CChangeUnitDlg 대화 상자

class CChangeUnitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeUnitDlg)

public:
	CChangeUnitDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CChangeUnitDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHANGE_UNIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditUnit();
	CAddSettlementDlg* m_addDlg;
	void SetAddDlg(CAddSettlementDlg* dlg);
	CString m_strChangeUnit;
	long m_nChangeValue;
	double m_dExchangeRate;
	CString m_strPresentUnit;
	long m_nPresentValue;
	CString m_strUnit;
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedButtonChange();
	CViewSettlementDlg* m_viewDlg;
	void SetViewDlg(CViewSettlementDlg* dlg);
	void SetAmountOrBalance(bool isAmount);
	bool m_isAmount;
};
