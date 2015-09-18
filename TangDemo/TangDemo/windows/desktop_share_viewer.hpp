#ifndef DESKTOP_SHARE_VIEWER_HPP
#define DESKTOP_SHARE_VIEWER_HPP

#include "WindowWithShadow.hpp"
using namespace DuiLib;

class CDynamicHorizontalLayoutUI :public CHorizontalLayoutUI
{
public:
	CDynamicHorizontalLayoutUI(void);
protected:
	void DoEvent(TEventUI& event) override;
};

class CDeskShareViewer : public CWindowWithShadow //public WindowImplBase
{
public:
	CDeskShareViewer();
	~CDeskShareViewer();
public:
	LPCTSTR GetWindowClassName() const;	
	virtual void OnFinalMessage(HWND hWnd);
	virtual void InitWindow();
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	static CControlUI* FindChild( CContainerUI* pContainer, LPCTSTR strName );
	DUI_DECLARE_MESSAGE_MAP()
	virtual void OnMouseHoverEvent(TNotifyUI& msg);
protected:	

	void Notify(TNotifyUI& msg);
	void OnPrepare(TNotifyUI& msg);
	//void OnExit(TNotifyUI& msg);

private:
	bool m_bTopFrameIsHidden;
};

#endif // DESKTOP_SHARE_VIEWER_HPP