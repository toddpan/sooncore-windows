#include "stdafx.h"
#include <windows.h>
#include <shellapi.h>

#include "video_frame.hpp"
#include "webEventHanderEx.hpp"

CVideoFrame::CVideoFrame()
{}

CVideoFrame::~CVideoFrame()
{}

LPCTSTR CVideoFrame::GetWindowClassName() const
{
	return _T("CVideoFrame");
}

CControlUI* CVideoFrame::CreateControl(LPCTSTR pstrClass)
{
	return __super::CreateControl(pstrClass);
}

CControlUI* CVideoFrame::FindChild( CContainerUI* pContainer, LPCTSTR strName )
{
	if (!pContainer)
		return NULL;

	if (_tcsicmp(strName, pContainer->GetName()) == 0)
	{
		return pContainer;
	}
	for (int i = 0; ; i ++)
	{
		CControlUI* pControl = pContainer->GetItemAt(i);
		if (pControl == NULL)
			return NULL;
		if ( _tcsicmp(strName ,pControl->GetName()) == 0)
		{
			return pControl;
		}
		CContainerUI* pContainerSub = dynamic_cast<CContainerUI*>(pControl);
		if (pContainerSub)
		{
			CControlUI* p = FindChild(pContainerSub, strName);
			if (p)
				return p;
		}
	}
	return NULL;
}

void CVideoFrame::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);	
	delete this;
}

CDuiString CVideoFrame::GetSkinFile()
{
	return _T("video_frame.xml");
}

CDuiString CVideoFrame::GetSkinFolder()
{
	//return CDuiString(CPaintManagerUI::GetInstancePath()) + _T("skin\\");
	return _T("UIRes\\");
}

LRESULT CVideoFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CVideoFrame::OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CVideoFrame::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if defined(WIN32) && !defined(UNDER_CE)
	BOOL bZoomed = ::IsZoomed(m_hWnd);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (::IsZoomed(m_hWnd) != bZoomed)
	{
		if (!bZoomed)
		{
		}
		else 
		{
		}
	}
#else
	return __super::OnSysCommand(uMsg, wParam, lParam, bHandled);
#endif

	return 0;
}

LRESULT CVideoFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//禁用双击全屏事件
	if (uMsg == WM_NCLBUTTONDBLCLK)
	{
		return 0;
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}


void CVideoFrame::InitWindow()
{
}

void CVideoFrame::OnPrepare(TNotifyUI& msg)
{
	CVerticalLayoutUI* pVideoLayoutUI = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("videoViewLayout")));

	if (pVideoLayoutUI)
	{
		CDuiRect rcWindow;
		GetWindowRect(m_hWnd, &rcWindow);
		rcWindow.top += 80;
		LONG height = rcWindow.bottom - rcWindow.top;
		LONG width = rcWindow.right - rcWindow.left;

		int nControlWidth = pVideoLayoutUI->GetFixedWidth();//pActiveXUI->GetWidth();
		int nControlHeight = pVideoLayoutUI->GetFixedHeight();//pActiveXUI->GetHeight();
		RECT posRect;
		posRect = rcWindow;
		posRect.top = (height - nControlHeight)/2;
		posRect.left= (width - nControlWidth) /2;
		posRect.bottom = posRect.top + nControlHeight;
		posRect.right = posRect.left + nControlWidth;

		pVideoLayoutUI->SetVisible(true);
		pVideoLayoutUI->SetPos(posRect);
	}
	
	CWebBrowserUI* pActiveXUI = static_cast<CWebBrowserUI*>(m_PaintManager.FindControl(_T("htmlView")));
	if( pActiveXUI ) 
	{
		pActiveXUI->SetVisible(true);

		pActiveXUI->SetDelayCreate(true);
		CWebEventHandlerEx *pWebHandle = new CWebEventHandlerEx;
		pActiveXUI->SetWebBrowserEventHandler(pWebHandle);
		//这行代码，如果注释掉，就不会去掉边框，IE有bug，第二次加载网页才会让事件处理器有效
		pActiveXUI->Navigate2(L"about:blank");    

		std::wstring strHtml = CPaintManagerUI::GetInstancePath() + _T("UIRes\\html\\video.html");
		pActiveXUI->Navigate2(strHtml.c_str());
		//pActiveXUI->Navigate2(L"http://www.baidu.com/");
	}
}

void CVideoFrame::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, _T("windowinit")) == 0)
	{
		OnPrepare(msg);
	}
	else if (_tcsicmp(msg.sType, _T("killfocus")) == 0)
	{
	}
	else if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		if (_tcsicmp(msg.pSender->GetName(), _T("closebtn")) == 0)
		{
			Close();
		}
		else if (_tcsicmp(msg.pSender->GetName(), _T("minbtn")) == 0)
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
	}
	else if (_tcsicmp(msg.sType, _T("selectchanged")) == 0)
	{
	}
	else if (_tcsicmp(msg.sType, _T("itemselect")) == 0)
	{
	}
}

LRESULT CVideoFrame::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}