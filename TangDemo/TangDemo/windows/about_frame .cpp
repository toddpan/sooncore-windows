#include "StdAfx.h"
#include "about_frame.hpp"
#include <ShellAPI.h>

DUI_BEGIN_MESSAGE_MAP(CAboutFrame,CWindowWithShadow)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_LINK,OnLink)
DUI_END_MESSAGE_MAP()

CAboutFrame::CAboutFrame( void )
{

}

DuiLib::CDuiString CAboutFrame::GetSkinFile()
{
	return _T("about.xml");
}

DuiLib::CDuiString CAboutFrame::GetSkinFolder()
{
	return _T("UIRes\\");
}

void CAboutFrame::OnClick( TNotifyUI& msg )
{
	if (msg.pSender->GetName() == L"btnClose" || msg.pSender->GetName() == L"btnYes")
	{
		Close();
	}
}

void CAboutFrame::Show(HWND hwndParent)
{
	Create(hwndParent, L"About", UI_WNDSTYLE_DIALOG, 0);
	CenterWindow();
	ShowModal();
}

void CAboutFrame::OnLink( TNotifyUI& msg )
{
	if (msg.pSender->GetName() == L"lnkFeedback")
	{
		ShellExecute(NULL, L"open", L"http://www.raydownload.com", NULL, NULL, SW_NORMAL);
	}
}
