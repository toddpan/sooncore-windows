#ifndef COLORSKIN_HPP
#define COLORSKIN_HPP

#include "WindowWithShadow.hpp"

//class MainFrame;
using namespace DuiLib;

class CSettingWindow : public CWindowWithShadow 
{
public:
	CSettingWindow(RECT rcParentWindow,HWND hwOwn = NULL,UINT msgId=0);

	bool Show(RECT parentWndRect,HWND hOwner = NULL, UINT msgID = 0);
	LPCTSTR GetWindowClassName() const;

	virtual void OnFinalMessage(HWND hWnd);

	void Notify(TNotifyUI& msg);
	
	virtual void InitWindow();

	virtual CDuiString GetSkinFile();

	virtual CDuiString GetSkinFolder();

	virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
	RECT parent_window_rect_;

	//MainFrame* main_frame_;
	HWND m_hwndOwner;
	UINT m_uMsgId;
};

#endif // COLORSKIN_HPP