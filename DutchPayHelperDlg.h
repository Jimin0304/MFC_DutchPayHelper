﻿
// DutchPayHelperDlg.h: 헤더 파일
//

#pragma once


// CDutchPayHelperDlg 대화 상자
class CDutchPayHelperDlg : public CDialogEx
{
// 생성입니다.
public:
	CDutchPayHelperDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DUTCHPAYHELPER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnSelchangeMonthcalendar(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDatetimepicker(NMHDR* pNMHDR, LRESULT* pResult);
	COleDateTime m_timeDT;
	COleDateTime m_timeMC;
	CListCtrl m_listDutchPay;
	CMonthCalCtrl m_calendarMC;
	CDateTimeCtrl m_pickerDT;
	afx_msg void OnClickedButtonPickDate();
	void DisplayUnCompletedSettlements();
	void DisplaySelectedDateSettlements(CString selectedDate);
	afx_msg void OnClickedButtonDelete();
	int m_nSelectedPay;
	afx_msg void OnLvnItemchangedListDutchpay(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedButtonViewDetails();
};
