// CDialogInputData.cpp : implementation file
//

#include "pch.h"
#include "Project_MFC.h"
#include "CDialogInputData.h"
#include "afxdialogex.h"
#include "Utils.h"

// CDialogInputData dialog

IMPLEMENT_DYNAMIC(CDialogInputData, CDialogEx)

CDialogInputData::CDialogInputData(CProjectMFCDoc* pDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INPUT_DATA, pParent)
	, m_X(1)
	, m_Y(1)

{
	pDocum = pDoc;
	memset((void*)&lvi, 0, sizeof(LVITEMA));
	pDat = pDocum->pDat;	
	//m_color = RGB(255, 0, 0);
	m_name = "init";
}

CDialogInputData::~CDialogInputData()
{
	m_smallImageList.DeleteImageList();
}

void CDialogInputData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CTRL, m_ListCtrl);
	DDX_Text(pDX, IDC_EDIT_X, m_X);
	DDX_Text(pDX, IDC_EDIT_Y, m_Y);

	// Temporary CString for data exchange
	CString tempStr;
	tempStr = "M1";
	//tempStr = m_name;
	DDX_Text(pDX, IDC_EDIT_NAME, tempStr);
	

	//if (pDX->m_bSaveAndValidate) {
	//	// Copy data from the edit control to m_Y
	//	DDX_Text(pDX, IDC_EDIT_NAME, tempStr);
	//	// Ensure we do not overflow the buffer
	//	strncpy(m_name, tempStr, 255);
	//	m_name[255] = '\0'; // Null-terminate to be safe
	//} else {
	//	// Copy data from m_name to the edit control
	//	tempStr = m_name;
	//	DDX_Text(pDX, IDC_EDIT_NAME, tempStr);
	//}
}


BEGIN_MESSAGE_MAP(CDialogInputData, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDialogInputData::OnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MOD, &CDialogInputData::OnClickedButtonMod)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CDialogInputData::OnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_DEL_ALL, &CDialogInputData::OnClickedButtonDelAll)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST_CTRL, &CDialogInputData::OnItemchangingListCtrl)
	ON_BN_CLICKED(IDOK, &CDialogInputData::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CDialogInputData::OnClickedButtonColor)
END_MESSAGE_MAP()

BOOL CDialogInputData::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	VERIFY(m_ColorBox.SubclassDlgItem(IDC_STATIC_COLOR, this));

	CString strx, stry, color, name;

	lvi.mask = LVIF_TEXT;
	lvi.state = 0;
	lvi.stateMask = 0;
	lvi.iImage = 0;

	HICON hIcon = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_ProjectMFCTYPE));

	m_smallImageList.Create(16, 16, FALSE, 1, 0);
	m_smallImageList.Add(hIcon);
	m_ListCtrl.SetImageList(&m_smallImageList, LVSIL_SMALL);

	CRect rectListCtrl;
	memset(rectListCtrl, 0, sizeof(rectListCtrl));
	m_ListCtrl.GetClientRect(&rectListCtrl);

	int list_ctrl_width = rectListCtrl.right - rectListCtrl.left;
	int column_width = list_ctrl_width / 4;

	int ret;
	int nFormat = LVCFMT_LEFT;
	ret = m_ListCtrl.InsertColumn(0, "X", nFormat, column_width, 0);
	ret = m_ListCtrl.InsertColumn(1, "Y", nFormat, column_width, 1);
	ret = m_ListCtrl.InsertColumn(2, "Color", nFormat, column_width, 2);
	ret = m_ListCtrl.InsertColumn(3, "Name", nFormat, column_width, 3);

	ASSERT(pDat);
	int no_item = pDat->size();

	lvi.iSubItem = 0;
	m_ListCtrl.SetItemCount(no_item);

	for (int i = 0; i < no_item; i++)
	{
		MY_POINT pt = (*pDat)[i];
		lvi.iItem = i;
		strx.Format("%le", pt.x);
		size_t Len = strlen(strx);
		stry.Format("%le", pt.y);
		Len += strlen(stry);
		color.Format("%d", pt.color);
		Len += strlen(color);
		//name.Format("%d", pt.name);
		Len += strlen(name);

		lvi.pszText = " ";
		lvi.cchTextMax = (int)Len;
		ret = m_ListCtrl.InsertItem(&lvi);
		m_ListCtrl.SetItemText(lvi.iItem, 0, strx);
		m_ListCtrl.SetItemText(lvi.iItem, 1, stry);
		m_ListCtrl.SetItemText(lvi.iItem, 2, color);
		m_ListCtrl.SetItemText(lvi.iItem, 3, name);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogInputData::ModifyData()
{
	char st[512];
	BOOL ret(0);
	MY_POINT tmp;

	UpdateData(TRUE);
	const int no_it(m_ListCtrl.GetItemCount());

	if (pDat)
		delete pDat;
	pDocum->pDat = pDat = new MY_DATA(no_it);

	for (int nItem = 0; nItem < no_it; ++nItem)
	{
		BOOL ret = m_ListCtrl.GetItemText(nItem, 0, st, sizeof(st));
		tmp.x = atof(st);
		ret = m_ListCtrl.GetItemText(nItem, 1, st, sizeof(st));
		tmp.y = atof(st);
		ret = m_ListCtrl.GetItemText(nItem, 2, st, sizeof(st));
		tmp.color = atol(st);
		ret = m_ListCtrl.GetItemText(nItem, 3, st, sizeof(st));
		tmp.name = st;

		pDat->Push(tmp);
	}

	UpdateData(FALSE);

	ASSERT_VALID(pDocum);
	pDocum->SetModifiedFlag();
	pDocum->UpdateAllViews(NULL);
}

// CDialogInputData message handlers
void CDialogInputData::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

	ModifyData();
}

void CDialogInputData::OnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	int nItem = m_ListCtrl.GetItemCount();
	int ret = -1;
	MY_POINT tmp;
	CString strx, stry, name;

	UpdateData(TRUE);

	tmp.x = m_X;
	tmp.y = m_Y;
	strx.Format("%le", m_X);
	size_t Len = strlen(strx);
	stry.Format("%le", m_Y);
	Len += strlen(stry);

	char* strColor = Utils::ColorRefToCharArray(m_ColorBox.GetColor());
	//LPCTSTR strColor = Utils::ColorRefToString(m_ColorBox.GetColor()).c_str();
	//LPCTSTR strColor = Utils::ColorRefToString(m_ColorBox.GetColor());
	Len += strlen(strColor);

	tmp.name = m_name;
	//name.Format("%d", m_name);
	Len += strlen(m_name);

	lvi.iItem = nItem;
	lvi.pszText = " ";
	lvi.cchTextMax = (int)Len;
	ret = m_ListCtrl.InsertItem(&lvi);
	m_ListCtrl.SetItemText(lvi.iItem, 0, strx);
	m_ListCtrl.SetItemText(lvi.iItem, 1, stry);
	//m_ListCtrl.SetItemText(lvi.iItem, 2, strColor);
	m_ListCtrl.SetItemText(lvi.iItem, 2, "RGB(0, 0, 255)");
	//m_ListCtrl.SetTextBkColor(RGB(0, 0, 255));
	m_ListCtrl.SetItemText(lvi.iItem, 3, m_name);

	UpdateData(FALSE);

	ASSERT_VALID(pDocum);
	pDocum->SetModifiedFlag();
	pDocum->UpdateAllViews(NULL);
}


void CDialogInputData::OnClickedButtonMod()
{
	// TODO: Add your control notification handler code here
	int ret = -1;
	int no_item = m_ListCtrl.GetItemCount();

	if (m_SelItem < 0 || m_SelItem >= no_item)
		return;

	MY_POINT tmp;
	CString strx, stry, color, name;
	int nItem = m_SelItem;

	UpdateData(TRUE);

	tmp.x = m_X;
	tmp.y = m_Y;
	strx.Format("%le", m_X);
	size_t Len = strlen(strx);
	stry.Format("%le", m_Y);
	Len += strlen(stry);
	//color.Format("%d", m_color);
	Len += strlen(color);

	lvi.iItem = nItem;
	//lvi.pszText = " ";
	//lvi.cchTextMax = (int)Len;
	//ret = ListCtrl.InsertItem(&lvi);
	m_ListCtrl.SetItemText(lvi.iItem, 0, strx);
	m_ListCtrl.SetItemText(lvi.iItem, 1, stry);
	m_ListCtrl.SetItemText(lvi.iItem, 2, color);
	m_ListCtrl.SetItemText(lvi.iItem, 3, name);

	UpdateData(FALSE);

	ModifyData();
}


void CDialogInputData::OnClickedButtonDel()
{
	// TODO: Add your control notification handler code here
	int ret = -1;
	UpdateData(TRUE);

	int no_item = m_ListCtrl.GetItemCount();

	if (m_SelItem < 0 || m_SelItem >= no_item)
		return;

	m_ListCtrl.DeleteItem(m_SelItem);
	UpdateData(FALSE);

	ASSERT_VALID(pDocum);
	pDocum->SetModifiedFlag();
	pDocum->UpdateAllViews(NULL);
}

void CDialogInputData::OnClickedButtonDelAll()
{
	if (m_ListCtrl.GetItemCount() == 0) return;

	// TODO: Add your control notification handler code here
	int ret = -1;
	UpdateData(TRUE);	
	m_ListCtrl.DeleteAllItems();
	UpdateData(FALSE);

	ASSERT_VALID(pDocum);
	pDocum->SetModifiedFlag();
	pDocum->UpdateAllViews(NULL);
}

void CDialogInputData::OnItemchangingListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	UpdateData(TRUE);

	int nItem = m_SelItem = pNMLV->iItem;
	int no_item = m_ListCtrl.GetItemCount();

	if (m_SelItem < 0 || m_SelItem >= no_item)
		return;

	int ncol = 0;
	char st[512];
	BOOL ret = m_ListCtrl.GetItemText(nItem, ncol, st, sizeof(st));
	m_X = atof(st);

	ncol = 1;
	ret = m_ListCtrl.GetItemText(nItem, ncol, st, sizeof(st));
	m_Y = atof(st);
	
	ncol = 2;
	ret = m_ListCtrl.GetItemText(nItem, ncol, st, sizeof(st));
	//m_color = atol(st);

	//m_ColorBox.SetItem(nItem);
	COLORREF color = Utils::StringToColorRef(st);
	m_ColorBox.SetColor(color);
	m_ColorBox.Invalidate();

	ncol = 3;
	ret = m_ListCtrl.GetItemText(nItem, ncol, st, sizeof(st));

	if (strlen(st) == 0) {
		char str[100];         // Buffer to hold the final concatenated string
		const char* baseStr = "P-";

		// Convert integer to string
		char numStr[10];
		sprintf_s(numStr, sizeof(numStr), "%d", nItem);

		// Copy baseStr to str
		strcpy_s(str, sizeof(str), baseStr);

		// Concatenate the integer string to the base string
		strcat_s(str, sizeof(str), numStr);
		m_name = str;
	}
	else {
		m_name = st;
	}
	

	UpdateData(FALSE);
}

void CDialogInputData::OnClickedButtonColor()
{
	// TODO: Add your control notification handler code here

	CColorDialog dlg;

	if (dlg.DoModal())
	{
		m_ColorBox.SetColor(dlg.GetColor());
		m_ColorBox.Invalidate();
	}
}

///////////////////////////////////////////////////////////////////////////////
//   CColorBox

BEGIN_MESSAGE_MAP(CColorBox, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CColorBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages

	CRect rect;
	this->GetClientRect(&rect);

	CBrush newbrush;
	CBrush* oldbrush;
	newbrush.CreateSolidBrush(color);
	oldbrush = dc.SelectObject(&newbrush);

	dc.Rectangle(0, 0, (rect.right - rect.left), (rect.bottom - rect.top));

	dc.SelectObject(oldbrush);
	newbrush.DeleteObject();
}

void CColorBox::SetItem(int i)
{
	COLORREF tab[] = { RGB(0, 0, 0), RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255) };
	int ii = i % (sizeof(tab) / sizeof(tab[0]));
	color = tab[ii];
}









