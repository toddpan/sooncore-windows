#pragma once
#include "WindowWithShadow.hpp"

using namespace DuiLib;


class CAboutFrame : public CWindowWithShadow
{
public:
	CAboutFrame(void);

	void Show(HWND hwndParent);
protected:
	LPCTSTR GetWindowClassName() const override
	{
		return _T("CAboutFrame");
	}
	CDuiString GetSkinFile() override;
	CDuiString GetSkinFolder() override;
	void OnClick(TNotifyUI& msg) override;

	DUI_DECLARE_MESSAGE_MAP()
	virtual void OnLink(TNotifyUI& msg);
};