#pragma once


class CDutchPayHelperDlg;
// CAddSettlementDlg 대화 상자

class CAddSettlementDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddSettlementDlg)

public:
	CAddSettlementDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAddSettlementDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listFriend;
	int m_nAmount;
	CString m_strDate;
	CComboBox m_cbUnit;
	CString m_strPlace;
	afx_msg void OnBnClickedButtonCalculateAdd();
	CString m_strFriend;
	CString m_strCalculateName;
	CString m_strAccountNum;
	CString m_strGeneralAffairs;
	CString m_strMemo;
	CString m_strUnit;
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedListCalculate(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_listCalculate;
	afx_msg void OnClickedButtonCalculateDelete();
	int m_nSelectedItem;
	CString ChangeListToString();
	afx_msg void OnClickedButtonFriendAdd();
	afx_msg void OnClickedButtonEditFriends();
	afx_msg void OnClickedButtonFriendDelete();
	CDutchPayHelperDlg* m_pDlg;
	void SetParentDlg(CDutchPayHelperDlg* dlg);
	int m_nCountCal;
	afx_msg void OnBnClickedOk();
	void InsertParticipants(int amount, CString nameList);
	CComboBox m_cbSelectedUnit;
	CString m_strPresnetUnit;
};
