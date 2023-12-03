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
	afx_msg void OnLbnSelchangeListCalculate();
	CListBox m_listFriend;
	afx_msg void OnLbnSelchangeListFriend();
	int m_nAmount;
	afx_msg void OnEnChangeEditAmount();
	afx_msg void OnEnChangeEditDate();
	CString m_strDate;
	CComboBox m_cbUnit;
	afx_msg void OnCbnSelchangeComboUnit();
	CString m_strPlace;
	afx_msg void OnEnChangeEditPlace();
	afx_msg void OnBnClickedButtonCalculateAdd();
	CString m_strFriend;
	afx_msg void OnEnChangeEditFriend();
	afx_msg void OnEnChangeEditCalculateName();
	CString m_strCalculateName;
	CString m_strAccountNum;
	CString m_strGeneralAffairs;
	CString m_strMemo;
	afx_msg void OnEnChangeEditGeneralAffairs();
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnItemchangedListCalculate(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_listCalculate;
	afx_msg void OnClickedButtonCalculateDelete();
	int m_nSelectedItem;
	CString ChangeListToString();
	void UpdateFriendListBox(CString str);
	afx_msg void OnClickedButtonFriendAdd();
	afx_msg void OnClickedButtonEditFriends();
	afx_msg void OnClickedButtonFriendDelete();
	CDutchPayHelperDlg* m_pDlg;
	void SetParentDlg(CDutchPayHelperDlg* dlg);
	int m_nCountCal;
	CListCtrl* GetListCtrlPointer();
	afx_msg void OnBnClickedOk();
	void InsertParticipants(int amount, CString nameList);
};
