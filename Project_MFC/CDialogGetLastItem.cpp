// CDialogGetLastItem.cpp: plik implementacji
//

#include "pch.h"
#include "Project_MFC.h"
#include "afxdialogex.h"
#include "CDialogGetLastItem.h"
#include "Resource.h"


// Okno dialogowe CDialogGetLastItem

IMPLEMENT_DYNAMIC(CDialogGetLastItem, CDialogEx)

CDialogGetLastItem::CDialogGetLastItem(CProjectMFCDoc* pDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GET_LAST_ITEM, pParent)
	, last_item_output(_T(""))
{
	pDocum = pDoc;
	pDat = pDocum->pDat;

	if (pDat->size()) {
		auto& last_item = (*pDat)[pDat->size() - 1];
		last_item_output.Format("Element %d - x: %g; y: %g", pDat->size(), last_item.x, last_item.y);
	}
	else {
		last_item_output.SetString("No points found!");
	}
	
}

CDialogGetLastItem::~CDialogGetLastItem()
{
}

void CDialogGetLastItem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATA_TEXT, last_item_output);
}

BEGIN_MESSAGE_MAP(CDialogGetLastItem, CDialogEx)
END_MESSAGE_MAP()

// Procedury obsługi komunikatów CDialogGetLastItem
BOOL CDialogGetLastItem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
