#pragma once
#include "afxdialogex.h"
#include "Project_MFCDoc.h"
#include "MyData.h"


// Okno dialogowe CDialogGetLastItem

class CDialogGetLastItem : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogGetLastItem)

public:
	MY_DATA* pDat;
	CProjectMFCDoc* pDocum;
	CString last_item_output;

	CDialogGetLastItem(CProjectMFCDoc* pDoc, CWnd* pParent = nullptr);   // konstruktor standardowy
	virtual ~CDialogGetLastItem();

// Dane okna dialogowego
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GET_LAST_ITEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // obsługa DDX/DDV
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
