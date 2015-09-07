#include "StdAfx.h"
#include "desktop_share.hpp"
#include <ShellAPI.h>

//DUI_BEGIN_MESSAGE_MAP(CDesktopShare,CWindowWithShadow)
//	//DUI_ON_MSGTYPE(DUI_MSGTYPE_LINK,OnLink)
//	//DUI_ON_MSGTYPE(DUI_MSGTYPE_MOUSEENTER,OnLink)
//DUI_END_MESSAGE_MAP()

CDesktopShare::CDesktopShare( void )
	:m_bIsAutoHide(false)
{

}

DuiLib::CDuiString CDesktopShare::GetSkinFile()
{
	return _T("desktop_share.xml");
}

DuiLib::CDuiString CDesktopShare::GetSkinFolder()
{
	return _T("UIRes\\");
}

LRESULT CDesktopShare::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	if (uMsg == WM_MOUSELEAVE)
	{
		if (m_bIsAutoHide)
		{
			//TopCenterWindow(true);
			::SetWindowPos(m_hWnd, NULL, m_nPosLeft,m_nPosTop /*yTop*/, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
		}
	}
	else if (uMsg == WM_MOUSEHOVER)
	{
		if (m_bIsAutoHide)
		{
			//TopCenterWindow(true);
			::SetWindowPos(m_hWnd, NULL, m_nPosLeft,0 /*yTop*/, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
		}
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void CDesktopShare::TopCenterWindow()
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT((GetWindowStyle(m_hWnd)&WS_CHILD)==0);
	RECT rcDlg = { 0 };
	::GetWindowRect(m_hWnd, &rcDlg);
	RECT rcArea = { 0 };
	RECT rcCenter = { 0 };
	HWND hWnd=*this;
	//HWND hWndParent = ::GetParent(m_hWnd);
	HWND hWndCenter = ::GetWindowOwner(m_hWnd);
	if (hWndCenter!=NULL)
		hWnd=hWndCenter;

	// 处理多显示器模式下屏幕居中
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST), &oMonitor);
	rcArea = oMonitor.rcWork;

	if( hWndCenter == NULL )
		rcCenter = rcArea;
	else
		::GetWindowRect(hWndCenter, &rcCenter);

	int DlgWidth = rcDlg.right - rcDlg.left;
	int DlgHeight = rcDlg.bottom - rcDlg.top;

	// Find dialog's upper left based on rcCenter
	int xLeft = (rcCenter.left + rcCenter.right) / 2 - DlgWidth / 2;
	//int yTop = (rcCenter.top + rcCenter.bottom) / 2 - DlgHeight / 2;
	int yTop = 0;

	// The dialog is outside the screen, move it inside
	if( xLeft < rcArea.left ) xLeft = rcArea.left;
	else if( xLeft + DlgWidth > rcArea.right ) xLeft = rcArea.right - DlgWidth;
	//if( yTop < rcArea.top ) yTop = rcArea.top;
	//else if( yTop + DlgHeight > rcArea.bottom ) yTop = rcArea.bottom - DlgHeight;

	m_nPosLeft = xLeft;
	m_nPosTop  = HIDE_WINDOW_LEAVE_EDGE - DlgHeight;
	::SetWindowPos(m_hWnd, NULL, xLeft,0 /*yTop*/, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void CDesktopShare::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, _T("windowinit")) == 0)
	{
		//OnPrepare(msg);
	}
	else if (_tcsicmp(msg.sType,DUI_MSGTYPE_CLICK ) == 0)
	{
		if (_tcsicmp(msg.pSender->GetName(), _T("btnExitShare")) == 0)
		{
			Close();
		}
		else if (_tcsicmp(msg.pSender->GetName(), _T("btnStable")) == 0 )
		{
			m_bIsAutoHide = !m_bIsAutoHide;
			CControlUI* pStableControl = m_PaintManager.FindControl(_T("btnStable"));
			if (pStableControl != NULL)
			{
				CButtonUI* pStableButton = dynamic_cast<CButtonUI*>(pStableControl);
				if(m_bIsAutoHide)
				{
					pStableButton->SetNormalImage(_T("file='gc_tools2.png' source='280,0,320,40'"));
					pStableButton->SetHotImage(_T("file='gc_tools2.png' source='280,40,320,80'"));
					pStableButton->SetToolTip(_T("钉住工具栏"));
				}
				else
				{
					pStableButton->SetNormalImage(_T("file='gc_tools2.png' source='320,0,360,40'"));
					pStableButton->SetHotImage(_T("file='gc_tools2.png' source='320,40,360,80'"));
					pStableButton->SetToolTip(_T("取消钉住"));
				}
			}
		}
		else if (_tcsicmp(msg.pSender->GetName(), _T("btnPeg")) == 0 )
		{
			m_bIsAutoHide = false;
		}
	}
	//else if (_tcsicmp(msg.sType, _T("timer")) == 0)
	//{
	//	return OnTimer(msg);
	//}
	//else if (_tcsicmp(msg.sType, DUI_MSGTYPE_MOUSEENTER) == 0)
	//{
	//	if (m_bIsAutoHide)
	//	{
	//		TopCenterWindow();
	//	}
	//}
	//else if (_tcsicmp(msg.sType, DUI_MSGTYPE_MOUSELEAVE) == 0)
	//{
	//	if (m_bIsAutoHide)
	//	{
	//		TopCenterWindow(!m_bIsAutoHide);
	//	}
	//}
}