#pragma once
using namespace DuiLib;

class CWindowWithShadow : public WindowImplBase
{
public:
	CWindowWithShadow(void);
	~CWindowWithShadow(void);

	//void ShowByEffect();
protected:
// 	LPCTSTR GetWindowClassName() const override
// 	{
// 		return _T("SUPDuiWindow");
// 	}
// 	CDuiString GetSkinFile() override;
// 	CDuiString GetSkinFolder() override;
 	//void OnClick(TNotifyUI& msg) override;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	void ShowWindow(bool bShow = true, bool bTakeFocus = true);

	DUI_DECLARE_MESSAGE_MAP()
	void OnShadowWinInit(TNotifyUI& msg);

private:
	void _InitVars()
	{
		m_lAlpha = 0;
	}

	long m_lAlpha;

	class CWndShadow : public CWindowWnd
	{
	public:
		CWndShadow();
		~CWndShadow();
		
	protected:
		LPCTSTR GetWindowClassName() const override
		{
			return _T("SUPDuiWindow");
		}
		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

	private:
		void _InitVars()
		{
			m_hmpOffscreen = NULL;
			m_hbmpOffscreenOld = NULL;
			m_pDibOffScreen = NULL;
			m_hDcPaint = NULL;
			m_hDcOffScreen = NULL;
		}
		HBITMAP	m_hmpOffscreen;
		HBITMAP m_hbmpOffscreenOld;
		LPDWORD	m_pDibOffScreen;
		HDC		m_hDcPaint;
		HDC		m_hDcOffScreen;

		CPaintManagerUI m_PaintManager;

		void DoPaint(RECT* prcPaint);
		bool GetRectNeedUpdate(RECT* pRc );

	};
	CWndShadow	m_wndShadow;
};

