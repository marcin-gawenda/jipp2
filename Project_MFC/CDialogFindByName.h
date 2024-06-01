#pragma once
#include "afxdialogex.h"
#include "Project_MFCDoc.h"
#include "MyData.h"

class CDialogFindByName : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogFindByName)

public:
	MY_DATA* pDat;
	CProjectMFCDoc* pDocum;
	CString m_name;
	CString m_item_found;

	CDialogFindByName(CProjectMFCDoc* pDoc, CWnd* pParent = nullptr);   // konstruktor standardowy
	virtual ~CDialogFindByName();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FIND_BY_NAME};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // obs³uga DDX/DDV
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFind();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditNameToFind();
	afx_msg void DisableEditNameToFind();
	afx_msg void DisableBtnFind();
	afx_msg void EnableBtnFind();
};