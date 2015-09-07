#ifndef UIFRIENDS_HPP
#define UIFRIENDS_HPP

#include "UIListCommonDefine.hpp"

namespace DuiLib
{
struct PtiptListItemInfo
{
	bool folder;
	bool empty;
	CDuiString id;
	CDuiString logo;
	CDuiString nick_name;
	CDuiString description;
	CDuiString video_icon;
	CDuiString video_icon_hot;
};


class CPartiaipantList : public CListUI
{
public:
	enum {SCROLL_TIMERID = 10};

	CPartiaipantList(CPaintManagerUI& paint_manager);

	~CPartiaipantList();

	bool Add(CControlUI* pControl);

	bool AddAt(CControlUI* pControl, int iIndex);

	bool Remove(CControlUI* pControl);

	bool RemoveAt(int iIndex);

	void RemoveAll();

	void DoEvent(TEventUI& event);

	Node* GetRoot();

	Node* AddNode(const PtiptListItemInfo& item, Node* parent = NULL);

	bool RemoveNode(Node* node);

	void SetChildVisible(Node* node, bool visible);

	bool CanExpand(Node* node) const;

	bool SelectItem(int iIndex, bool bTakeFocus = false);

private:
	Node*	root_node_;
	LONG	delay_deltaY_;
	DWORD	delay_number_;
	DWORD	delay_left_;
	CDuiRect	text_padding_;
	int level_text_start_pos_;
	CDuiString level_expand_image_;
	CDuiString level_collapse_image_;
	CPaintManagerUI& paint_manager_;

    CDialogBuilder m_dlgBuilder;
};

} // DuiLib

#endif // UIFRIENDS_HPP