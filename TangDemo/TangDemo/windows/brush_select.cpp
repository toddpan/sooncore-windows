#include "stdafx.h"
#include <windows.h>
#if !defined(UNDER_CE)
#include <shellapi.h>
#endif

#include "brush_select.hpp"

//const TCHAR* const kAdjustColorControlName = _T("adjcolor");
//const TCHAR* const kAdjustBkControlName = _T("adjbk");
//
//const TCHAR* const kAdjustColorSliderRControlName = _T("AdjustColorSliderR");
//const TCHAR* const kAdjustColorSliderGControlName = _T("AdjustColorSliderG");
//const TCHAR* const kAdjustColorSliderBControlName = _T("AdjustColorSliderB");
//
//const TCHAR* const kHColorLayoutControlName = _T("HColorLayout");
//const TCHAR* const kHBkLayoutControlName = _T("HBkLayout");
//
//const TCHAR* const kTabControlName = _T("tabs");

CBrushSelWindow::CBrushSelWindow(RECT rcParentWindow)
: parent_window_rect_(rcParentWindow)
{
	Create(NULL, _T("brush"), WS_POPUP, WS_EX_TOOLWINDOW, 0, 0);
	ShowWindow(true);
}

LPCTSTR CBrushSelWindow::GetWindowClassName() const 
{ 
	return _T("CBrushSelWindow");
}

void CBrushSelWindow::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

void CBrushSelWindow::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		if (_tcsicmp(msg.pSender->GetName(), _T("brush_black")) == 0)
		{
			//TODO:
		}
	}
	else if (_tcsicmp(msg.sType, _T("valuechanged")) == 0)
	{
		
	}
	else if (_tcsicmp(msg.sType, _T("selectchanged")) == 0)
	{

	}
}

void CBrushSelWindow::InitWindow()
{
	SIZE size = m_PaintManager.GetInitSize();
	MoveWindow(m_hWnd, parent_window_rect_.left, parent_window_rect_.top, size.cx, size.cy, FALSE);
}

CDuiString CBrushSelWindow::GetSkinFile()
{
	return _T("brush_select.xml");
}

CDuiString CBrushSelWindow::GetSkinFolder()
{
	//return CDuiString(CPaintManagerUI::GetInstancePath()) + _T("skin\\");
	return _T("UIRes\\");
}

LRESULT CBrushSelWindow::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	Close();
	return 0;
}
