#pragma once
#include "WindowWithShadow.hpp"

using namespace DuiLib;

const int HIDE_WINDOW_LEAVE_EDGE = 5;

class CDesktopShare : public CWindowWithShadow //
{
public:
	CDesktopShare(void);

	//void Show(HWND hwndParent);
	void TopCenterWindow( );
protected:
	LPCTSTR GetWindowClassName() const override
	{
		return _T("CDesktopShare");
	}
	CDuiString GetSkinFile() override;
	CDuiString GetSkinFolder() override;
	//void OnClick(TNotifyUI& msg) override;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

	void Notify(TNotifyUI& msg);
private:
	bool		m_bIsAutoHide;
	int			m_nPosLeft;
	int			m_nPosTop;
	//DUI_DECLARE_MESSAGE_MAP()
	//virtual void OnLink(TNotifyUI& msg);
};