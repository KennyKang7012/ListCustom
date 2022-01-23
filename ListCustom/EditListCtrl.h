#pragma once
#include <afxcmn.h>

/////////////////////////////////////////////////////////////////////////////
//CItemEdit window

class CItemEdit : public CEdit
{
	// Construction
public:
	CItemEdit();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CItemEdit)
	//}}AFX_VIRTUAL

	// Implementation
public:
	int m_iXPos;
	virtual ~CItemEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CItemEdit)
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEditListCtrl window
class CEditListCtrl : public CListCtrl
{
	// Construction
public:
	CEditListCtrl();

	// Attributes
public:

	// Operations
public:

	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CEditListCtrl)
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditListCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
private:
	int m_iSubItem;            // �l�����ѧO��
	int m_iItem;               // �D���Хܲ�
	BOOL m_bHighLight;         // �O�_���G����
	BOOL m_bFocus;             // �O�_ø�s�J�I��
	CItemEdit m_edtItemEdit;   // �Ω�l����EditLabel��ƪ�^��CEdit*���w
};


/////////////////////////////////////////////////////////////////////////////

