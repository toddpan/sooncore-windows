#ifndef COLORSKIN_HPP
#define COLORSKIN_HPP

#include "WindowWithShadow.hpp"

using namespace DuiLib;

class CBrushSelWindow : public CWindowWithShadow
{
public:
	CBrushSelWindow( RECT rcParentWindow);

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
};

#endif // COLORSKIN_HPP