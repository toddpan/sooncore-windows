#include "stdafx.h"
#include <windows.h>
#include <shellapi.h>

#include "desktop_share_viewer.hpp"
#include "brush_select.hpp"
#include "webEventHanderEx.hpp"

const TCHAR* kTopHiddenLayoutName = _T("topBorder");
const TCHAR* kFullScreenButtonName = _T("fullScreenBtn");
const TCHAR* kPinFrameButtonName = _T("btnPin");


DUI_BEGIN_MESSAGE_MAP(CDeskShareViewer,CWindowWithShadow)
	//DUI_ON_MSGTYPE(DUI_MSGTYPE_WINDOWINIT,OnWinInit)
	DUI_ON_MSGTYPE(L"mousehover",OnMouseHoverEvent)
DUI_END_MESSAGE_MAP()

CDynamicHorizontalLayoutUI::CDynamicHorizontalLayoutUI()
{
}

void CDynamicHorizontalLayoutUI::DoEvent(TEventUI& event)
{
	CLabelUI *pTitle = dynamic_cast<CLabelUI*>(CDeskShareViewer::FindChild(this, L"dynamicLayout"));
	if (event.Type == UIEVENT_BUTTONUP)
	{
		GetManager()->SendNotify(this, L"mousehover", 0, 0, true);
	}
	else if(event.Type == UIEVENT_MOUSEENTER)
	{
		pTitle->SetTextColor(0xFFffffff);
	}
	else if(event.Type == UIEVENT_MOUSELEAVE)
	{
		pTitle->SetTextColor(0xFF555555);
	}
	__super::DoEvent(event);
}


CDeskShareViewer::CDeskShareViewer()
	:m_bTopFrameIsHidden(false)
{}

CDeskShareViewer::~CDeskShareViewer()
{}

LPCTSTR CDeskShareViewer::GetWindowClassName() const
{
	return _T("CDeskShareViewer");
}

CControlUI* CDeskShareViewer::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass,_T("HorizontalLayout")) ==0 ) //HorizontalLayout
		return new CDynamicHorizontalLayoutUI;
	return __super::CreateControl(pstrClass);
}

void CDeskShareViewer::OnMouseHoverEvent(TNotifyUI& msg)
{
	MessageBox(m_hWnd,_T("mouse hover"),_T("caption"),0);
}

CControlUI* CDeskShareViewer::FindChild( CContainerUI* pContainer, LPCTSTR strName )
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

void CDeskShareViewer::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);	
	delete this;
}

CDuiString CDeskShareViewer::GetSkinFile()
{
	return _T("desktop_share_viewer.xml");
}

CDuiString CDeskShareViewer::GetSkinFolder()
{
	//return CDuiString(CPaintManagerUI::GetInstancePath()) + _T("skin\\");
	return _T("UIRes\\");
}

LRESULT CDeskShareViewer::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CDeskShareViewer::OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CDeskShareViewer::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if defined(WIN32) && !defined(UNDER_CE)
	BOOL bZoomed = ::IsZoomed(m_hWnd);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (::IsZoomed(m_hWnd) != bZoomed)
	{
		if (!bZoomed)
		{
			//CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(kMaxButtonControlName));
			//if( pControl ) pControl->SetVisible(false);
			//pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(kRestoreButtonControlName));
			//if( pControl ) pControl->SetVisible(true);
			//CActiveXUI* pActiveXUI = static_cast<CActiveXUI*>(m_PaintManager.FindControl(_T("htmlView")));
			//if( pActiveXUI ) 
			//{
			//	CDuiRect rcWindow;
			//	GetWindowRect(m_hWnd, &rcWindow);
			//	rcWindow.top += 80;
			//	LONG height = rcWindow.bottom - rcWindow.top;
			//	LONG width = rcWindow.right - rcWindow.left;

			//	int nControlWidth = pActiveXUI->GetFixedWidth();//pActiveXUI->GetWidth();
			//	int nControlHeight = pActiveXUI->GetFixedHeight();//pActiveXUI->GetHeight();
			//	RECT posRect;
			//	posRect = rcWindow;
			//	posRect.top = (height - nControlHeight)/2;
			//	posRect.left= (width - nControlWidth) /2;
			//	posRect.bottom = posRect.top + nControlHeight;
			//	posRect.right = posRect.left + nControlWidth;
			//	//400,300
			//	pActiveXUI->SetPos(posRect);
			//}
		}
		else 
		{
			//CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(kMaxButtonControlName));
			//if( pControl ) pControl->SetVisible(true);
			//pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(kRestoreButtonControlName));
			//if( pControl ) pControl->SetVisible(false);
		}
	}
#else
	return __super::OnSysCommand(uMsg, wParam, lParam, bHandled);
#endif

	return 0;
}

LRESULT CDeskShareViewer::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//禁用双击全屏事件
	if (uMsg == WM_NCLBUTTONDBLCLK)
	{
		return 0;
	}

	//if (uMsg == WM_MOUSELEAVE)
	//{
	//	 
	//}
	//else if (uMsg == WM_MOUSEHOVER)
	//{
	//	POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };

	//}
	//else if(uMsg == WM_MOUSELEAVE)
	//{
	//	POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
	//}
	return __super::HandleMessage(uMsg, wParam, lParam);
}


static bool OnDynamicLayoutEvent(void* event)
{
	if( ((TEventUI*)event)->Type == UIEVENT_MOUSEHOVER ) 
	{
		CControlUI* pButton = ((TEventUI*)event)->pSender;
		if( pButton != NULL ) 
		{
			//CHorizontalLayoutUI* pListElement = (CHorizontalLayoutUI*)(pButton->GetTag());
			//if( pListElement != NULL ) pListElement->DoEvent(*(TEventUI*)event);
		}
	}
	else if( ((TEventUI*)event)->Type == UIEVENT_MOUSELEAVE ) 
	{
		CControlUI* pButton = ((TEventUI*)event)->pSender;
	}
	return true;
}
void CDeskShareViewer::InitWindow()
{
}

void CDeskShareViewer::OnPrepare(TNotifyUI& msg)
{
	CHorizontalLayoutUI* pDynamicLayout = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("dynamicLayout")));
	if (pDynamicLayout)
	{
		pDynamicLayout->OnEvent += MakeDelegate(&OnDynamicLayoutEvent);
	}

	CWebBrowserUI* pActiveXUI = static_cast<CWebBrowserUI*>(m_PaintManager.FindControl(_T("htmlView")));
	if( pActiveXUI ) 
	{
		CDuiRect rcWindow;
		GetWindowRect(m_hWnd, &rcWindow);
		rcWindow.top += 80;
		LONG height = rcWindow.bottom - rcWindow.top;
		LONG width = rcWindow.right - rcWindow.left;

		int nControlWidth = pActiveXUI->GetFixedWidth();//pActiveXUI->GetWidth();
		int nControlHeight = pActiveXUI->GetFixedHeight();//pActiveXUI->GetHeight();
		RECT posRect;
		posRect = rcWindow;
		posRect.top = (height - nControlHeight)/2;
		posRect.left= (width - nControlWidth) /2;
		posRect.bottom = posRect.top + nControlHeight;
		posRect.right = posRect.left + nControlWidth;

		pActiveXUI->SetVisible(true);
		pActiveXUI->SetPos(posRect);

		pActiveXUI->SetDelayCreate(true);
		CWebEventHandlerEx *pWebHandle = new CWebEventHandlerEx;
		pActiveXUI->SetWebBrowserEventHandler(pWebHandle);
		//这行代码，如果注释掉，就不会去掉边框，IE有bug，第二次加载网页才会让事件处理器有效
		pActiveXUI->Navigate2(L"about:blank");    

		std::wstring strHtml = CPaintManagerUI::GetInstancePath() + _T("UIRes\\html\\index.html");
		pActiveXUI->Navigate2(strHtml.c_str());
		//pActiveXUI->Navigate2(L"http://www.baidu.com/");
	}
}

void CDeskShareViewer::Notify(TNotifyUI& msg)
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
		else if (_tcsicmp(msg.pSender->GetName(), kFullScreenButtonName) == 0)
		{
			m_bTopFrameIsHidden = !m_bTopFrameIsHidden;
			CButtonUI* pFullScreeControl = static_cast<CButtonUI*>(m_PaintManager.FindControl(kFullScreenButtonName));
			CButtonUI* pPinBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(kPinFrameButtonName));
			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(kTopHiddenLayoutName));
			if (m_bTopFrameIsHidden)
			{
				if( pControl ) pControl->SetVisible(false);
				if( pFullScreeControl ) 
				{
					pFullScreeControl->SetNormalImage(_T("file='images\\gc_tools.png' source='240,0,280,40'"));
					pFullScreeControl->SetHotImage(_T("file='images\\gc_tools.png' source='240,40,280,80'"));
					pFullScreeControl->SetToolTip(_T("取消全屏"));
				}
				//显示钉住按钮
				if (pPinBtn)
				{
					pPinBtn->SetVisible(true);
					pPinBtn->SetNormalImage(_T("file='images\\gc_tools.png' source='280,0,320,40'"));
					pPinBtn->SetHotImage(_T("file='images\\gc_tools.png' source='280,40,320,80'"));
				}

				//::SetWindowPos(m_hWnd, NULL, 0,-30, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
			}
			else
			{
				if( pFullScreeControl ) 
				{
					pFullScreeControl->SetNormalImage(_T("file='images\\gc_tools.png' source='200,0,240,40'"));
					pFullScreeControl->SetHotImage(_T("file='images\\gc_tools.png' source='200,40,240,80'"));
					pFullScreeControl->SetToolTip(_T("全屏"));
				}
				if( pControl ) pControl->SetVisible(true);

				if (pPinBtn)
				{
					pPinBtn->SetVisible(false);
				}
			}
		}
		else if (_tcsicmp(msg.pSender->GetName(), kPinFrameButtonName) == 0)
		{
			//::SetWindowPos(m_hWnd, NULL, 0,-30, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
		}
		else if (_tcsicmp(msg.pSender->GetName(), _T("selectbrushBtn")) == 0)
		{
			CDuiRect rcWindow;
			GetWindowRect(m_hWnd, &rcWindow);
			rcWindow.top = rcWindow.top + msg.pSender->GetPos().bottom + 17;
			rcWindow.left = rcWindow.left + msg.pSender->GetPos().left - 30;
			new CBrushSelWindow(rcWindow);
		}
	}
	else if (_tcsicmp(msg.sType, _T("selectchanged")) == 0)
	{
		
	}
	else if (_tcsicmp(msg.sType, _T("itemselect")) == 0)
	{

	}
}

LRESULT CDeskShareViewer::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}