#include "stdafx.h"
#include <windows.h>
#if !defined(UNDER_CE)
#include <shellapi.h>
#endif

#include "main_frame.hpp"
#include "setting_frame.hpp"
#include "about_frame.hpp"
#include "desktop_share.hpp"
#include "desktop_share_viewer.hpp"

const TCHAR* const kCloseButtonControlName = _T("closebtn");
const TCHAR* const kMinButtonControlName = _T("minbtn");
const TCHAR* const kTabControlName = _T("tabs");
const TCHAR* const kFriendsListControlName = _T("participants");
const TCHAR* const kAddUserControlName = _T("adduserbtn");
const TCHAR* const kDesktopShareName = _T("deskSharebtn");

//const TCHAR* const kGroupsListControlName = _T("groups");
//const TCHAR* const kMicroBlogListControlName = _T("microblog");

//const TCHAR* const kHideLeftMainPannelControlName = _T("btnleft");
//const TCHAR* const kShowLeftMainPannelControlName = _T("btnright");
//const TCHAR* const kLeftMainPannelControlName = _T("LeftMainPanel");

//const TCHAR* const kSignatureTipsControlName = _T("signaturetip");
//const TCHAR* const kSignatureControlName = _T("signature");

//const TCHAR* const kSearchEditTipControlName = _T("search_tip");
//const TCHAR* const kSearchEditControlName = _T("search_edit");

//const TCHAR* const kChangeBkSkinControlName = _T("bkskinbtn");
const TCHAR* const kSettingListControlName = _T("settingbtn");
//const TCHAR* const kBackgroundControlName = _T("bg");

//const int kBackgroundSkinImageCount = 3;

MainFrame::MainFrame()
: bk_image_index_(12)
{}

MainFrame::~MainFrame()
{
	PostQuitMessage(0);
}

LPCTSTR MainFrame::GetWindowClassName() const
{
	return _T("TXGuiFoundation");
}

CControlUI* MainFrame::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass, _T("FriendList")) == 0)
	{
		return new CPartiaipantList(m_PaintManager);
	}
	//else if (_tcsicmp(pstrClass, _T("GroupList")) == 0)
	//{
	//	return new CGroupsUI(m_PaintManager);
	//}
	//else if (_tcsicmp(pstrClass, _T("MicroBlog")) == 0)
	//{
	//	//return new CMicroBlogUI(m_PaintManager);
	//}

	return NULL;
}

void MainFrame::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

CDuiString MainFrame::GetSkinFile()
{
	return _T("main_frame.xml");
}

CDuiString MainFrame::GetSkinFolder()
{
	//return  _T("skin\\");
	return _T("UIRes\\");
}

LRESULT MainFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT MainFrame::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if defined(WIN32) && !defined(UNDER_CE)
	//BOOL bZoomed = ::IsZoomed(m_hWnd);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	//if (::IsZoomed(m_hWnd) != bZoomed)
	//{
	//	if (!bZoomed)
	//	{
	//		CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(kMaxButtonControlName));
	//		if( pControl ) pControl->SetVisible(false);
	//		pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(kRestoreButtonControlName));
	//		if( pControl ) pControl->SetVisible(true);
	//	}
	//	else 
	//	{
	//		CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(kMaxButtonControlName));
	//		if( pControl ) pControl->SetVisible(true);
	//		pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(kRestoreButtonControlName));
	//		if( pControl ) pControl->SetVisible(false);
	//	}
	//}
#else
	//return __super::OnSysCommand(uMsg, wParam, lParam, bHandled);
#endif

	return 0;
}

LRESULT MainFrame::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return FALSE;
}

void MainFrame::OnTimer(TNotifyUI& msg)
{
}

void MainFrame::OnExit(TNotifyUI& msg)
{
	Close();
}

void MainFrame::InitWindow()
{}

void MainFrame::UpdateFriendsList()
{
	CPartiaipantList* pFriendsList = static_cast<CPartiaipantList*>(m_PaintManager.FindControl(kFriendsListControlName));
	if (pFriendsList != NULL)
	{
		if (!friends_.empty())
			friends_.clear();
		if (pFriendsList->GetCount() > 0)
			pFriendsList->RemoveAll();

		PtiptListItemInfo item;

		item.id = _T("0");
		item.folder = true;
		item.empty = false;
		item.nick_name = _T("已入会");

		root_parent_ = pFriendsList->AddNode(item, NULL);
		friends_.push_back(item);

		item.id = _T("1");
		item.folder = false;		
		item.logo = _T("man.png");
		item.nick_name = _T("tojen");
		item.video_icon  = _T("file='videoStatus.png' source='0,0,16,16'");
		item.video_icon_hot = _T("file='videoStatus.png' source='0,32,16,48'");
		item.description = _T("tojen.me@gmail.com");

		myself_info_ = item;

		pFriendsList->AddNode(item, root_parent_);
		friends_.push_back(item);

        item.id = _T("2");
        item.folder = false;
        item.logo = _T("default.png");
        item.nick_name = _T("wangchyz");
        item.description = _T("wangchyz@gmail.com");
		item.video_icon  = _T("file='videoStatus.png' source='0,0,16,16'");
		item.video_icon_hot = _T("file='videoStatus.png' source='0,32,16,48'");
        pFriendsList->AddNode(item, root_parent_);
        friends_.push_back(item);
	}
}

void MainFrame::OnPrepare(TNotifyUI& msg)
{
	UpdateFriendsList();
}

LRESULT MainFrame::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{ 
	if (uMsg == MSG_SETTING_MENU)
	{
		if (wParam == ITEM_ABOUT)
		{
			CAboutFrame dlg;
			dlg.Show(GetHWND());
		}
		else if (wParam == ITEM_VIDEO_CHECK)
		{
			//Close(0);
			MessageBox(GetHWND(),_T("video check"),_T("check"),0);
		}
		else if (wParam == ITEM_ONLINE_SERVIE)
		{
			MessageBox(GetHWND(),_T("在线客服"),_T("客服"),0);
		}
		else if (wParam == ITEM_QUESTION)
		{
			MessageBox(GetHWND(),_T("问题反馈"),_T("question"),0);
		}
		else if (wParam == ITEM_SETTING)
		{
			MessageBox(GetHWND(),_T("设置"),_T("setting"),0);
		}
	}

	//取消窗体双击事件
	if (uMsg == WM_NCLBUTTONDBLCLK)
	{
		return 0;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

void MainFrame::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, _T("windowinit")) == 0)
	{
		OnPrepare(msg);
	}
	else if (_tcsicmp(msg.sType, DUI_MSGTYPE_MOUSEENTER) == 0)
	{
		::ShowWindow(m_hWnd, SW_MINIMIZE);
	}
	else if (_tcsicmp(msg.sType, _T("killfocus")) == 0)
	{
		//if (_tcsicmp(msg.pSender->GetName(), kSignatureControlName) == 0)
		//{
		//	msg.pSender->SetVisible(false);
		//	CControlUI* signature_tip = m_PaintManager.FindControl(kSignatureTipsControlName);
		//	if (signature_tip != NULL)
		//	{
		//		CRichEditUI* signature = static_cast<CRichEditUI*>(msg.pSender);
		//		if (signature != NULL)
		//			signature_tip->SetText(signature->GetText());
		//		signature_tip->SetVisible(true);
		//	}
		//}
		//else if (_tcsicmp(msg.pSender->GetName(), kSearchEditControlName) == 0)
		//{
		//	msg.pSender->SetVisible(false);
		//	CControlUI* search_tip = static_cast<CRichEditUI*>(m_PaintManager.FindControl(kSearchEditTipControlName));
		//	if (search_tip != NULL)
		//	{
		//		CRichEditUI* search_edit = static_cast<CRichEditUI*>(msg.pSender);
		//		if (search_edit != NULL)
		//			search_tip->SetText(search_edit->GetText());
		//		search_tip->SetVisible(true);
		//	}
		//}
	}
	else if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		if (_tcsicmp(msg.pSender->GetName(), kCloseButtonControlName) == 0)
		{
			OnExit(msg);
		}
		else if (_tcsicmp(msg.pSender->GetName(), kMinButtonControlName) == 0)
		{
#if defined(UNDER_CE)
			::ShowWindow(m_hWnd, SW_MINIMIZE);
#else
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
#endif
		}
		else if(_tcsicmp(msg.pSender->GetName(), kAddUserControlName) == 0)
		{
			CPartiaipantList* pFriendsList = static_cast<CPartiaipantList*>(m_PaintManager.FindControl(kFriendsListControlName));
			if (pFriendsList != NULL)
			{
				PtiptListItemInfo item;

				item.id = _T("1");
				item.folder = false;		
				item.logo = _T("man.png");
				item.nick_name = _T("tojen");
				item.description = _T("tojen.me@gmail.com");
				item.video_icon  = _T("file='videoStatus.png' source='0,0,16,16'");
				item.video_icon_hot = _T("file='videoStatus.png' source='0,32,16,48'");
				friends_.push_back(item);
				pFriendsList->AddNode(item,root_parent_);
			}
		}
		else if(_tcsicmp(msg.pSender->GetName(), kDesktopShareName) == 0)
		{
			//MessageBox(m_hWnd,_T("桌面共享"),_T("test") ,0);
			if(false)//共享端
			{
				CDesktopShare *pdesktopDlg = new CDesktopShare;

				pdesktopDlg->Create(NULL, _T("桌面共享"), UI_WNDSTYLE_DIALOG | WS_POPUP,  NULL, 0, 0, 0, 0);

				pdesktopDlg->TopCenterWindow();
				::ShowWindow(*pdesktopDlg, SW_SHOW);
			}
			else
			{
				CDeskShareViewer* pDeskViewer = new CDeskShareViewer;

				pDeskViewer->Create(NULL, _T("DesktopShareView"), UI_WNDSTYLE_FRAME | WS_POPUP,  NULL, 0, 0, 0, 0);

				//skin_changed_observer_.AddReceiver(pChatDialog);

				pDeskViewer->CenterWindow();
				::ShowWindow(*pDeskViewer, SW_MAXIMIZE);
			}
		}
//		else if (_tcsicmp(msg.pSender->GetName(), kMaxButtonControlName) == 0)
//		{
//#if defined(UNDER_CE)
//			::ShowWindow(m_hWnd, SW_MAXIMIZE);
//			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(kMaxButtonControlName));
//			if( pControl ) pControl->SetVisible(false);
//			pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(kRestoreButtonControlName));
//			if( pControl ) pControl->SetVisible(true);
//#else
//			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
//#endif
//		}
		else if (_tcsicmp(msg.pSender->GetName(), kSettingListControlName) == 0)
		{
			CDuiRect rcWindow;
			GetWindowRect(m_hWnd, &rcWindow);
			rcWindow.top = rcWindow.top + msg.pSender->GetPos().bottom;
			new CSettingWindow(rcWindow,GetHWND(),MSG_SETTING_MENU);
			//CSettingWindow setWnd(this, rcWindow,GetHWND(),MSG_SETTING_MENU);
			//setWnd.Show(rcWindow,GetHWND(),MSG_SETTING_MENU);
		}
	}
	//else if (_tcsicmp(msg.sType, _T("timer")) == 0)
	//{
	//	return OnTimer(msg);
	//}
	else if (_tcsicmp(msg.sType, _T("selectchanged")) == 0)
	{
		/*CTabLayoutUI* pTabControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(kTabControlName));
		if (_tcsicmp(msg.pSender->GetName(), kFriendButtonControlName) == 0)
		{
			if (pTabControl && pTabControl->GetCurSel() != 0)
			{
				pTabControl->SelectItem(0);
				UpdateFriendsList();
			}
		}*/
		/*else if (_tcsicmp(msg.pSender->GetName(), kGroupButtonControlName) == 0)
		{
			if (pTabControl && pTabControl->GetCurSel() != 1)
			{
				pTabControl->SelectItem(1);
				UpdateGroupsList();
			}
		}
		else if (_tcsicmp(msg.pSender->GetName(), kMicroBlogButtonControlName) == 0)
		{
			if (pTabControl && pTabControl->GetCurSel() != 2)
			{
				pTabControl->SelectItem(2);
				UpdateMicroBlogList();
			}
		}*/
	}
	else if (_tcsicmp(msg.sType, _T("itemactivate")) == 0)
	{
		CTabLayoutUI* pTabControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(kTabControlName));
		if (pTabControl != NULL)
		{
			if (pTabControl->GetCurSel() == 0)
			{
				CPartiaipantList* pFriendsList = static_cast<CPartiaipantList*>(m_PaintManager.FindControl(kFriendsListControlName));
				if ((pFriendsList != NULL) &&  pFriendsList->GetItemIndex(msg.pSender) != -1)
				{
					if (_tcsicmp(msg.pSender->GetClass(), _T("ListContainerElementUI")) == 0)
					{
						//Node* node = (Node*)msg.pSender->GetTag();

						//CControlUI* background = m_PaintManager.FindControl(kBackgroundControlName);
						//if (!pFriendsList->CanExpand(node) && (background != NULL))
						//{
							/*PtiptListItemInfo friend_info;

							for (std::vector<PtiptListItemInfo>::const_iterator citer = friends_.begin(); citer != friends_.end(); ++citer)
							{
								if (_tcsicmp(citer->id, node->data().value) == 0)
								{
									friend_info = *citer;
									break;
								}
							}
							TCHAR szBuf[MAX_PATH] = {0};
							if (_tcslen(background->GetBkImage()) > 0)
							{
#if defined(UNDER_WINCE)
								_stprintf(szBuf, _T("bg%d.png"), bk_image_index_);
#else
								_stprintf_s(szBuf, MAX_PATH - 1, _T("bg%d.png"), bk_image_index_);
#endif
							}*/

//							ChatDialog* pChatDialog = new ChatDialog(szBuf, background->GetBkColor(), myself_info_, friend_info);
//							if( pChatDialog == NULL )
//								return;
//#if defined(WIN32) && !defined(UNDER_CE)
//							pChatDialog->Create(NULL, _T("ChatDialog"), UI_WNDSTYLE_FRAME | WS_POPUP,  NULL, 0, 0, 0, 0);
//#else
//							pChatDialog->Create(NULL, _T("ChatDialog"), UI_WNDSTYLE_FRAME | WS_POPUP, NULL, 0, 0, 0, 0);
//#endif
//							skin_changed_observer_.AddReceiver(pChatDialog);
//
//							pChatDialog->CenterWindow();
//							::ShowWindow(*pChatDialog, SW_SHOW);
						//}
					}
				}
			}
		}
	}
	else if (_tcsicmp(msg.sType, _T("itemclick")) == 0)
	{
		CTabLayoutUI* pTabControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(kTabControlName));
		if (pTabControl != NULL)
		{
			if (pTabControl->GetCurSel() == 0)
			{
				CPartiaipantList* pFriendsList = static_cast<CPartiaipantList*>(m_PaintManager.FindControl(kFriendsListControlName));
				if ((pFriendsList != NULL) &&  pFriendsList->GetItemIndex(msg.pSender) != -1)
				{
					if (_tcsicmp(msg.pSender->GetClass(), _T("ListContainerElementUI")) == 0)
					{
						Node* node = (Node*)msg.pSender->GetTag();

						if (pFriendsList->CanExpand(node))
						{
							pFriendsList->SetChildVisible(node, !node->data().child_visible_);
						}
					}
				}
			}
			/*else if (pTabControl->GetCurSel() == 1)
			{
				CGroupsUI* pGroupsList = static_cast<CGroupsUI*>(m_PaintManager.FindControl(kGroupsListControlName));
				if ((pGroupsList != NULL) &&  pGroupsList->GetItemIndex(msg.pSender) != -1)
				{
					if (_tcsicmp(msg.pSender->GetClass(), _T("ListContainerElementUI")) == 0)
					{
						Node* node = (Node*)msg.pSender->GetTag();

						if (pGroupsList->CanExpand(node))
						{
							pGroupsList->SetChildVisible(node, !node->data().child_visible_);
						}
					}
				}
			}*/

		}
	}
}

//LRESULT MainFrame::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
//{
//	return 0;
//}

UILIB_RESOURCETYPE MainFrame::GetResourceType() const
{
	//return UILIB_ZIPRESOURCE;
	return UILIB_FILE;
}

LPCTSTR MainFrame::GetResourceID() const
{
	return MAKEINTRESOURCE(101);
}
