#include "stdafx.h"
#include "WindowWithShadow.hpp"

#define BORDER_SIZE_LEFT 5
#define BORDER_SIZE_TOP 5
#define BORDER_SIZE_RIGHT 5
#define BORDER_SIZE_BOTTOM 7

#define TIMER_SHOWEFFECT_ID 1
#define TIMER_SHOWEFFECT_ELAPSE 50

DUI_BEGIN_MESSAGE_MAP(CWindowWithShadow,WindowImplBase)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_WINDOWINIT,OnShadowWinInit)
DUI_END_MESSAGE_MAP()
CWindowWithShadow::CWindowWithShadow(void)
{
	//_InitVars();
}

CWindowWithShadow::~CWindowWithShadow(void)
{
}

void CWindowWithShadow::OnShadowWinInit( TNotifyUI& msg )
{
	m_wndShadow.Create(GetHWND(), L"border", WS_POPUP | WS_VISIBLE, 0);

	RECT rcMain;
	GetWindowRect(GetHWND(), &rcMain);
	int iWidth = rcMain.right - rcMain.left;
	int iHeight = rcMain.bottom - rcMain.top;
	MoveWindow(m_wndShadow.GetHWND(), rcMain.left - BORDER_SIZE_LEFT, rcMain.top - BORDER_SIZE_TOP
		, iWidth + BORDER_SIZE_LEFT + BORDER_SIZE_RIGHT, iHeight + BORDER_SIZE_TOP + BORDER_SIZE_BOTTOM, TRUE);
	::InvalidateRect(m_wndShadow.GetHWND(), NULL, FALSE);
	//m_wndShadow.ShowWindow(true);
}

LRESULT CWindowWithShadow::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if (uMsg == WM_SIZE || uMsg == WM_MOVE)
	{
		RECT rcMain;
		GetWindowRect(GetHWND(), &rcMain);
		int iWidth = rcMain.right - rcMain.left;
		int iHeight = rcMain.bottom - rcMain.top;
		MoveWindow(m_wndShadow.GetHWND(), rcMain.left - BORDER_SIZE_LEFT, rcMain.top - BORDER_SIZE_TOP
			, iWidth + BORDER_SIZE_LEFT + BORDER_SIZE_RIGHT, iHeight + BORDER_SIZE_TOP + BORDER_SIZE_BOTTOM, TRUE);
		::InvalidateRect(m_wndShadow.GetHWND(), NULL, FALSE);
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CWindowWithShadow::OnDestroy( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	if (m_wndShadow.GetHWND())
		m_wndShadow.Close();
	return __super::OnDestroy(uMsg, wParam, lParam, bHandled);
}

void CWindowWithShadow::ShowWindow( bool bShow /*= true*/, bool bTakeFocus /*= true*/ )
{
	WindowImplBase::ShowWindow(bShow, bTakeFocus);
	if (m_wndShadow.GetHWND())
		m_wndShadow.ShowWindow(bShow, false);
}

//void CWindowWithShadow::ShowByEffect()
//{
//	m_lAlpha = 0;
//	SetWindowLong(*this,GWL_EXSTYLE, GetWindowLong(*this, GWL_EXSTYLE) | WS_EX_LAYERED);
//	SetLayeredWindowAttributes(*this, 0, 0, LWA_ALPHA);
//
//	SetTimer(*this, TIMER_SHOWEFFECT_ID, TIMER_SHOWEFFECT_ELAPSE, NULL);
//}

//////////////////////////////////////////////////////////////////////////
CWindowWithShadow::CWndShadow::CWndShadow()
{
	_InitVars();
}

CWindowWithShadow::CWndShadow::~CWndShadow()
{
	
	
}

LRESULT CWindowWithShadow::CWndShadow::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if (uMsg == WM_CREATE)
	{
		//MoveWindow(GetHWND(), 0, 0, 100, 100, TRUE);
		//DoPaint(NULL);
	}
	else if (uMsg == WM_DESTROY)
	{
		if (m_hmpOffscreen)
		{
			::SelectObject(m_hDcOffScreen, m_hbmpOffscreenOld);
			::DeleteObject(m_hmpOffscreen);
			::DeleteDC(m_hDcOffScreen);
		}
		if (m_hDcPaint)
			ReleaseDC(GetHWND(), m_hDcPaint);
	}
	else if (uMsg == WM_ERASEBKGND)
	{
		return 1;
	}
	else if (uMsg == WM_PAINT)
	{
		//COMMON_TRACE(L"pait");
		RECT rcPaint;
		if (GetRectNeedUpdate(&rcPaint) && IsRectEmpty(&rcPaint) == FALSE)
		{
			DoPaint(&rcPaint);
		}
		//return ;
	}
	return __super::HandleMessage(uMsg,wParam,lParam);
}

void CWindowWithShadow::CWndShadow::DoPaint( RECT* prcPaint )
{
	//COMMON_TRACE(L"Paint--------");
	if ((GetWindowLong(GetHWND(), GWL_EXSTYLE) & WS_EX_LAYERED) == 0)
		SetWindowLong(GetHWND(), GWL_EXSTYLE, GetWindowLong(GetHWND(), GWL_EXSTYLE) | WS_EX_LAYERED);

	if (prcPaint == NULL)
		GetWindowRect(GetHWND(), prcPaint);
	if (::IsRectEmpty(prcPaint))
		return;
	int iWidth = prcPaint->right - prcPaint->left;
	int iHeight = prcPaint->bottom - prcPaint->top;
	if (m_hmpOffscreen != NULL)
	{
		::SelectObject(m_hDcOffScreen, m_hbmpOffscreenOld);
		::DeleteObject(m_hmpOffscreen);
		::DeleteDC(m_hDcOffScreen);
	}
	if (m_hDcPaint ==  NULL)
		m_hDcPaint = GetDC(GetHWND());

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = iWidth;
	bmi.bmiHeader.biHeight = iHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = iWidth * iHeight * (bmi.bmiHeader.biBitCount/8);
	m_hmpOffscreen = ::CreateDIBSection(m_hDcPaint, &bmi, DIB_RGB_COLORS, (LPVOID*) &m_pDibOffScreen, NULL, 0);

	m_hDcOffScreen = CreateCompatibleDC(m_hDcPaint);
	m_hbmpOffscreenOld = (HBITMAP)SelectObject(m_hDcOffScreen, m_hmpOffscreen);

	RECT rcClient;
	GetClientRect(GetHWND(), &rcClient);

	if (m_PaintManager.GetResourcePath().IsEmpty())
	{	// 允许更灵活的资源路径定义
		CDuiString strResourcePath=m_PaintManager.GetInstancePath();
		m_PaintManager.SetResourcePath(strResourcePath.GetData());
	}
	DuiLib::CRenderEngine::DrawImageString(m_hDcOffScreen, &m_PaintManager,  rcClient, *prcPaint, L"file='bk_shadow.png' corner='10,10,10,10'");
	//FillRect(m_hDcOffScreen, &rcClient, (HBRUSH)GetStockObject(BLACK_BRUSH));

	POINT ptDest = {prcPaint->left, prcPaint->top};
	::ClientToScreen(GetHWND(), &ptDest);
	POINT ptSrc = {0, 0};
	SIZE sz = {rcClient.right-rcClient.left, rcClient.bottom-rcClient.top};

	BLENDFUNCTION bfUpdate;
	bfUpdate.BlendOp = AC_SRC_OVER;
	bfUpdate.AlphaFormat = AC_SRC_ALPHA;
	bfUpdate.BlendFlags = 0;
	bfUpdate.SourceConstantAlpha = 255;
	BOOL bRet = UpdateLayeredWindow(GetHWND(), m_hDcPaint, NULL, &sz, m_hDcOffScreen, &ptSrc, 0, &bfUpdate,ULW_ALPHA);

// 	HDC hDCScreen = GetDC(NULL);
// 	BitBlt(hDCScreen, 100,100, 100, 100, m_hDcOffScreen, 0, 0, SRCCOPY);
// 	ReleaseDC(NULL, hDCScreen);
}
bool CWindowWithShadow::CWndShadow::GetRectNeedUpdate(RECT* pRc )
{
	if( !::GetUpdateRect(GetHWND(), pRc, FALSE))
		return false;
	
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(GetHWND(), MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	RECT rcMonitor = oMonitor.rcMonitor;
	RECT rcWindow;
	GetWindowRect(GetHWND(), &rcWindow);

	//计算显示在屏幕外的区域
	pRc->left = rcWindow.left < rcMonitor.left ? 0 : pRc->left;
	pRc->right = rcWindow.right > rcMonitor.right ? (rcWindow.right - rcWindow.left) : pRc->right;
	pRc->top = rcWindow.top < rcMonitor.top ? 0 : pRc->top;
	pRc->bottom = rcWindow.bottom > rcMonitor.bottom ? (rcWindow.bottom - rcWindow.top) : pRc->bottom;

	return true;
}

