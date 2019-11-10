#pragma once
#include "OpenGLProjectView.h"

class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, bool bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPropertiesWnd : public CDockablePane
{
	// 생성입니다.
public:
	CPropertiesWnd() noexcept;

	void AdjustLayout();

	// 특성입니다.
public:
	void SetVSDotNetLook(bool bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}
private:
	const LONG height = 30;
	const int nOPT_LTG = 8;
	const CString checkBoxLabel[8] = { _T("light0_position"), _T("light0_ambient"), _T("light0_diffuse"), _T("light0_specular"), _T("mat_ambient"), _T("mat_diffuse"), _T("mat_specular"), _T("mat_shiness") };
protected:
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CPropertiesToolBar m_wndToolBar;
	CMFCPropertyGridCtrl m_wndPropList;

	CButton* m_testBtn;
	CButton* checkBox;
	COpenGLProjectView* cOpenGLProjectView;

	// 구현입니다.
public:
	virtual ~CPropertiesWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	afx_msg void OnUpdateButton(CCmdUI* pCmdUI);
	afx_msg void OnBtnClick();
	afx_msg void OnChecked(UINT nID);

	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();

	int m_nComboHeight;
public:
	afx_msg void OnDestroy();
};
