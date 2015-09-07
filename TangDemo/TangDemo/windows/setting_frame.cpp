#include "stdafx.h"
#include <windows.h>
#if !defined(UNDER_CE)
#include <shellapi.h>
#endif

#include "setting_frame.hpp"
#include "main_frame.hpp"
#include "about_frame.hpp"

//control name define
const TCHAR* const kItemVideoCheckName = _T("");
const TCHAR* const kItemOnlineServiceName =_T("");
const TCHAR* const kItemSettingName = _T("");
const TCHAR* const kItemQuestionName = _T("");
const TCHAR* const kItemAboutName = _T("");


CSettingWindow::CSettingWindow(RECT rcParentWindow,HWND hwOwner,UINT msgId)
 : parent_window_rect_(rcParentWindow),
 m_hwndOwner(hwOwner),
 m_uMsgId(msgId)
{
	Create(NULL, _T("settingWnd"), WS_POPUP, WS_EX_TOOLWINDOW, 0, 0);
	ShowWindow(true);
}

bool CSettingWindow::Show(RECT parentWndRect,HWND hOwner , UINT msgID )
{
	//m_hwndOwner = hOwner;
	//m_uMsgId = msgID;

	//if (GetHWND() != NULL)
	//	return false;

	/*Create(NULL, L"CSettingWindow", WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP, WS_EX_TOOLWINDOW | WS_EX_PALETTEWINDOW);
	ShowWindow(true);*/

	Create(NULL, _T("settingWnd"), WS_POPUP, WS_EX_TOOLWINDOW, 0, 0);
	ShowWindow(true);

	return true;
}

LPCTSTR CSettingWindow::GetWindowClassName() const 
{ 
	return _T("CSettingWindow");
}

void CSettingWindow::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

void CSettingWindow::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		
	}
	else if (_tcsicmp(msg.sType, DUI_MSGTYPE_ITEMCLICK) == 0)
	{
		if (_tcsicmp(msg.pSender->GetName(), _T("videocheckItem")) == 0)
		{
			::PostMessage(m_hwndOwner, m_uMsgId, MENU_ITEM_ID::ITEM_VIDEO_CHECK, 0);
		}
		else if (_tcsicmp(msg.pSender->GetName(), _T("onlineseviceItem")) == 0)
		{
			::PostMessage(m_hwndOwner, m_uMsgId, MENU_ITEM_ID::ITEM_ONLINE_SERVIE, 0);
		}
		else if (_tcsicmp(msg.pSender->GetName(), _T("settingItem")) == 0)
		{
			::PostMessage(m_hwndOwner, m_uMsgId, MENU_ITEM_ID::ITEM_SETTING, 0);
		}
		else if (_tcsicmp(msg.pSender->GetName(), _T("questionItem")) == 0)
		{
			::PostMessage(m_hwndOwner, m_uMsgId, MENU_ITEM_ID::ITEM_QUESTION, 0);
		}
		else if (_tcsicmp(msg.pSender->GetName(), _T("aboutItem")) == 0)
		{
			::PostMessage(m_hwndOwner, m_uMsgId, MENU_ITEM_ID::ITEM_ABOUT, 0);
		}
	}
	else if (_tcsicmp(msg.sType, _T("valuechanged")) == 0)
	{
	/*	CTabLayoutUI* pTabControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(kTabControlName));
		if (pTabControl != NULL)
		{
			if (pTabControl->GetCurSel() == 0)
			{
				CSliderUI* AdjustColorSliderR = static_cast<CSliderUI*>(m_PaintManager.FindControl(kAdjustColorSliderRControlName));
				CSliderUI* AdjustColorSliderG = static_cast<CSliderUI*>(m_PaintManager.FindControl(kAdjustColorSliderGControlName));
				CSliderUI* AdjustColorSliderB = static_cast<CSliderUI*>(m_PaintManager.FindControl(kAdjustColorSliderBControlName));
				if ((AdjustColorSliderR != NULL) && (AdjustColorSliderG != NULL) && (AdjustColorSliderB != NULL))
				{
					if ((_tcsicmp(msg.pSender->GetName(), kAdjustColorSliderRControlName) == 0) ||
						(_tcsicmp(msg.pSender->GetName(), kAdjustColorSliderGControlName) == 0) ||
						(_tcsicmp(msg.pSender->GetName(), kAdjustColorSliderBControlName) == 0))
					{
						BYTE red = AdjustColorSliderR->GetValue();
						BYTE green = AdjustColorSliderG->GetValue();
						BYTE blue = AdjustColorSliderB->GetValue();
						COLORREF crColor = RGB(red, green, blue);
						TCHAR szBuf[MAX_PATH] = {0};
#if defined(UNDER_CE)
						_stprintf(szBuf, _T("FF%02X%02X%02X"), GetRValue(crColor), GetGValue(crColor), GetBValue(crColor));
#else
						_stprintf_s(szBuf, MAX_PATH - 1, _T("FF%02X%02X%02X"), GetRValue(crColor), GetGValue(crColor), GetBValue(crColor));
#endif
						LPTSTR pstr = NULL;
						DWORD dwColor = _tcstoul(szBuf, &pstr, 16);
						main_frame_->SetBkColor(dwColor);
					}
				}
			}
			else if (pTabControl->GetCurSel() == 1)
			{}
		}*/
	}
	else if (_tcsicmp(msg.sType, _T("selectchanged")) == 0)
	{
		//CTabLayoutUI* pTabControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(kTabControlName));
		//if (_tcsicmp(msg.pSender->GetName(), kAdjustColorControlName) == 0)
		//{
		//	if (pTabControl && pTabControl->GetCurSel() != 0)
		//	{
		//		pTabControl->SelectItem(0);
		//	}
		//}
		//else if (_tcsicmp(msg.pSender->GetName(), kAdjustBkControlName) == 0)
		//{
		//	if (pTabControl && pTabControl->GetCurSel() != 1)
		//	{
		//		pTabControl->SelectItem(1);
		//	}
		//}
	}
}

void CSettingWindow::InitWindow()
{
	SIZE size = m_PaintManager.GetInitSize();
	MoveWindow(m_hWnd, parent_window_rect_.right - size.cx - 1, parent_window_rect_.top, size.cx, size.cy, FALSE);
}

CDuiString CSettingWindow::GetSkinFile()
{
	return _T("setting.xml");
}

CDuiString CSettingWindow::GetSkinFolder()
{
	return /*CDuiString(CPaintManagerUI::GetInstancePath()) +*/ _T("UIRes\\");
}

LRESULT CSettingWindow::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	Close();
	return 0;
}


