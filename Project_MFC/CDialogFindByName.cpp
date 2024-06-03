
#include "pch.h"
#include "Project_MFC.h"
#include "afxdialogex.h"
#include "CDialogFindByName.h"
#include "Resource.h"
#include <string>


template <class T, class Key> const T* find(const T* p_begin, const T* p_end, const Key& k) {

	if (p_begin == nullptr || p_end == nullptr || p_begin > p_end) {
		return nullptr;
	}

	for (const T* p = p_begin; p != p_end; ++p) {
		if (*p == k) {
			return p;
		}
	}

	return nullptr;
};


const MY_POINT* findMyPoint(MY_POINT* p_begin, MY_POINT* p_end, const CString& name) {
	const MY_POINT* p = find(p_begin, p_end, name); // uzycie funkcji template
	return p;
}

IMPLEMENT_DYNAMIC(CDialogFindByName, CDialogEx)


CDialogFindByName::CDialogFindByName(CProjectMFCDoc* pDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FIND_BY_NAME, pParent)
	, m_name(_T(""))
	, m_item_found(_T(""))
{
	pDocum = pDoc;
	pDat = pDocum->pDat;

	if (!pDat->size()) {
		m_item_found = _T("There is no item defined! Enter some data using 'Input Data'");
	}
}

CDialogFindByName::~CDialogFindByName()
{
}

void CDialogFindByName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME_TO_FIND, m_name);
	DDX_Text(pDX, IDC_DATA_FIND_BY_NAME_OUTPUT, m_item_found);
}

BEGIN_MESSAGE_MAP(CDialogFindByName, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CDialogFindByName::OnBnClickedButtonFind)
	ON_BN_CLICKED(IDOK, &CDialogFindByName::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_NAME_TO_FIND, &CDialogFindByName::OnEnChangeEditNameToFind)
END_MESSAGE_MAP()


BOOL CDialogFindByName::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT(pDat);
	int no_item = pDat->size();

	if (no_item == 0) {
		DisableBtnFind();
		DisableEditNameToFind();
	}
	else {
		EnableBtnFind();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDialogFindByName::OnBnClickedButtonFind()
{
		UpdateData(TRUE); // Ensure data is updated from the UI

		if (m_name.IsEmpty()) {
			m_item_found = _T("Please enter a name to search for.");
			UpdateData(FALSE);
			return;
		}

		DisableBtnFind(); // Disable the Find button while processing

		if (pDat->size()) {
			auto& first_item = (*pDat)[0];
			auto& last_item = (*pDat)[pDat->size() - 1];
	
			const MY_POINT* p = findMyPoint(&first_item, &last_item + 1, m_name); // uzycie funkcji template

			if (p != nullptr) {
				m_item_found.Format(_T("Found item: x: %g, y: %g, color: RGB(%d, %d, %d), name: %s, numb: %d"), p->x, p->y, GetRValue(p->color), GetGValue(p->color), GetBValue(p->color), p->name, p->numb);
			}
			else {
				m_item_found = _T("Item not found.");
			}
		}

		UpdateData(FALSE); // Update the UI with the results
}


void CDialogFindByName::OnBnClickedOk()
{
	// TODO: Dodaj tutaj swój kod procedury obs³ugi powiadamiania kontrolki
	CDialogEx::OnOK();
}


void CDialogFindByName::OnEnChangeEditNameToFind()
{
	UpdateData(TRUE);
	if (!m_name.IsEmpty()) {
		EnableBtnFind();
	}
	else {
		DisableBtnFind();
	}
}


void CDialogFindByName::DisableEditNameToFind()
{
	CWnd* pDlgItem = GetDlgItem(IDC_EDIT_NAME_TO_FIND);
	if (pDlgItem != nullptr)
	{
		pDlgItem->EnableWindow(FALSE);
	}
}

void CDialogFindByName::DisableBtnFind()
{
	CWnd* pButton = GetDlgItem(IDC_BUTTON_FIND);
	if (pButton != nullptr)
	{
		pButton->EnableWindow(FALSE);
	}
}

void CDialogFindByName::EnableBtnFind()
{
	CWnd* pButton = GetDlgItem(IDC_BUTTON_FIND);
	if (pButton != nullptr)
	{
		pButton->EnableWindow(TRUE);
	}
}

