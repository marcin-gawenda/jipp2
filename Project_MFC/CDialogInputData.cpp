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
	, m_X(0)
	, m_Y(0)	
	, m_Color(RGB(0, 255, 0)) // Initializing the color member variable
{
	pDocum = pDoc;
	memset((void*)&lvi, 0, sizeof(LVITEMA));
	pDat = pDocum->pDat;	
	m_ColorBox.SetColor(m_Color);	
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
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
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

	CString strx, stry, strColor, strName;

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

		strColor = Utils::ColorRefToCString(pt.color);
		Len += strlen(strColor);
		
		strName = Utils::CharArrayToCString(pt.name);
		Len += strlen(strName);

		lvi.pszText = " ";
		lvi.cchTextMax = (int)Len;
		ret = m_ListCtrl.InsertItem(&lvi);
		
		m_ListCtrl.SetItemText(lvi.iItem, 0, strx);
		m_ListCtrl.SetItemText(lvi.iItem, 1, stry);
		m_ListCtrl.SetItemText(lvi.iItem, 2, strColor);
		m_ListCtrl.SetItemText(lvi.iItem, 3, strName);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogInputData::ModifyData()
{
	char st[512]{0};
	BOOL ret(0);
	MY_POINT tmp;

	UpdateData(TRUE);
	const int no_it(m_ListCtrl.GetItemCount());

	if (pDat)
		delete pDat;
	pDocum->pDat = pDat = new MY_DATA(no_it);

	for (int nItem = 0; nItem < no_it; ++nItem)
	{
		CString strX, strY, strColor, strName;
		GetListCtrlItemText(nItem, 0, strX);
		GetListCtrlItemText(nItem, 1, strY);
		GetListCtrlItemText(nItem, 2, strColor);
		GetListCtrlItemText(nItem, 3, strName);

		tmp.x = atof(strX);
		tmp.y = atof(strY);
		tmp.color = Utils::CStringToColorRef(strColor);
		tmp.name = Utils::CStringToCharArray(strName);
		tmp.numb = nItem;

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

	CString strx, stry, strColor, strName;

	UpdateData(TRUE);

	strx.Format("%le", m_X);
	size_t Len = strlen(strx);

	stry.Format("%le", m_Y);
	Len += strlen(stry);

	strColor = Utils::ColorRefToCString(m_ColorBox.GetColor());
	Len += strlen(strColor);

	strName = m_name;
	if (strName == "" || strName == "P-") {
		// Convert int to CString
		CString strNumber;
		strNumber.Format(_T("%d"), nItem);
		strName = "P-" + strNumber;
	}
	Len += strlen(strName);
		
	lvi.iItem = nItem;
	lvi.pszText = " ";
	lvi.cchTextMax = (int)Len;
	
	ret = m_ListCtrl.InsertItem(&lvi);
	m_ListCtrl.SetItemText(lvi.iItem, 0, strx);
	m_ListCtrl.SetItemText(lvi.iItem, 1, stry);
	m_ListCtrl.SetItemText(lvi.iItem, 2, strColor);
	m_ListCtrl.SetItemText(lvi.iItem, 3, strName);

	UpdateData(FALSE);

	ASSERT_VALID(pDocum);
	pDocum->SetModifiedFlag();
	pDocum->UpdateAllViews(NULL);

	//SelectLastItemInListCtrl();
}


void CDialogInputData::OnClickedButtonMod()
{

	// TODO: Add your control notification handler code here
	int ret = -1;
	int no_item = m_ListCtrl.GetItemCount();

	if (m_SelItem < 0 || m_SelItem >= no_item)
		return;

	CString strx, stry, strColor, strName;

	int nItem = m_SelItem;

	UpdateData(TRUE);

	strx.Format("%le", m_X);
	size_t Len = strlen(strx);

	stry.Format("%le", m_Y);
	Len += strlen(stry);

	strColor = Utils::ColorRefToCString(m_ColorBox.GetColor());
	Len += strlen(strColor);
	
	strName = m_name;
	Len += strlen(strName);

	lvi.iItem = nItem;
	m_ListCtrl.SetItemText(lvi.iItem, 0, strx);
	m_ListCtrl.SetItemText(lvi.iItem, 1, stry);
	m_ListCtrl.SetItemText(lvi.iItem, 2, strColor);
	m_ListCtrl.SetItemText(lvi.iItem, 3, strName);

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

	// Ensure that the new state includes selection
	if ((pNMLV->uChanged & LVIF_STATE) &&
		(pNMLV->uNewState & LVIS_SELECTED))
	{

		UpdateData(TRUE);

		int nItem = m_SelItem = pNMLV->iItem;
		int no_item = m_ListCtrl.GetItemCount();

		if (nItem < 0 || nItem >= no_item)
			return;

		// Retrieve text from the selected item's columns
		CString strX, strY, strColor, strName;
		GetListCtrlItemText(nItem, 0, strX);
		GetListCtrlItemText(nItem, 1, strY);
		GetListCtrlItemText(nItem, 2, strColor);
		GetListCtrlItemText(nItem, 3, strName);

		// Update dialog controls with the selected item's data
		m_X = _tstof(strX);
		m_Y = _tstof(strY);

		// set color according to selected item
		m_ColorBox.SetColor(Utils::CStringToColorRef(strColor));
		m_ColorBox.Invalidate();
		
		m_name = strName;

		// Update dialog controls
		UpdateData(FALSE);
	}
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

void CDialogInputData::GetListCtrlItemText(int nItem, int nCol, CString& outText)
{
	TCHAR szText[256]{0};  // Buffer to store the text
	m_ListCtrl.GetItemText(nItem, nCol, szText, sizeof(szText) / sizeof(TCHAR));
	outText = szText;
}


void CDialogInputData::IncreaseValues()
{
	m_X += 1;
	m_Y += 1;
	m_name = "inc";
}

void CDialogInputData::ResetValues()
{
	m_X = 0;
	m_Y = 0;
	m_ColorBox.SetColor(RGB(0,255,0));
	m_ColorBox.Invalidate();
	m_name = "";
}

void CDialogInputData::SelectLastItemInListCtrl()
{

	// Ensure the list control has items
	int itemCount = m_ListCtrl.GetItemCount();

	if (itemCount == 0)
		return;

	// Get the index of the last item
	int lastIndex = itemCount - 1;

	// Ensure the last item is visible
	m_ListCtrl.EnsureVisible(lastIndex, FALSE);

	// Set the state of the last item to selected and focused
	m_ListCtrl.SetItemState(lastIndex, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	m_ListCtrl.SetSelectionMark(lastIndex); // Set the selection mark to the second item
}

