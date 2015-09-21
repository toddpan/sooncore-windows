#ifndef UIFRIENDS_HPP
#define UIFRIENDS_HPP

#include "UIListCommonDefine.hpp"

namespace DuiLib
{
	const TCHAR* const VoiceEnableImg = _T("file='images\\voice.png'");
	const TCHAR* const VoiceEnableImgHot = _T("file='images\\voiceHover.png'");
	const TCHAR* const VoiceMuteImg = _T("file='images\\voiceMute.png'");
	const TCHAR* const VoiceMuteImgHot = _T("file='images\\voiceMuteHover.png'");
	
	const TCHAR* const VideoOpenImg = _T("file='images\\openCamera.png'");
	const TCHAR* const VideoOpenImgHot = _T("file='images\\openCameraHover.png'");
	const TCHAR* const VideoMuteImg = _T("");
	const TCHAR* const VideoMuteImgHot = _T("");

struct PtiptListItemInfo
{
	bool folder;
	bool empty;
	CDuiString id;
	CDuiString logo;
	CDuiString nick_name;
	CDuiString description;

	enum VOICE_STATUS
	{
		VOICE_CLOSE		= -1,
		VOICE_Mute		= 0,
		VOICE_Enable	= 1
	};

	VOICE_STATUS eVoiceStatus;

	enum CAMERA_STATUS
	{
		CAMERA_CLOSE	= -1,
		CAMERA_Mute		= 0,
		CAMERA_Enable	= 1
	};
	CAMERA_STATUS eVideoStatus;
	//CDuiString voice_icon;
	//CDuiString voice_icon_hot;
	//CDuiString video_icon;
	//CDuiString video_icon_hot;
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
	void SetSelectedItemBkColor(DWORD dwBkColor);
	void SetHotItemBkColor(DWORD dwBkColor);
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