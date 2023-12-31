﻿#pragma once


// CViewSettlementDlg 대화 상자

class CDutchPayHelperDlg;

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
	CDutchPayHelperDlg* m_pDlg;
	void SetViewParentDlg(CDutchPayHelperDlg* dlg);
	CString m_strDate;
	virtual BOOL OnInitDialog();
	int m_nIndex;
	CString m_strCalcName;
	CString m_strGeneralAffairs;
	CString m_strMemo;
	CString m_strAccountNum;
	HTREEITEM m_hRoot;
	HTREEITEM m_hSelectNode;
	CTreeCtrl m_treeControl;
	afx_msg void OnSelchangedTreeControl(NMHDR* pNMHDR, LRESULT* pResult);
	BOOL m_bChecked;
	CComboBox m_cbUnit;
	CComboBox m_cbBalanceUnit;
	int m_nUnsettledNum;
	int m_nBalance;
	CString m_strDegree;
	CString m_strName;
	int m_nAmount;
	afx_msg void OnBnClickedOk();
	MYSQL_ROW GetContentByDegree(CString degree);
	CString m_strAmountPresentUnit;
	CString m_strAmountChangeUnit;
	afx_msg void OnSelchangeComboBalanceUnit();
	afx_msg void OnSelchangeComboUnit();
	CString m_strBalancePresentUnit;
	CString m_strBalanceChangeUnit;
	void SetSettlementIndex(int index);
	void SetStrDate(CString date);
};
